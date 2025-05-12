#pragma once
#include "ofMain.h"

struct Sparkle {
    glm::vec3 pos;
    float size;
    float alpha;
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void createMesh();

    ofEasyCam cam;
    ofSoundPlayer sound;

    ofMesh mesh;
    vector<float> fftSmoothed;
    int nBandsToGet = 128;

    float sparkleThreshold = 0.2;
    int maxSparkles = 300;

    vector<Sparkle> sparkles;
};
