#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    ofEasyCam cam;               // EasyCam for 3D navigation
    ofLight pointLight;          // Light source for glow effects

    ofSoundPlayer soundPlayer;   // Audio player
    vector<float> fftSmoothed;   // Smoothed FFT values for audio-reactive effects
};
