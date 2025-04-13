#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void drawRecursiveTetrahedron(ofVec3f pos, float size, int level, float time);
    void drawTetrahedron(float size, int level);

    ofEasyCam cam;
    static ofVec3f tetrahedronOffsets[4];
};
