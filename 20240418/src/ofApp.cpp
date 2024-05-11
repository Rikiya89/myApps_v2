#include "ofApp.h"

void ofApp::setup(){
    ofSetBackgroundColor(ofColor::black);
    initialRadius = 100.0;
    generations = 6;
    ofSetCircleResolution(100);
    animationPhase = 0.0;
    rotationSpeed = 10.0;
    scale = 1.0;

    ofEnableSmoothing(); // Enhances the visual quality by smoothing shapes
    ofEnableAlphaBlending(); // Allows for transparency blending
}

void ofApp::update(){
    float targetPhaseIncrement = 0.05;
    animationPhase += targetPhaseIncrement;
    scale = 1.0 + 0.1 * sin(animationPhase);
    rotationSpeed = 10 + 5 * sin(animationPhase * 2);

    if(animationPhase > TWO_PI) {
        animationPhase -= TWO_PI;
    }
}

void ofApp::draw(){
    drawBackground();
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotateDeg(ofGetElapsedTimef() * rotationSpeed);
    ofScale(scale, scale);

    float dynamicRadius = initialRadius + 20 * sin(animationPhase);
    drawFlowerOfLife(0, 0, dynamicRadius, generations, 180);

    ofPopMatrix();

    drawVignette();
}

void ofApp::drawFlowerOfLife(float x, float y, float radius, int generations, float alpha){
    if (generations < 1 || alpha <= 0) return;

    float hue = fmod(90 + 120 * (animationPhase + generations), 255);
    ofColor color = ofColor::fromHsb(hue, 180, 180, alpha); // Adjusted for softer color
    ofSetColor(color, alpha);

    // Adding dynamic lighting effects
    float pulseEffect = 1.0 + 0.1 * sin(animationPhase + generations);
    float effectiveRadius = radius * pulseEffect;
    ofDrawCircle(x, y, effectiveRadius);

    ofSetLineWidth(2 + 0.5 * generations);
    ofDrawCircle(x, y, effectiveRadius);

    float angle = TWO_PI / 6;
    float nextAlpha = alpha * 0.8;
    for (int i = 0; i < 6; i++) {
        float nx = x + effectiveRadius * cos(angle * i);
        float ny = y + effectiveRadius * sin(angle * i);
        drawFlowerOfLife(nx, ny, radius * 0.5, generations - 1, nextAlpha);
    }
}

void ofApp::drawBackground(){
    // More atmospheric background with gradient lighting
    ofColor centerColor = ofColor::fromHsb(fmod(255 * sin(animationPhase), 255), 180, 180, 255);
    ofColor edgeColor = ofColor(25, 25, 30, 255);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
}

void ofApp::drawVignette(){
    // Draw a vignette to focus attention
    ofPushStyle();
    ofSetColor(0, 0, 0, 100);  // Adjust alpha for stronger/weaker effect
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
}
