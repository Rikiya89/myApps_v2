#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    ofEasyCam cam;
    ofVboMesh sphereMesh;
    float time;
    ofLight light1, light2;
    ofMaterial material;
    vector<glm::vec3> originalVertices;
    vector<vector<glm::vec3>> trails;
    int maxTrailLength = 25; // Reduced trail length for performance

    void drawVertexEffects(const glm::vec3 &vertex, float colorValue);
};
