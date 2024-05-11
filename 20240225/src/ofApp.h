#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    ofMesh mesh;
    vector<glm::vec3> speeds;
    vector<float> distances;
    ofEasyCam cam;
    ofLight light; // Lighting

    // Variables for color dynamics
    float hue;
};
