#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    ofEasyCam cam;
    ofMesh mesh;
    ofShader shader;

    int sphereResolution = 150;
    float noiseFactor = 0.15;
    float timeOffset = 0.0;

    glm::vec3 colorA = glm::vec3(1.0, 0.5, 1.0); // Purple-Pink
    glm::vec3 colorB = glm::vec3(0.1, 0.8, 1.0); // Blue-Cyan
};
