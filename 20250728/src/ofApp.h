#pragma once

#include "ofMain.h"

struct GridCell {
    float x, y;
    float size;
    char letter;
    float rotation;
    float scale;
    ofColor color;
    float animationPhase;
    float pulseSpeed;
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

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
    // Grid system
    vector<GridCell> grid;
    int gridCols;
    int gridRows;
    float cellSize;
    float gridSpacing;

    // Typography
    ofTrueTypeFont font;
    string alphabet;
    string words[5];

    // Animation
    float time;
    float waveSpeed;
    float colorShift;

    // Visual effects
    bool showGrid;
    float noiseScale;
    float rotationSpeed;

    // Methods
    void setupGrid();
    void updateGrid();
    void drawGrid();
    void generateRandomLetter(GridCell& cell);
    ofColor getColorFromPosition(float x, float y, float time);
};
