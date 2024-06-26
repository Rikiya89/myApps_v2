#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);

    // Setup main lighting
    light.setup();
    light.setPosition(600, 600, 600);
    light.enable();

    // Setup point light for glowing effect
    pointLight.setup();
    pointLight.setPointLight();
    pointLight.setPosition(0, 0, 0);
    pointLight.setDiffuseColor(ofColor(255, 255, 255));
    pointLight.setSpecularColor(ofColor(255, 255, 255));
    pointLight.enable();

    // Define start, mid, and end colors
    startColor = ofColor(255, 0, 0);  // Red
    midColor = ofColor(0, 255, 0);    // Green
    endColor = ofColor(0, 0, 255);    // Blue

    rotationAngle = 0.0f;
    animationOffset = 0.0f;
    time = 0.0f;

    cam.setDistance(1000);
}

//--------------------------------------------------------------
void ofApp::update(){
    rotationAngle += 0.3f; // Rotate by 0.1 degrees every frame (slower rotation speed)
    animationOffset += 0.03f; // Update animation offset for sine wave motion
    time += 0.01f; // Increment time for dynamic radius effect
}

//--------------------------------------------------------------
void ofApp::draw(){

    cam.begin();

    int numPoints = 1200;
    float baseHelixRadius = 300;
    float helixHeight = 900;
    float helixTurns = 5;
    float waveAmplitude = 30; // Amplitude of the sine wave motion
    int numLayers = 12; // Number of helix layers

    ofSetLineWidth(3);
    ofEnableDepthTest();

    ofPushMatrix();
    ofRotateYDeg(rotationAngle); // Apply rotation animation

    for (int layer = 0; layer < numLayers; ++layer) {
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_LINE_STRIP);

        for (int i = 0; i < numPoints; i++) {
            float t = ofMap(i, 0, numPoints, 0, TWO_PI * helixTurns);
            float radius = baseHelixRadius + 50 * sin(time + layer * PI / numLayers); // Dynamic radius effect
            float x = radius * cos(t + layer * TWO_PI / numLayers);
            float y = radius * sin(t + layer * TWO_PI / numLayers);
            float z = ofMap(i, 0, numPoints, -helixHeight / 2, helixHeight / 2) + waveAmplitude * sin(t + animationOffset);

            // Interpolate color dynamically
            float colorFactor = (sin(t * 0.5 + ofGetElapsedTimef() + layer * PI / numLayers) + 1) / 2; // Creates a dynamic wave effect
            ofColor color;
            if (layer == 0) color = startColor.getLerped(midColor, colorFactor);
            else if (layer == 1) color = midColor.getLerped(endColor, colorFactor);
            else if (layer == 2) color = endColor.getLerped(startColor, colorFactor);
            else if (layer == 3) color = startColor.getLerped(endColor, colorFactor);
            else color = endColor.getLerped(midColor, colorFactor);
            color.a = ofMap(i, 0, numPoints, 255, 50); // Add transparency for trailing effect
            mesh.addColor(color);
            mesh.addVertex(glm::vec3(x, y, z));
        }

        mesh.draw();

        // Add moving particles along the helix path
        for (int i = 0; i < numPoints; i += 50) {
            float t = ofMap(i, 0, numPoints, 0, TWO_PI * helixTurns) + animationOffset; // Make particles move along the helix
            float radius = baseHelixRadius + 50 * sin(time + layer * PI / numLayers); // Dynamic radius effect
            float x = radius * cos(t + layer * TWO_PI / numLayers);
            float y = radius * sin(t + layer * TWO_PI / numLayers);
            float z = ofMap(i, 0, numPoints, -helixHeight / 2, helixHeight / 2) + waveAmplitude * sin(t);

            // Draw glowing particles with pulsing effect
            float pulse = (sin(ofGetElapsedTimef() * 5 + t) + 1) / 2 * 10 + 5; // Pulsing size
            ofSetColor(255, 255, 255, 128); // Add transparency for particles
            ofDrawSphere(glm::vec3(x, y, z), pulse);
        }
    }

    ofPopMatrix();

    ofDisableDepthTest();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
