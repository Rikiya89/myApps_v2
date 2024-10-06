// ofApp.h

#ifndef OFAPP_H
#define OFAPP_H

#include "ofMain.h"

class Particle {
public:
    Particle(float startX, float startY);
    void update();
    void draw();

    ofPoint position;
    ofPoint velocity;
    ofColor color;
    float lifespan;
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    std::vector<Particle> particles;
    float theta;
};

#endif // OFAPP_H
