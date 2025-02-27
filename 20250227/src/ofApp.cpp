#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    cam.setDistance(300);
    ofEnableDepthTest();
    ofEnableBlendMode(OF_BLENDMODE_ADD); // Additive blending for glowing effect
}

//--------------------------------------------------------------
void ofApp::update(){
    time += 0.02; // Increment time for animation
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();

    int numPoints = 3000; // Increase points for more details
    float baseRadius = 150; // Larger shape for visual impact

    ofPushMatrix();
    ofRotateYDeg(time * 10); // Add slow rotation for beauty

    for(int i = 0; i < numPoints; i++){
        float theta = ofMap(i, 0, numPoints, 0, TWO_PI);
        float phi = ofNoise(i * 0.003, time * 0.03) * TWO_PI;

        float radius = baseRadius * (0.85 + 0.15 * sin(time * 0.5 + i * 0.008)); // Subtle pulsation

        float x = radius * sin(theta) * cos(phi);
        float y = radius * sin(theta) * sin(phi);
        float z = radius * cos(theta);

        float noise = ofNoise(x * 0.01, y * 0.01, z * 0.01, time * 0.1);
        x *= noise;
        y *= noise;
        z *= noise;

        float size = ofMap(noise, 0, 1, 2, 5); // Adjust sphere size dynamically
        float hue = fmod(time * 10 + ofMap(noise, 0, 1, 120, 255), 255); // Cycling color effect
        float alpha = ofMap(noise, 0, 1, 150, 255); // Dynamic transparency

        ofSetColor(ofColor::fromHsb(hue, 255, 255, alpha)); // Beautiful gradient colors
        ofDrawSphere(x, y, z, size);
    }

    ofPopMatrix();
    cam.end();
}
