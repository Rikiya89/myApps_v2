#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(28, 34, 70);
    ofEnableDepthTest();
    ofSetSmoothLighting(true);

    positions.clear();

    int numArms = 8;          // More spiral arms for density
    int pointsPerArm = 90;    // More stars per arm
    float spiralRadius = 780;
    float starSpacing = 13;

    for (int arm = 0; arm < numArms; arm++) {
        float armOffset = ofRandom(1000);
        for (int i = 0; i < pointsPerArm; i++) {
            float angle = ofMap(i, 0, pointsPerArm, 0, TWO_PI * 2.7); // More turns
            float armAngle = TWO_PI * arm / numArms + angle;
            float radius = ofMap(i, 0, pointsPerArm, 80, spiralRadius);

            // Spiral with a bit more chaos
            float nx = cos(armAngle) * radius + ofNoise(arm, i*0.06) * 52;
            float ny = sin(armAngle) * radius + ofNoise(arm*2, i*0.09) * 52;
            float nz = (i - pointsPerArm/2) * starSpacing + ofNoise(arm*3, i*0.04) * 90;
            positions.push_back(ofVec3f(nx, ny, nz));
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Bright, cosmic background
    ofClear(28, 34, 70, 255); // Rich deep blue

    cam.begin();

    float t = ofGetElapsedTimef();

    // Brighter connecting lines with color cycling
    for (int i = 0; i < positions.size(); i++) {
        for (int j = i + 1; j < positions.size(); j++) {
            float dist = positions[i].distance(positions[j]);
            if (dist < 90) {
                float hue = fmod(170 + 90 * sin(t * 0.5 + i * 0.03 + j * 0.06), 255);
                float alpha = ofMap(dist, 10, 90, 160, 50, true);
                ofSetColor(ofColor::fromHsb(hue, 245, 245), alpha);
                ofSetLineWidth(2.2);
                ofDrawLine(positions[i], positions[j]);
            }
        }
    }

    // Glowing, vibrant stars with animation
    for (int i = 0; i < positions.size(); i++) {
        ofPushMatrix();
        ofTranslate(positions[i]);

        // Swirl
        float baseAngle = atan2(positions[i].y, positions[i].x);
        float r = ofVec2f(positions[i].x, positions[i].y).length();
        float swirl = t * 0.22 + r * 0.001 + baseAngle;
        ofRotateZDeg(ofRadToDeg(swirl));

        // Color: Max brightness, more hue variation
        float n = ofNoise(i * 0.09, t * 0.21);
        float hue = fmod(150 + 100 * n + 95 * sin(t * 0.7 + i), 255);
        ofColor starColor = ofColor::fromHsb(hue, 255, 255);

        // Bright halo
        ofSetColor(starColor.r, starColor.g, starColor.b, 95);
        ofDrawSphere(0, 0, 0, 35 + 16 * n);

        // Main star: super bright and opaque
        ofSetColor(starColor.r, starColor.g, starColor.b, 250);
        float starSize = 17 + 10 * n + 12 * fabs(sin(t * 1.0 + i * 0.16));
        ofDrawSphere(0, 0, 0, starSize);

        // Add white sparkle for intense stars (center-most)
        if (r < 180) {
            ofSetColor(255, 255, 255, 190);
            ofDrawSphere(0, 0, 0, 6 + 5 * fabs(sin(t + i)));
        }

        // Animated rotating ring
        float ringRadius = starSize + 7 + 3 * sin(t * 0.8 + i);
        float ringHue = fmod(hue + 35, 255);
        ofSetColor(ofColor::fromHsb(ringHue, 255, 255), 160);
        ofSetLineWidth(3.0);
        ofNoFill();
        ofPushMatrix();
        ofRotateZDeg(ofGetElapsedTimef() * 35 + i * 2); // Animate rotation
        ofDrawCircle(0, 0, ringRadius);

        // Orbiting mini-planet animation
        float orbitAngle = t * 1.6 + i * 0.85;
        float orbitRadius = ringRadius + 12 + 6 * sin(t * 0.3 + i);
        float px = cos(orbitAngle) * orbitRadius;
        float py = sin(orbitAngle) * orbitRadius;
        float planetHue = fmod(hue + 120, 255);
        ofSetColor(ofColor::fromHsb(planetHue, 255, 255), 220);
        ofDrawCircle(px, py, 7.5f + 2.5f * fabs(sin(t * 0.7 + i)));

        ofPopMatrix();
        ofFill();

        ofPopMatrix();
    }

    // Cosmic spiral pulse effect
    int numSpiralArms = 6;
    float spiralCore = 60 + 20 * sin(t * 0.4);
    for (int arm = 0; arm < numSpiralArms; arm++) {
        ofSetColor(255, 255, 255, 28);
        ofSetLineWidth(2.5);
        float phase = t * 0.5 + arm * TWO_PI / numSpiralArms;
        for (int j = 0; j < 150; j++) {
            float angle = j * 0.08f + phase;
            float r = spiralCore + j * 4.2 + 30 * sin(t * 0.9 + arm * 0.7 + j * 0.16);
            float x = cos(angle) * r;
            float y = sin(angle) * r;
            float nextAngle = (j+1) * 0.08f + phase;
            float nextR = spiralCore + (j+1) * 4.2 + 30 * sin(t * 0.9 + arm * 0.7 + (j+1) * 0.16);
            float nx = cos(nextAngle) * nextR;
            float ny = sin(nextAngle) * nextR;
            ofDrawLine(x, y, 0, nx, ny, 0);
        }
    }

    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}
void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::exit() {}
