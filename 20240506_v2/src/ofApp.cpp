#include "ofApp.h"

void ofApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);
    cam.setup(1280, 720);
    contourFinder.setMinAreaRadius(10);
    contourFinder.setMaxAreaRadius(150);
    colorImg.allocate(cam.getWidth(), cam.getHeight());
    grayImage.allocate(cam.getWidth(), cam.getHeight());
    showLabels = true;
    ofEnableSmoothing();
    ofSetFrameRate(60);  // Increase the frame rate for smoother animations
}

void ofApp::update() {
    cam.update();
    if (cam.isFrameNew()) {
        colorImg.setFromPixels(cam.getPixels());
        grayImage = colorImg;
        grayImage.blur(10);
        contourFinder.findContours(grayImage);
    }
}

void ofApp::draw() {
    ofBackgroundGradient(ofColor(10, 10, 10), ofColor(0, 0, 0), OF_GRADIENT_CIRCULAR);  // Dynamic gradient background

    for (int i = 0; i < contourFinder.size(); i++) {
        vector<cv::Point> points = contourFinder.getContour(i);
        ofPath path;
        path.setFilled(true);
        path.setFillColor(ofColor::fromHsb(ofRandom(255), 255, 255, 180));

        for (auto& p : points) {
            if (p == points[0]) path.newSubPath();
            path.lineTo(glm::vec3(p.x, p.y, 0));
        }
        path.close();
        path.draw();

        // Set outline properties
        float hue = ofMap(i, 0, contourFinder.size(), 0, 255);
        path.setStrokeColor(ofColor::fromHsb(hue, 255, 255));
        path.setStrokeWidth(3);
        path.setFilled(false);
        path.draw();

        if (showLabels) {
            cv::Point2f centroid = contourFinder.getCentroid(i);
            glm::vec2 glmCentroid = glm::vec2(centroid.x, centroid.y);
            drawParticles(glmCentroid);
            ofDrawBitmapStringHighlight(ofToString(i), glmCentroid.x + 20, glmCentroid.y, ofColor::black, ofColor::fromHsb(hue, 255, 255));
        }
    }
}

void ofApp::drawParticles(glm::vec2 position) {
    for (int i = 0; i < 10; i++) {
        ofSetColor(ofMap(i, 0, 10, 255, 0), 255, 255);
        ofDrawCircle(position.x + ofRandom(-20, 20), position.y + ofRandom(-20, 20), ofRandom(1, 5));
    }
}

