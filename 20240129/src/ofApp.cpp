#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);

    numCircles = 20; // More circles for additional complexity
    baseRadius = 300.0; // Increase the base radius

    for(int i = 0; i < numCircles; i++) {
        float hue = ofMap(i, 0, numCircles, 0, 255);
        colors.push_back(ofColor::fromHsb(hue, 255, 255, 150)); // More transparency in colors
    }

    time = 0.0;
    rotationSpeed = 0.03; // Slower, more graceful rotation
}

//--------------------------------------------------------------
void ofApp::update(){
    time += 1.0 / 60.0;
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Dynamic background with subtle color changes
    ofColor bgColor = ofColor::fromHsb(sin(time * 0.1) * 128 + 127, 180, 30);
    ofBackground(bgColor);

    drawSacredGeometry();
}

//--------------------------------------------------------------
void ofApp::drawSacredGeometry(){
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

    // Multiple layers for intricate patterns
    drawGeometryLayer(baseRadius, time * rotationSpeed);
    drawGeometryLayer(baseRadius * 0.6, -time * rotationSpeed * 2.0);
    drawGeometryLayer(baseRadius * 0.4, time * rotationSpeed * 2.8);

    ofPopMatrix();
}

void ofApp::drawGeometryLayer(float radius, float rotation){
    float animatedRadius = radius + 40 * sin(time * 2); // More dynamic radius change

    for (int i = 0; i < numCircles; i++) {
        float angle = TWO_PI / numCircles * i + rotation;
        float x = cos(angle) * animatedRadius;
        float y = sin(angle) * animatedRadius;

        // Dynamic circle sizes
        float circleSize = 20 + 15 * sin(time + i * 0.5);

        ofSetColor(colors[i]);
        ofDrawCircle(x, y, circleSize);

        // Enhanced line drawing for a more fluid look
        for (int j = 0; j < numCircles; j++) {
            if (i != j) {
                float nextAngle = TWO_PI / numCircles * j + rotation;
                float nextX = cos(nextAngle) * animatedRadius;
                float nextY = sin(nextAngle) * animatedRadius;

                ofColor lineColor = colors[i].getLerped(colors[j], 0.5);
                lineColor.a = 100; // More transparency for a subtler effect
                ofSetColor(lineColor);
                ofDrawLine(x, y, nextX, nextY);
            }
        }
    }
}
