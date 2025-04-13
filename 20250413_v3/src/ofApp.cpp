#include "ofApp.h"

void ofApp::setup(){
    ofSetWindowShape(720, 1080);
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetCircleResolution(64);

    gridSizeX = 30;
    gridSizeY = 40;
    spacing = 25;

    int total = gridSizeX * gridSizeY;
    points.resize(total);
    sizes.resize(total);
}

void ofApp::update(){
    float time = ofGetElapsedTimef();

    glm::vec2 center = glm::vec2(gridSizeX / 2, gridSizeY / 2);

    for (int x = 0; x < gridSizeX; x++) {
        for (int y = 0; y < gridSizeY; y++) {
            int idx = y * gridSizeX + x;

            glm::vec2 pos2D = glm::vec2(x, y);
            float distToCenter = glm::distance(pos2D, center);

            float z = sin(distToCenter * 0.4 - time * 2.0) * 60;

            points[idx] = glm::vec3(x * spacing, y * spacing, z);

            // Sacred pulse
            sizes[idx] = ofMap(sin(time * 1.2 + distToCenter * 0.2), -1, 1, 3, 8);
        }
    }
}

void ofApp::draw(){
    cam.begin();

    ofPushMatrix();
    ofTranslate(-gridSizeX * spacing / 2, -gridSizeY * spacing / 2, 0);

    // 🌌 Sacred Constellation Lines
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 6; j < points.size(); j += 12) {
            float dist = glm::distance(points[i], points[j]);
            if (dist < 120) {
                float alpha = ofMap(dist, 0, 120, 120, 0);
                ofSetColor(255, alpha);
                ofDrawLine(points[i], points[j]);
            }
        }
    }

    // 🌟 Glowing Spheres with Depth Fog
    for (int i = 0; i < points.size(); i++) {
        float depthFade = ofMap(points[i].z, -100, 100, 100, 255);
        ofSetColor(255, depthFade);

        // soft glow with layered drawing
        ofDrawSphere(points[i], sizes[i]);
        ofSetColor(255, depthFade * 0.2);
        ofDrawSphere(points[i], sizes[i] + 4);
    }

    ofPopMatrix();
    cam.end();
}
