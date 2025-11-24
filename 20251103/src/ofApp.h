#pragma once

#include "ofMain.h"

struct Particle {
    ofVec3f pos;
    ofVec3f vel;
    ofColor color;
    float size;
    float rotation;
    float rotationSpeed;
    ofVec3f axis;
    int shapeType; // 0: sphere, 1: box, 2: cone
};

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    // Color palette
    vector<ofColor> colors;

    // Particles
    vector<Particle> particles;

    // Camera
    ofEasyCam cam;

    // Time
    float time;

    // Lighting
    ofLight light;
};
