#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0); // Set the background to black
    ofSetCircleResolution(100); // Higher resolution for smoother circles
    ofSetFrameRate(60); // Set a comfortable frame rate
}

void ofApp::update(){
    // Update logic can be added here if needed
}

void ofApp::draw(){
    int centerX = ofGetWidth() / 2;
    int centerY = ofGetHeight() / 2;
    float elapsedTime = ofGetElapsedTimef(); // Declare elapsedTime here for use in draw

    // Now we can use elapsedTime safely within this function
    float size = 10.0 + sin(elapsedTime * 0.5) * 5.0;
    float goldenRatio = 1.61803398875;
    int n = 10 + (sin(elapsedTime * 0.2) * 5);
    drawFibonacciSpirals(centerX, centerY, n, size, goldenRatio, elapsedTime); // Pass elapsedTime as an argument

    int numStars = 6 + (sin(elapsedTime * 0.7) * 5);
    drawStars(centerX, centerY, 250, numStars, 8, elapsedTime); // Pass elapsedTime as an argument
}

// Notice we now include elapsedTime as a parameter for these functions
void ofApp::drawFibonacciSpirals(int x, int y, int n, float size, float goldenRatio, float elapsedTime){
    float layerOffset = 5.0; // Offset between layers for depth
    int numberOfLayers = 3; // Number of layers to create depth
    for(int layer = 0; layer < numberOfLayers; layer++){
        float currentSize = size + layer * layerOffset;
        float a = currentSize;
        float b = currentSize;
        int totalSpirals = n * (1 + layer); // More spirals in each subsequent layer

        for(int i = 0; i < totalSpirals; i++){
            float hue = fmod(64 * i + elapsedTime * 10, 255);
            float alpha = 255 * (1 - (float)layer / numberOfLayers); // Decrease alpha for distant layers
            ofColor spiralColor;
            spiralColor.setHsb(hue, 255, 255, alpha);
            ofSetColor(spiralColor);

            // Adjust line width based on layer
            ofSetLineWidth(1 + layer);

            ofPolyline polyline;
            float angleIncrement = 360.0 / totalSpirals;
            float angle = angleIncrement * i;
            float endAngle = angle + 360; // Full circle for each spiral

            for(float theta = angle; theta < endAngle; theta += 0.1){
                float rad = ofDegToRad(theta);
                float r = a + b * rad;
                float xSpiral = x + cos(rad) * r;
                float ySpiral = y + sin(rad) * r;
                polyline.addVertex(ofPoint(xSpiral, ySpiral));
            }

            a += b;
            b *= goldenRatio;
            polyline.draw();
        }
    }
}


void ofApp::drawStars(int centerX, int centerY, int radius, int numStars, int layers, float elapsedTime){
    float angleStep = 360.0 / numStars;
    for(int i = 0; i < layers; i++){
        for(int j = 0; j < numStars; j++){
            float hue = fmod(255 * elapsedTime / 4 + j * 45, 255);
            ofColor starColor;
            starColor.setHsb(hue, 200, 255, 255);
            ofSetColor(starColor);

            float angle = ofDegToRad(j * angleStep + elapsedTime * 40);
            float x = centerX + cos(angle) * (radius + i * 15);
            float y = centerY + sin(angle) * (radius + i * 15);
            drawStar(x, y, 8, 30, 60);
        }
    }
}

void ofApp::drawStar(float x, float y, int points, float innerRadius, float outerRadius){
    ofPolyline line;
    line.clear();
    for(int i = 0; i <= points; i++){
        float angle = ofDegToRad((360 / points) * i);
        float outerX = x + cos(angle) * outerRadius;
        float outerY = y + sin(angle) * outerRadius;
        line.addVertex(outerX, outerY);
        angle += ofDegToRad((360 / (points * 2)));
        float innerX = x + cos(angle) * innerRadius;
        float innerY = y + sin(angle) * innerRadius;
        line.addVertex(innerX, innerY);
    }
    line.close();
    line.draw();
}
