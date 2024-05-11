#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    image.load("stars.png");
    image.resize(450, 450);

    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.enableColors();
    mesh.enableIndices();

    float intensityThreshold = 180.0;
    int w = image.getWidth();
    int h = image.getHeight();
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            ofColor c = image.getColor(x, y);
            float intensity = c.getLightness();
            if (intensity >= intensityThreshold) {
                float saturation = c.getSaturation();
                float z = ofMap(saturation, 0, 255, -100, 100);
                ofVec3f pos(x * 2, y * 2, z);
                mesh.addVertex(pos);
                mesh.addColor(c);
            }
        }
    }

    float connectionDistance = 30;
    int numVerts = mesh.getNumVertices();
    for (int a = 0; a < numVerts; ++a) {
        ofVec3f verta = mesh.getVertex(a);
        for (int b = a + 1; b < numVerts; ++b) {
            ofVec3f vertb = mesh.getVertex(b);
            float distance = verta.distance(vertb);
            if (distance <= connectionDistance) {
                mesh.addIndex(a);
                mesh.addIndex(b);
            }
        }
    }

    noiseSeeds.resize(mesh.getNumVertices());
    offsets.resize(mesh.getNumVertices());  // Ensure this is properly resized
    for (size_t i = 0; i < noiseSeeds.size(); ++i) {
        noiseSeeds[i] = ofRandom(0, 1000);
        offsets[i] = ofVec3f(ofRandom(0,100000), ofRandom(0,100000), ofRandom(0,100000));
    }

    ofSetFrameRate(60);  // Set the frame rate
}

//--------------------------------------------------------------
void ofApp::update(){
    int numVerts = mesh.getNumVertices();
    float time = ofGetElapsedTimef();
    float timeScale = 5.0;
    float displacementScale = 0.75;

    for (int i = 0; i < numVerts; ++i) {
        ofVec3f vert = mesh.getVertex(i);
        ofVec3f timeOffsets = offsets[i];

        vert.x += ofSignedNoise(time * timeScale + timeOffsets.x) * displacementScale;
        vert.y += ofSignedNoise(time * timeScale + timeOffsets.y) * displacementScale;
        vert.z += ofSignedNoise(time * timeScale + timeOffsets.z) * displacementScale;

        mesh.setVertex(i, vert);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);

    easyCam.begin();
        ofPushMatrix();
            ofTranslate(-ofGetWidth()/3, -ofGetHeight()/2);
            mesh.draw();
        ofPopMatrix();
    easyCam.end();
}

// Define the remaining event handlers with empty implementations
// or remove them from the header if not used to avoid linker errors

//--------------------------------------------------------------
void ofApp::exit() {
    // Cleanup code here
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // Handle key press
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    // Handle key release
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    // Handle mouse movement
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    // Handle mouse drag
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    // Handle mouse press
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    // Handle mouse release
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {
    // Handle mouse scroll
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
    // Handle mouse enter
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
    // Handle mouse exit
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    // Handle window resize
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    // Handle drag event
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    // Handle messages received
}
