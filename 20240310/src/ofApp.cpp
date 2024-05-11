#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
    time += 0.01; // Slower increment for time
    growth = (sin(time) + 1) / 2; // Oscillate growth between 0 and 1
}


//--------------------------------------------------------------
void ofApp::draw(){
    // Draw a subtle background gradient
    ofColor centerColor = ofColor(255, 240, 230);
    ofColor edgeColor = ofColor(230, 230, 250);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);

    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);


    int numLayers = 15;
    float maxRadius = 360;

    for (int i = numLayers - 1; i >= 0; i--) { // Render from back to front
        float norm = (float)i / (numLayers - 1);
        float radius = ofLerp(0, maxRadius, norm * growth);
        float lineWidth = ofMap(i, 0, numLayers, 1, 5); // Thicker lines for closer layers
        ofSetLineWidth(lineWidth);

        // Enhanced color palette with time-based hue variation
        float hue = ofMap(sin(time / 2 + i), -1, 1, 0, 255);
        float saturation = 200;
        float brightness = ofMap(growth, 0, 1, 180, 255);
        ofColor color = ofColor::fromHsb(hue, saturation, brightness);

        // Apply a scaling factor for depth effect
        float scaleFactor = ofMap(i, 0, numLayers - 1, 0.5, 1.0);
        ofPushMatrix();
        ofScale(scaleFactor, scaleFactor);

        for (int j = 0; j < 3; j++) {
            float layeredRadius = radius * (0.8 + 0.2 * j / 2);
            float alpha = 255 * (1 - (float)j / 3);
            ofSetColor(color, alpha);

            ofPushMatrix();
            float angle = ofMap(growth, 0, 1, 0, 180) * norm * (j + 1); // More exaggerated rotation
            ofRotateDeg(angle);
            drawLayer(layeredRadius * growth, i, numLayers); // Apply growth factor to layer radius
            ofPopMatrix();
        }
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::drawLayer(float radius, int layerIndex, int totalLayers){
    int baseNumPoints = 5;
    int maxNumPoints = 20;
    float norm = (float)layerIndex / (totalLayers - 1);
    int numPoints = baseNumPoints + norm * (maxNumPoints - baseNumPoints) * growth;

    float angleStep = TWO_PI / numPoints;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numPoints; i++) {
        float x = radius * cos(angleStep * i);
        float y = radius * sin(angleStep * i);
        glVertex2f(x, y);
    }
    glEnd();
}


