#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();

        void drawSacredGeometry();
        void drawGeometryLayer(float radius, float rotation); // Additional function for layered geometry

        int numCircles;
        float baseRadius;
        vector<ofColor> colors;

        float time;
        float rotationSpeed;
};
