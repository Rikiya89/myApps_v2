#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofEnableSmoothing();
    ofSetLineWidth(1.2);

    timeScale = 0.3;

    float size = 180;
    points = {
        {-size, -size, -size}, { size, -size, -size},
        {-size,  size, -size}, { size,  size, -size},
        {-size, -size,  size}, { size, -size,  size},
        {-size,  size,  size}, { size,  size,  size}
    };
}

void ofApp::update(){}

void ofApp::draw(){
    ofPushStyle();
    ofDisableDepthTest();
    ofMesh gradient;
    gradient.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    gradient.addVertex(ofVec3f(0, 0, -100));
    gradient.addColor(ofColor(50, 30, 60)); // top
    gradient.addVertex(ofVec3f(ofGetWidth(), 0, -100));
    gradient.addColor(ofColor(50, 30, 60));
    gradient.addVertex(ofVec3f(0, ofGetHeight(), -100));
    gradient.addColor(ofColor(10, 5, 15)); // bottom
    gradient.addVertex(ofVec3f(ofGetWidth(), ofGetHeight(), -100));
    gradient.addColor(ofColor(10, 5, 15));
    gradient.draw();
    ofEnableDepthTest();
    ofPopStyle();

    ofPushStyle();
    ofDisableDepthTest();
    ofMesh fullBg;
    fullBg.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    fullBg.addVertex(ofVec3f(0, 0, -110));
    fullBg.addColor(ofColor(50, 30, 60));
    fullBg.addVertex(ofVec3f(ofGetWidth(), 0, -110));
    fullBg.addColor(ofColor(50, 30, 60));
    fullBg.addVertex(ofVec3f(0, ofGetHeight(), -110));
    fullBg.addColor(ofColor(10, 5, 15));
    fullBg.addVertex(ofVec3f(ofGetWidth(), ofGetHeight(), -110));
    fullBg.addColor(ofColor(10, 5, 15));
    fullBg.draw();
    ofEnableDepthTest();
    ofPopStyle();

    cam.begin();
    float time = ofGetElapsedTimef() * timeScale;

    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofPushMatrix();
    ofRotateDeg(time * 20, 0.3, 1.0, 0.5);

    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            ofVec3f p1 = points[i];
            ofVec3f p2 = points[j];
            float offset = sin(time + i * 0.5 + j * 0.7) * 15;
            ofVec3f mid = (p1 + p2) * 0.5 + ofVec3f(0, offset, 0);

            ofSetColor(200 + 55 * sin(time + i), 180 + 50 * cos(time + j), 255, 100);
            ofDrawLine(p1, mid);
            ofDrawLine(mid, p2);
        }
    }
    ofPopMatrix();

    drawSacredForm(time);
    drawSparkles(time);

    ofDisableBlendMode();
    ofPopStyle();
    cam.end();
}

void ofApp::drawSacredForm(float time) {
    ofPushMatrix();
    ofRotateDeg(time * 30, sin(time * 0.3), cos(time * 0.2), 0.5);

    float baseR = 140;
    ofNoFill();
    ofSetColor(255, 220, 240, 120);
    ofDrawSphere(0, 0, 0, baseR);

    ofSetColor(180, 220, 255, 150);
    drawTorus(baseR * 0.6, 16, 36, 12);

    for (int i = 0; i < 10; i++) {
        float angle = TWO_PI * i / 10.0;
        float x = cos(angle + time * 0.5) * baseR;
        float y = sin(angle + time * 0.5) * baseR;
        float z = sin(time + i) * 50;

        ofPushMatrix();
        ofTranslate(x, y, z);
        ofRotateDeg(time * 50 + i * 36, 1.0, 1.0, 0.5);
        ofDrawBox(0, 0, 0, 15);
        ofPopMatrix();
    }

    ofPopMatrix();
}

void ofApp::drawTorus(float radius, float tubeRadius, int sides, int rings) {
    for (int i = 0; i < sides; i++) {
        float theta = TWO_PI * i / sides;
        float nextTheta = TWO_PI * (i + 1) / sides;

        for (int j = 0; j < rings; j++) {
            float phi = TWO_PI * j / rings;
            float nextPhi = TWO_PI * (j + 1) / rings;

            ofVec3f p1(
                (radius + tubeRadius * cos(phi)) * cos(theta),
                (radius + tubeRadius * cos(phi)) * sin(theta),
                tubeRadius * sin(phi));

            ofVec3f p2(
                (radius + tubeRadius * cos(nextPhi)) * cos(theta),
                (radius + tubeRadius * cos(nextPhi)) * sin(theta),
                tubeRadius * sin(nextPhi));

            ofVec3f p3(
                (radius + tubeRadius * cos(phi)) * cos(nextTheta),
                (radius + tubeRadius * cos(phi)) * sin(nextTheta),
                tubeRadius * sin(phi));

            ofSetColor(220 + 20 * sin(phi), 190 + 30 * cos(theta), 255, 80);
            ofDrawLine(p1, p2);
            ofDrawLine(p1, p3);
        }
    }
}

void ofApp::drawSparkles(float time) {
    ofPushMatrix();
    ofRotateDeg(time * 20, 0.5, 1, 0);

    for (int i = 0; i < 80; i++) {
        float angle = time * 0.3 + i * 0.4;
        float baseRadius = 160 + 40 * sin(time * 0.6 + i);
        float wave = 15 * sin(time * 2.0 + i * 0.5);
        float radius = baseRadius + wave;

        float x = cos(angle) * radius;
        float y = sin(angle) * radius;
        float z = sin(time * 0.8 + i * 0.2) * 90 + 10 * cos(time + i * 0.3);

        float alpha = 150 + 100 * sin(time * 1.5 + i * 0.6);
        float size = 2.0 + 1.8 * sin(time * 2.0 + i * 0.7);

        ofSetColor(255, 255, 255, ofClamp(alpha, 80, 255));
        ofDrawSphere(x, y, z, size);
    }

    ofPopMatrix();
}
