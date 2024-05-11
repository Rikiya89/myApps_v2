#pragma once

#include "ofMain.h"
#include <vector>

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();

        ofVideoGrabber cam;  // Webcam object
        vector<ofPoint> petals; // Stores positions of petals
        void addPetals(int x, int y, int amount); // Function to add petals
};
