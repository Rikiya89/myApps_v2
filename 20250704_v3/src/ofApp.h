#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

    ofEasyCam cam;
    float time;
    int numPoints;

    struct GeoPoint {
        glm::vec3 pos;
        float phi;
        float theta;
    };
    std::vector<GeoPoint> geoPoints;

    void generateFibonacciSphere();
    ofColor getCosmicColor(float t, float time);
    ofColor getChakraColor(float t);
};
