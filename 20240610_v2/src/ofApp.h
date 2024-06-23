#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    ofImage image;
    ofMesh mesh;
    ofEasyCam easyCam;
    ofLight light1;  // Adding first light source
    ofLight light2;  // Adding second light source
    float time;     // Variable to track time for animation

    // GUI elements
    ofxPanel gui;
    ofxFloatSlider camPosX;
    ofxFloatSlider camPosY;
    ofxFloatSlider camPosZ;
    ofxFloatSlider camRotX;
    ofxFloatSlider camRotY;
    ofxFloatSlider camRotZ;
};
