#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    gridWidth = 35;  // Slightly increase for performance, but maintain complexity
    gridHeight = 35;
    noiseOffset = 0;
    noiseIncrement = 0.02;  // Fine-tune for more intricate noise patterns
    magnetismStrength = 600.0;  // Increase for more pronounced interaction

    ofBackground(0);
    ofSetCircleResolution(32);  // Maintain resolution for performance

    // Populate the life cycles for more nuanced motion
    for(int x = 0; x < ofGetWidth(); x += gridWidth){
        for(int y = 0; y < ofGetHeight(); y += gridHeight){
            lifeCycles.push_back(ofRandom(0, TWO_PI));
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    noiseOffset += 0.03;  // Slightly quicker evolution for dynamic visuals
}

//--------------------------------------------------------------
void ofApp::draw(){
    float time = ofGetElapsedTimef();
    vector<glm::vec2> positions;
    vector<float> sizes;

    // Introduce a fluid-like motion for the circles
    for(int x = 0; x < ofGetWidth(); x += gridWidth){
        for(int y = 0; y < ofGetHeight(); y += gridHeight){
            float noiseValue = ofNoise(x * noiseIncrement, y * noiseIncrement, noiseOffset);
            float lifeCycle = lifeCycles[(y / gridHeight) * (ofGetWidth() / gridWidth) + (x / gridWidth)];
            float size = ofMap(noiseValue, 0, 1, 15, gridWidth / 2) * (1 + 0.3 * sin(lifeCycle + time));

            glm::vec2 position = glm::vec2(x + gridWidth / 2 + 10 * sin(time + y * 0.05), y + gridHeight / 2 + 10 * cos(time + x * 0.05));
            positions.push_back(position);
            sizes.push_back(size);

            float hue = ofMap(x, 0, ofGetWidth(), 0, 255) + 128 * sin(time * 0.05 + y * 0.01);
            ofColor color;
            color.setHsb(hue, 255, 255, 180);  // Slightly transparent for a softer look
            ofSetColor(color);
            ofDrawCircle(position, size);
        }
    }

    // Enhanced line connections with variable thickness and more reactivity to the mouse
    for (size_t i = 0; i < positions.size(); i++) {
        for (size_t j = i + 1; j < positions.size(); j++) {
            float distance = glm::distance(positions[i], positions[j]);
            float mouseDistance = glm::distance(positions[i], mousePos) + glm::distance(positions[j], mousePos);
            if (distance < 150 && mouseDistance < 450) {  // Broadened range for a more connected feel
                float alpha = ofMap(distance, 0, 150, 200, 0) * ofMap(mouseDistance, 0, 450, 1, 0.1);
                float thickness = ofMap(distance, 0, 150, 3, 0.5);
                ofSetLineWidth(thickness);
                ofSetColor(255, 255, 255, alpha);
                ofDrawLine(positions[i], positions[j]);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    mousePos.x = x;
    mousePos.y = y;
}
