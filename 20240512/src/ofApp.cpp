#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    image.load("stars.png");
    image.resize(300, 300);

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
    offsets.resize(mesh.getNumVertices());
    for (size_t i = 0; i < noiseSeeds.size(); ++i) {
        noiseSeeds[i] = ofRandom(0, 1000);
        offsets[i] = ofVec3f(ofRandom(0, 100000), ofRandom(0, 100000), ofRandom(0, 100000));
    }

    meshCopy = mesh;
    mouseDisplacement = false;  // Start without the magnifying effect
}

//--------------------------------------------------------------
void ofApp::update() {
    if (mouseDisplacement) {
        ofVec3f mouse(mouseX, ofGetHeight() - mouseY, 0);
        for (int i = 0; i < mesh.getNumVertices(); ++i) {
            ofVec3f vertex = meshCopy.getVertex(i);
            float distanceToMouse = mouse.distance(vertex);
            float displacement = ofMap(distanceToMouse, 0, 400, 300.0, 0, true);
            ofVec3f direction = vertex - mouse;
            direction.normalize();
            ofVec3f displacedVertex = vertex + displacement * direction;
            mesh.setVertex(i, displacedVertex);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'm') {
        mouseDisplacement = !mouseDisplacement;
        if (!mouseDisplacement) {
            mesh = meshCopy;  // Restore the original mesh
        }
    }
}

// Define the remaining event handlers with empty implementations or as needed
//--------------------------------------------------------------
void ofApp::exit() {
    // Cleanup code here
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
