#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    // Event handlers...

    ofEasyCam cam;  // Camera for easy 3D manipulation.
    ofLight light1;  // Primary light source.
    ofLight light2;  // Secondary light source.
    ofMaterial material;  // Material for the spheres.
    std::vector<Particle> particles;  // Particle system.
};
