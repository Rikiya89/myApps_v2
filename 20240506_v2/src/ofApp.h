#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void drawParticles(glm::vec2 position);  // Declaration for the particle drawing method

    ofVideoGrabber cam;  // Video grabber for capturing webcam input
    ofxCvColorImage colorImg;  // Color image captured from the webcam
    ofxCvGrayscaleImage grayImage;  // Grayscale image used for contour detection
    ofxCv::ContourFinder contourFinder;  // Contour finder for detecting shapes in the webcam feed
    bool showLabels;  // Toggle to show labels on detected contours
};
