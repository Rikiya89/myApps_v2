#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0); // Black background
    ofSetFrameRate(60);
    ofEnableDepthTest(); // Enable depth testing for 3D rendering
    ofEnableSmoothing(); // Enable smoothing for better visuals

    // Setting up light
    light.setup();
    light.setPosition(300, 300, 300);

    // Setting up GUI
    gui.setup();
    gui.add(radius.set("Radius", 300, 100, 500));
    gui.add(numPoints.set("Num Points", 8, 3, 20));
    gui.add(layers.set("Layers", 4, 1, 10));
    gui.add(rotationSpeed.set("Rotation Speed", 0.2, 0, 2));
    gui.add(oscillation.set("Oscillation", 1.0, 0, 3));
    gui.add(baseColor.set("Base Color", ofColor(128, 128, 255), ofColor(0, 0), ofColor(255, 255)));
    gui.add(animate.set("Animate", true));

    createGeometry();
    rotation = 0;
    time = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    if(animate) {
        rotation += rotationSpeed; // Update rotation
        time += 0.1f; // Faster color change
    }
    createGeometry();
}

//--------------------------------------------------------------
void ofApp::draw(){
    easyCam.begin();
    light.enable();

    ofSetLineWidth(3); // Thicker lines

    // Pulsating effect
    float pulse = sin(ofGetElapsedTimef()) * 0.5 + 1.0; // Creates a pulsating effect between 0.5 and 1.5

    ofPushMatrix();
    ofRotateYDeg(rotation);

    // Enhanced color and line drawing with pulsating effect
    for(size_t i = 0; i < points.size(); i++){
        for(size_t j = i + 1; j < points.size(); j++){
            float hue = fmod((baseColor->getHue() + time * 10 + (i + j) * 10), 255);
            ofSetColor(ofColor::fromHsb(hue, 255, 255));
            ofDrawLine(points[i] * pulse, points[j] * pulse); // Apply pulsating effect
        }
    }

    ofPopMatrix();

    light.disable();
    easyCam.end();

    gui.draw();
}

//--------------------------------------------------------------
void ofApp::createGeometry(){
    points.clear();
    float angleStep = TWO_PI / numPoints;
    float layerHeight = 60.0; // Height between each layer

    for(int layer = 0; layer < layers; layer++){
        for(int i = 0; i < numPoints; i++){
            float angle = angleStep * i + ofDegToRad(360.0 / layers * layer) + sin(time * oscillation) * 0.5;
            float x = cos(angle) * radius;
            float y = sin(angle) * radius;
            points.push_back(ofPoint(x, y, layer * layerHeight - layers * layerHeight / 2));
        }
    }
}
