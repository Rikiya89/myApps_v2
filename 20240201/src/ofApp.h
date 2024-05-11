#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();

        ofEasyCam easyCam; // 3D Camera
        ofLight light; // Dynamic lighting
        ofxPanel gui; // GUI for real-time control
        ofParameter<float> radius, rotationSpeed, oscillation;
        ofParameter<int> numPoints, layers;
        ofParameter<bool> animate;
        ofParameter<ofColor> baseColor; // Base color for patterns

        vector<ofPoint> points; // Points for sacred geometry
        float rotation; // Rotation for animation
        float time; // Time for animations

        void createGeometry();
};
