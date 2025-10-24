#include "ofApp.h"
#include <algorithm>
#include <cmath>
using std::vector;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false); // keep trails
    ofEnableAlphaBlending();
    // Drawing uses simple aliased lines for crisp mono look

    // Start with black background, white strokes
    invertColors = false;
    fadeTrails = true;
    fadeAlpha = 10;
    mode = Mode::Sunflower; // default to sunflower mode

    resetParticles();
    clearCanvas();
}

//--------------------------------------------------------------
void ofApp::update(){
    if (mode == Mode::Flow) {
        float t = ofGetElapsedTimef() * timeScale;
        float w = ofGetWidth();
        float h = ofGetHeight();

        for (size_t i = 0; i < positions.size(); ++i) {
            // store previous position
            prevPositions[i] = positions[i];

            // flow-field angle from noise
            float nx = positions[i].x * noiseScale;
            float ny = positions[i].y * noiseScale;
            float angle = ofNoise(nx, ny, t) * TWO_PI * 4.0f; // 4 curls

            glm::vec2 dir = {cosf(angle), sinf(angle)};
            positions[i] += dir * speed;

            // wrap-around edges
            if (positions[i].x < 0) positions[i].x += w;
            if (positions[i].x >= w) positions[i].x -= w;
            if (positions[i].y < 0) positions[i].y += h;
            if (positions[i].y >= h) positions[i].y -= h;
        }
    } else {
        // Sunflower growth animation
        if (sunflowerAnimate && sunflowerShown < sunflowerSeeds) {
            sunflowerShown = std::min(sunflowerSeeds, sunflowerShown + 12);
        } else if (!sunflowerAnimate) {
            sunflowerShown = sunflowerSeeds;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (mode == Mode::Flow) {
        // gentle fade to background to create trails
        if (fadeTrails && fadeAlpha > 0) {
            unsigned char bg = invertColors ? 255 : 0;
            ofSetColor(bg, bg, bg, ofClamp(fadeAlpha, 0, 255));
            ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        }

        // draw strokes
        unsigned char fg = invertColors ? 0 : 255;
        ofSetColor(fg);
        ofSetLineWidth(1.0f);

        for (size_t i = 0; i < positions.size(); ++i) {
            const glm::vec2 &a = prevPositions[i];
            const glm::vec2 &b = positions[i];
            ofDrawLine(a, b);
        }
    } else {
        drawSunflower();
    }
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'm':
        case 'M': {
            mode = (mode == Mode::Flow) ? Mode::Sunflower : Mode::Flow;
            clearCanvas();
            break;
        }
        case 'r':
        case 'R':
            if (mode == Mode::Flow) {
                resetParticles();
            } else {
                sunflowerShown = 0; // regrow
            }
            break;
        case 'c':
        case 'C':
            clearCanvas();
            break;
        case 'i':
        case 'I':
            invertColors = !invertColors;
            clearCanvas();
            break;
        case 'f':
        case 'F':
            if (mode == Mode::Flow) fadeTrails = !fadeTrails;
            break;
        case '[':
            if (mode == Mode::Flow) {
                fadeAlpha = std::max(0, fadeAlpha - 2);
            } else {
                sunflowerSeeds = std::max(100, sunflowerSeeds - 100);
                sunflowerShown = std::min(sunflowerShown, sunflowerSeeds);
            }
            break;
        case ']':
            if (mode == Mode::Flow) {
                fadeAlpha = std::min(255, fadeAlpha + 2);
            } else {
                sunflowerSeeds = std::min(20000, sunflowerSeeds + 100);
            }
            break;
        case '-':
            if (mode == Mode::Flow) speed = std::max(0.1f, speed - 0.1f);
            else sunflowerSeedRadius = std::max(0.5f, sunflowerSeedRadius - 0.2f);
            break;
        case '=':
        case '+':
            if (mode == Mode::Flow) speed += 0.1f;
            else sunflowerSeedRadius = std::min(10.0f, sunflowerSeedRadius + 0.2f);
            break;
        case ',':
            if (mode == Mode::Flow) noiseScale = std::max(0.0005f, noiseScale * 0.8f);
            else sunflowerAnimate = !sunflowerAnimate;
            break;
        case '.':
            if (mode == Mode::Flow) noiseScale = std::min(0.02f, noiseScale * 1.25f);
            else sunflowerShown = 0;
            break;
        case 'p':
        case 'P':
            if (mode == Mode::Flow) timeScale = ofClamp(timeScale + ofRandom(-0.05f, 0.05f), 0.0f, 1.0f);
            break;
        case 's':
        case 'S': {
            std::string name = "mySketch-" + ofGetTimestampString("%Y%m%d-%H%M%S") + ".png";
            ofSaveScreen(name);
            ofLogNotice() << "Saved screenshot: " << name;
            break;
        }
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if (mode != Mode::Flow) return;
    // Nudge a small subset of particles toward the cursor for interaction
    for (int k = 0; k < 200 && !positions.empty(); ++k) {
        int i = static_cast<int>(ofRandom(positions.size()));
        positions[i] = glm::vec2(x, y) + glm::vec2(ofRandom(-20, 20), ofRandom(-20, 20));
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (mode != Mode::Flow) return;
    // Seed a burst of particles near the press point
    for (int k = 0; k < 400 && !positions.empty(); ++k) {
        int i = static_cast<int>(ofRandom(positions.size()));
        positions[i] = glm::vec2(x, y) + glm::vec2(ofRandom(-50, 50), ofRandom(-50, 50));
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    // Clear when size changes to avoid stretched trails
    clearCanvas();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::resetParticles() {
    positions.resize(numParticles);
    prevPositions.resize(numParticles);
    for (int i = 0; i < numParticles; ++i) {
        positions[i] = glm::vec2(ofRandomWidth(), ofRandomHeight());
        prevPositions[i] = positions[i];
    }
}

//--------------------------------------------------------------
void ofApp::clearCanvas() {
    unsigned char bg = invertColors ? 255 : 0;
    ofSetColor(bg);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::drawSunflower() {
    // solid background per frame for crisp mono image
    unsigned char bg = invertColors ? 255 : 0;
    unsigned char fg = invertColors ? 0 : 255;
    ofSetColor(bg);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    ofSetColor(fg);
    ofFill();
    ofSetCircleResolution(24);

    float w = ofGetWidth();
    float h = ofGetHeight();
    glm::vec2 c(w * 0.5f, h * 0.5f);

    // choose radius to fit nicely
    float R = std::min(w, h) * 0.46f;
    float scale = R / std::sqrt((float)std::max(1, sunflowerSeeds));

    // golden angle in radians
    const float phi = PI * (3.0f - std::sqrt(5.0f));

    int N = sunflowerAnimate ? sunflowerShown : sunflowerSeeds;
    for (int n = 0; n < N; ++n) {
        float r = scale * std::sqrt((float)n);
        float theta = n * phi;
        glm::vec2 p = c + r * glm::vec2(cosf(theta), sinf(theta));
        ofDrawCircle(p, sunflowerSeedRadius);
    }
}
