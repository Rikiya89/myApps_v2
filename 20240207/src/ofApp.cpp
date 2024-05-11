#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60); // Set the frame rate
    ofBackground(255, 248, 220); // Set a light background color
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    vector<ofColor> colors = {
        ofColor::fromHex(0xF44336), // Red
        ofColor::fromHex(0x9C27B0), // Purple
        ofColor::fromHex(0x3F51B5), // Blue
        ofColor::fromHex(0x009688), // Teal
        ofColor::fromHex(0xFFEB3B), // Yellow
        ofColor::fromHex(0x795548), // Brown
    };

    int numColors = colors.size();
    int tileSize = 50;
    int patternRepeat = 4;
    float time = ofGetElapsedTimef(); // Get the elapsed time

    for (int x = 0; x < ofGetWidth(); x += tileSize * patternRepeat) {
        for (int y = 0; y < ofGetHeight(); y += tileSize * patternRepeat) {
            for (int i = 0; i < patternRepeat; i++) {
                for (int j = 0; j < patternRepeat; j++) {
                    int colorIndex = (i + j + (int)(time * 2)) % numColors; // Animate color changes over time
                    ofSetColor(colors[colorIndex]);

                    if ((i + j) % 2 == 0) {
                        // Dynamic rotation for the diamond shape
                        float angle = time * 10; // Rotate based on time
                        ofPushMatrix();
                        ofTranslate(x + i * tileSize + tileSize / 2, y + j * tileSize + tileSize / 2);
                        ofRotateDeg(angle);
                        ofDrawRectangle(-tileSize / 2, -tileSize / 2, tileSize, tileSize);
                        ofPopMatrix();
                    } else {
                        // Pulsing effect for circles
                        float radius = tileSize / 2 + sin(time * 3) * 10; // Sin wave for dynamic radius
                        ofDrawCircle(x + i * tileSize + tileSize / 2, y + j * tileSize + tileSize / 2, radius);
                    }
                }
            }

            // Animated zigzag pattern
            ofSetColor(255); // Use white for the zigzag lines
            for (int k = 0; k <= patternRepeat * tileSize; k += tileSize / 2) {
                float wave = sin(time + k * 0.05) * 20; // Sin wave for a waving effect
                ofDrawLine(x + wave, y + k, x + patternRepeat * tileSize + wave, y + k - tileSize / 2);
            }
        }
    }
}
