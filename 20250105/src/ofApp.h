#pragma once
#include "ofMain.h"
#include <vector>

// Structure to represent particles
struct Particle {
    ofPoint position;
    ofVec2f velocity;
    float size;
    ofColor color;
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    // Event handlers
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    float timeElapsed; // Time variable for animations
    std::vector<Particle> particles; // Particle system
};
