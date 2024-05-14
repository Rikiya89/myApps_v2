#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    image.load("chrysanthemum.jpg");
    width = image.getWidth();
    height = image.getHeight();

    mesh.setMode(OF_PRIMITIVE_POINTS);
    float intensityThreshold = 100.0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ofColor c = image.getColor(x, y);
            float brightness = c.getBrightness();
            if (brightness > intensityThreshold) {
                float z = ofMap(brightness, 0, 255, -300, 300);
                ofVec3f vertex(x - width / 2, y - height / 2, z);
                mesh.addVertex(vertex);
                mesh.addColor(c);
                baseVertices.push_back(vertex);
                baseColors.push_back(ofFloatColor(c.r / 255.0, c.g / 255.0, c.b / 255.0));
            }
        }
    }
    glPointSize(2);
    time = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    time += ofGetLastFrameTime();

    for (int i = 0; i < mesh.getNumVertices(); i++) {
        ofVec3f vertex = baseVertices[i];

        float xDisplacement = ofMap(sin(time * 1.3 + vertex.x * 0.02), -1, 1, -30, 30);
        float yDisplacement = ofMap(cos(time * 1.2 + vertex.y * 0.02), -1, 1, -30, 30);
        float zDisplacement = ofMap(sin(time * 1.5 + vertex.x * 0.05 + vertex.y * 0.05), -1, 1, -50, 50)
                            + ofMap(cos(time * 1.3 + vertex.x * 0.02 + vertex.y * 0.02), -1, 1, -30, 30);

        vertex.x = baseVertices[i].x + xDisplacement;
        vertex.y = baseVertices[i].y + yDisplacement;
        vertex.z = baseVertices[i].z + zDisplacement;

        mesh.setVertex(i, vertex);

        // Update color based on z position
        float colorShift = ofMap(vertex.z, -350, 350, 0, 1);
        ofFloatColor color = baseColors[i];
        color.setHue(fmod(color.getHue() + colorShift, 1.0));
        mesh.setColor(i, color);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Create gradient background
    ofColor color1(10, 10, 50); // Dark blue
    ofColor color2(0, 0, 0); // Black
    ofBackgroundGradient(color1, color2, OF_GRADIENT_CIRCULAR);

    ofEnableDepthTest();
    cam.begin();
    mesh.draw();
    cam.end();
    ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

// The remaining functions can remain empty if not used
void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y ) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
void ofApp::gotMessage(ofMessage msg) {}
