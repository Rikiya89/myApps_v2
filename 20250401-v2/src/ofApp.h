#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    ofImage flowerImg;
    ofMesh mesh;

    int resolutionX = 100;
    int resolutionY = 100;
    float meshScale = 4.0;
    float heightScale = 100.0;
};
