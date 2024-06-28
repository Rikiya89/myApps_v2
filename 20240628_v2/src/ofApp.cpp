#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(10); // Darker background for better glow effect
    ofEnableDepthTest();
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    ofEnableLighting();

    // Set up lighting
    light.setPointLight();
    light.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 600);
    light.setDiffuseColor(ofColor(255)); // Bright white light
    light.setSpecularColor(ofColor(255)); // Specular highlights
    light.enable();

    // Load image
    image.load("sun_flower.jpg");
    image.resize(300, 300); // Resize image for easier processing
    image.setImageType(OF_IMAGE_COLOR);

    // Create point cloud from image
    for (int y = 0; y < image.getHeight(); y++) {
        for (int x = 0; x < image.getWidth(); x++) {
            ofColor color = image.getColor(x, y);
            float brightness = color.getBrightness();
            ofVec3f point(x - image.getWidth() / 2, y - image.getHeight() / 2, ofMap(brightness, 0, 255, -100, 100));
            points.push_back(point);
            colors.push_back(ofFloatColor(color)); // Store the color
        }
    }

    // Create flower of life pattern
    float radius = 30;
    int layers = 6;
    for (int i = 0; i < layers; i++) {
        float r = radius * (i + 1);
        for (int j = 0; j < 6; j++) {
            float angle = ofDegToRad(j * 60);
            float x = r * cos(angle);
            float y = r * sin(angle);
            flowerOfLife.push_back(ofVec3f(x, y, 0));
        }
    }

    time = 0.0; // Initialize time variable
}

//--------------------------------------------------------------
void ofApp::update(){
    time += ofGetLastFrameTime(); // Update time variable with elapsed time
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofPushMatrix();
    // Animate rotation and spiral of the flower of life
    ofRotateYDeg(time * 20.0); // Rotate around Y-axis
    ofTranslate(0, 0, 100 * sin(time * 0.5)); // Spiral effect

    // Add orbiting animation
    float orbitRadius = 50;
    float orbitSpeed = 0.5;
    float orbitX = orbitRadius * cos(time * orbitSpeed);
    float orbitY = orbitRadius * sin(time * orbitSpeed);
    ofTranslate(orbitX, orbitY);

    // Draw point cloud with colors and pulsating animation
    for (size_t i = 0; i < points.size(); i++) {
        ofSetColor(colors[i]);
        float scale = 1.0 + 0.5 * sin(time * 2.0 + points[i].x * 0.1 + points[i].y * 0.1);
        ofDrawSphere(points[i], scale);
    }

    // Draw flower of life with gradients, rotating and color cycling animation
    for (size_t i = 0; i < flowerOfLife.size(); i++) {
        float hue = fmod(ofMap(i, 0, flowerOfLife.size(), 0, 255) + time * 40, 255);
        ofSetColor(ofColor::fromHsb(hue, 255, 255));
        ofDrawSphere(flowerOfLife[i], 5 + 2 * sin(time * 2.0 + i));
        for (size_t j = 0; j < flowerOfLife.size(); j++) {
            if (i != j) {
                ofSetColor(ofColor::fromHsb(hue, 255, 255, 127));
                ofDrawLine(flowerOfLife[i], flowerOfLife[j]);
            }
        }
    }

    // Draw glow effect
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (size_t i = 0; i < flowerOfLife.size(); i++) {
        float hue = fmod(ofMap(i, 0, flowerOfLife.size(), 0, 255) + time * 40, 255);
        ofSetColor(ofColor::fromHsb(hue, 255, 255, 100));
        ofDrawSphere(flowerOfLife[i], 8 + 4 * sin(time * 2.0 + i));
    }
    ofDisableBlendMode();

    ofPopMatrix();
    cam.end();
}
