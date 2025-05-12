#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void drawSacredForm(float time);
    void drawSparkles(float time);
    void drawTorus(float radius, float tubeRadius, int sides, int rings);

    ofEasyCam cam;
    vector<ofVec3f> points;
    float timeScale;
};
