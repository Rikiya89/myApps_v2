#include "ofApp.h"

void ofApp::setup() {
    ofSetWindowShape(1280, 720);
    cam.setDeviceID(0);
    cam.setDesiredFrameRate(30);
    cam.initGrabber(640, 480);

    colorImg.allocate(cam.getWidth(), cam.getHeight());
    grayImg.allocate(cam.getWidth(), cam.getHeight());
    blurredImg.allocate(cam.getWidth(), cam.getHeight());
    prevGrayImg.allocate(cam.getWidth(), cam.getHeight());
    diffImg.allocate(cam.getWidth(), cam.getHeight());

    animationOffset = 0.0;
    colorOffset = 0.0;
    blurAmount = 30;  // Increased blur strength for a softer look

    // Setup particle system
    numParticles = 800;  // More particles for a richer effect
    particles.setMode(OF_PRIMITIVE_POINTS);
    for (int i = 0; i < numParticles; i++) {
        particles.addVertex(ofVec3f(ofRandomWidth(), ofRandomHeight(), 0));
        particles.addColor(ofColor::fromHsb(ofRandom(255), 255, 255, 100));
    }
    glPointSize(2);  // Smaller particles for subtlety
}

void ofApp::update() {
    cam.update();

    if (cam.isFrameNew()) {
        colorImg.setFromPixels(cam.getPixels());
        grayImg = colorImg;
        grayImg.blurGaussian(blurAmount);

        // Calculate motion by finding the difference between current and previous frame
        diffImg.absDiff(grayImg, prevGrayImg);
        diffImg.threshold(30);

        prevGrayImg = grayImg;  // Update the previous frame

        // Update particle positions based on motion
        for (int i = 0; i < numParticles; ++i) {
            ofVec3f vert = particles.getVertex(i);
            int x = ofClamp(vert.x, 0, diffImg.getWidth() - 1);
            int y = ofClamp(vert.y, 0, diffImg.getHeight() - 1);
            if (diffImg.getPixels()[y * diffImg.getWidth() + x] > 0) {
                vert.x += ofRandom(-2, 2);
                vert.y += ofRandom(-2, 2);
            } else {
                vert.x += ofSignedNoise(vert.x * 0.01, vert.y * 0.01, animationOffset) * 0.5;
                vert.y += ofSignedNoise(vert.y * 0.01, vert.x * 0.01, animationOffset) * 0.5;
            }
            particles.setVertex(i, vert);
        }
    }

    // Update animation offset for smooth motion
    animationOffset += 0.01;
    if (animationOffset > TWO_PI) {
        animationOffset = 0.0;
    }

    // Update color offset for transitions
    colorOffset += 0.002;
    if (colorOffset > 1.0) {
        colorOffset = 0.0;
    }
}

void ofApp::draw() {
    drawGradientBackground();  // Draw gradient background

    ofSetColor(255);
    blurredImg.draw(0, 0);  // Draw the blurred image

    for (int i = 0; i < grayImg.getWidth(); i += 50) {
        for (int j = 0; j < grayImg.getHeight(); j += 50) {
            float brightness = blurredImg.getPixels()[j * int(blurredImg.getWidth()) + i];
            float size = ofMap(brightness, 0, 255, 5, 50);

            ofColor color = interpolateColor(colorOffset + brightness / 255.0);
            ofSetColor(color);

            if (brightness > 170) {
                drawCirclePattern(i, j, size);
            } else if (brightness > 85) {
                drawIslamicPattern(i, j, size);
            } else {
                drawSpiralPattern(i, j, size);
            }
        }
    }

    // Draw particles
    ofSetColor(255, 255, 255, 80); // Slight transparency for subtle effect
    particles.draw();
}

void ofApp::drawGradientBackground() {
    ofColor color1 = ofColor::fromHsb(fmod(colorOffset * 255, 255), 150, 200);
    ofColor color2 = ofColor::fromHsb(fmod((colorOffset + 0.5) * 255, 255), 150, 200);

    ofBackgroundGradient(color1, color2, OF_GRADIENT_LINEAR);
}

ofColor ofApp::interpolateColor(float t) {
    // Use a color gradient with smooth transitions
    ofColor startColor(150, 100, 255);
    ofColor midColor(255, 150, 150);
    ofColor endColor(255, 200, 100);

    if (t < 0.5) {
        return startColor.getLerped(midColor, t * 2);
    } else {
        return midColor.getLerped(endColor, (t - 0.5) * 2);
    }
}

void ofApp::drawCirclePattern(float x, float y, float size) {
    for (int i = 0; i < 5; ++i) {
        float radius = size * (i + 1) / 5;
        float offset = animationOffset + i * 0.1;
        float xOffset = cos(offset) * 5;
        float yOffset = sin(offset) * 5;
        ofSetColor(ofColor(255, 255, 255, 100)); // Add a glow effect
        ofDrawCircle(x + xOffset, y + yOffset, radius);
    }
}

void ofApp::drawSpiralPattern(float x, float y, float size) {
    float angleStep = 360.0 / 10;
    float radius = size / 2;

    for (int i = 0; i < 10; ++i) {
        float angle = angleStep * i + animationOffset * 10;
        float nextAngle = angleStep * (i + 1) + animationOffset * 10;

        float x1 = x + cos(ofDegToRad(angle)) * radius;
        float y1 = y + sin(ofDegToRad(angle)) * radius;
        float x2 = x + cos(ofDegToRad(nextAngle)) * radius;
        float y2 = y + sin(ofDegToRad(nextAngle)) * radius;

        ofSetColor(ofColor(255, 255, 255, 150)); // Add a glow effect
        ofDrawLine(x1, y1, x2, y2);
        radius += size / 20;
    }
}

void ofApp::drawIslamicPattern(float x, float y, float size) {
    float angleStep = 30.0; // Increased complexity for intricate pattern
    float radius = size * 0.6;

    for (int i = 0; i < 12; ++i) {
        float angle = ofDegToRad(angleStep * i + animationOffset * 20);
        float x1 = x + cos(angle) * radius;
        float y1 = y + sin(angle) * radius;

        float nextAngle = ofDegToRad(angleStep * (i + 1) + animationOffset * 20);
        float x2 = x + cos(nextAngle) * radius;
        float y2 = y + sin(nextAngle) * radius;

        ofSetColor(ofColor(255, 255, 255, 200)); // Add a glow effect
        ofDrawLine(x, y, x1, y1);
        ofDrawLine(x1, y1, x2, y2);

        // Nested smaller star with more points
        float innerRadius = radius * 0.5;
        float innerX = x + cos(angle) * innerRadius;
        float innerY = y + sin(angle) * innerRadius;
        float innerNextX = x + cos(nextAngle) * innerRadius;
        float innerNextY = y + sin(nextAngle) * innerRadius;

        ofDrawLine(x1, y1, innerX, innerY);
        ofDrawLine(innerX, innerY, innerNextX, innerNextY);
    }
}
