#include "ofApp.h"

void ofApp::setup(){
    ofSetBackgroundColor(ofColor::black);
    numWidth = 20;  // Increased grid density
    numHeight = 20; // Increased grid density
    phase = 0.0;
    speed = 0.02;   // Slower phase increment for smoother animation
}

void ofApp::update(){
    phase += speed;
}

void ofApp::draw(){
    float width = ofGetWidth() / numWidth;
    float height = ofGetHeight() / numHeight;

    for (int i = 0; i < numWidth; i++) {
        for (int j = 0; j < numHeight; j++) {
            float x = i * width;
            float y = j * height;
            float distance = ofDist(x, y, ofGetWidth()/2, ofGetHeight()/2);
            float offset = ofMap(distance, 0, ofGetWidth()/2, 0, PI * 2);
            float radius = ofMap(sin(phase + offset), -1, 1, 5, width/2);
            
            // Define specific hues based on grid position for diversity
            ofColor color;
            switch ((i + j) % 6) {  // Using modulo to cycle through six different colors
                case 0:
                    color = ofColor::fromHex(0x007FFF); // Sky Blue
                    break;
                case 1:
                    color = ofColor::fromHex(0x40E0D0); // Turquoise
                    break;
                case 2:
                    color = ofColor::deepSkyBlue;
                    break;
                case 3:
                    color = ofColor::darkBlue;
                    break;
                case 4:
                    color = ofColor::midnightBlue; // Midnight Blue
                    break;
                case 5:
                    color = ofColor(0x2A52BE); // Cerulean
                    break;
            }
            color.a = 255;  // Ensuring full opacity
            ofSetColor(color);
            ofDrawCircle(x + width/2, y + height/2, radius);
        }
    }
}
