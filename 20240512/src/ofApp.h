#pragma once

#include "ofMain.h"
#include <vector>

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseScrolled(int x, int y, float scrollX, float scrollY);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofImage image;
    ofMesh mesh;
    ofMesh meshCopy;
    std::vector<float> noiseSeeds;
    std::vector<ofVec3f> offsets;
    ofEasyCam easyCam;
    bool mouseDisplacement; // Toggling the magnifying glass effect
};
