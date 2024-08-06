#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(20, 20, 40); // Set the background to a deep, calming blue

    numLayers = 25; // Number of layers for radial symmetry
    baseRadius = 15.0; // Base radius for the smallest shape
    numShapes = 16; // Number of shapes per layer for intricate symmetry
    rotationSpeed = 0.008; // Slow rotation speed for a calming effect
    globalRotation = 0; // Initialize global rotation angle

    for (int i = 0; i < numLayers; i++) {
        float radius = baseRadius * (i + 1);
        radii.push_back(radius);

        // Generate a smooth gradient of soft, harmonious colors
        ofColor color = ofColor::fromHsb(ofMap(i, 0, numLayers - 1, 140, 250), 180, 220);
        colors.push_back(color);

        // Set a gentle speed for pulsating animation
        float speed = ofRandom(0.01, 0.02);
        speeds.push_back(speed);

        // Create random offsets for each layer to vary their movements
        offsets.push_back(ofRandom(0, TWO_PI));
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    for (int i = 0; i < numLayers; i++) {
        // Update radii to create a gentle pulsating effect
        radii[i] += sin(ofGetElapsedTimef() * speeds[i] + offsets[i]) * 0.5;
    }

    // Update global rotation for a dynamic overall effect
    globalRotation += rotationSpeed;
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofEnableBlendMode(OF_BLENDMODE_ADD); // Enable additive blending for glow effect
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotateDeg(globalRotation); // Apply global rotation to the entire scene

    for (int i = 0; i < numLayers; i++) {
        // Reduce transparency towards the center
        ofSetColor(colors[i], 50 + (i * 5)); // Increase transparency with layer index

        ofPushMatrix();
        ofRotateDeg(ofGetElapsedTimef() * rotationSpeed * (i + 1)); // Apply slow, layered rotation

        // Draw intricate radial symmetry with complex geometric patterns
        for (int j = 0; j < numShapes; j++) {
            ofRotateDeg(360.0 / numShapes); // Rotate for equal spacing

            // Create star and rosette patterns using complex interlocking shapes
            float angleIncrement = TWO_PI / numShapes;
            float currentAngle = angleIncrement * j;

            float x1 = radii[i] * cos(currentAngle);
            float y1 = radii[i] * sin(currentAngle);
            float x2 = radii[i] * cos(currentAngle + angleIncrement / 3);
            float y2 = radii[i] * sin(currentAngle + angleIncrement / 3);
            float x3 = radii[i] * cos(currentAngle + 2 * angleIncrement / 3);
            float y3 = radii[i] * sin(currentAngle + 2 * angleIncrement / 3);

            float innerRadius = radii[i] * 0.6;
            float x4 = innerRadius * cos(currentAngle + angleIncrement / 6);
            float y4 = innerRadius * sin(currentAngle + angleIncrement / 6);
            float x5 = innerRadius * cos(currentAngle + 5 * angleIncrement / 6);
            float y5 = innerRadius * sin(currentAngle + 5 * angleIncrement / 6);

            ofDrawLine(x1, y1, x4, y4);
            ofDrawLine(x4, y4, x2, y2);
            ofDrawLine(x2, y2, x5, y5);
            ofDrawLine(x5, y5, x3, y3);
            ofDrawLine(x3, y3, x1, y1);

            // Add smaller decorative elements for more complexity
            ofDrawCircle((x1 + x4) / 2, (y1 + y4) / 2, innerRadius * 0.1);
        }

        ofPopMatrix();
    }

    ofDisableBlendMode(); // Disable additive blending
}
