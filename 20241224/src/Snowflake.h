#pragma once
#include "ofMain.h"

class Snowflake {
public:
    float x, y, speed, size, rotation, rotationSpeed;
    ofColor color;

    Snowflake(float x, float y, float speed, float size, float rotationSpeed, ofColor color)
        : x(x), y(y), speed(speed), size(size), rotation(0), rotationSpeed(rotationSpeed), color(color) {}

    void update() {
        y += speed;
        rotation += rotationSpeed;
        if (y > ofGetHeight()) {
            y = 0; // Reset to top
            x = ofRandom(ofGetWidth()); // Randomize horizontal position
        }
    }

    void draw() {
        // Draw trails
        ofSetColor(color, 50); // Faint glow for the trail
        ofDrawCircle(x, y - size, size / 3);

        // Draw snowflake
        ofPushMatrix();
        ofTranslate(x, y);
        ofRotateDeg(rotation);
        drawSnowflakePattern(size);
        ofPopMatrix();
    }

private:
    void drawSnowflakePattern(float radius) {
        ofSetColor(color); // Snowflake color
        for (int i = 0; i < 6; i++) { // 6 symmetric branches
            ofPushMatrix();
            ofRotateDeg(i * 60); // Rotate branches
            drawBranch(radius);
            ofPopMatrix();
        }
    }

    void drawBranch(float length) {
        ofDrawLine(0, 0, 0, -length); // Main branch
        ofDrawCircle(0, -length, 4); // Circle at branch tip
        for (float offset = length / 4; offset < length; offset += length / 4) {
            ofDrawLine(0, -offset, 5, -offset - 5); // Left
            ofDrawLine(0, -offset, -5, -offset - 5); // Right
        }
    }
};
