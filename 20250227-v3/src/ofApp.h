#pragma once
#include "ofMain.h"
#include "ofxFft.h"

class Particle {
public:
    ofVec3f position, velocity;
    float mass;
    void update(ofVec3f force);
    void draw();
};

class ofApp : public ofBaseApp {
public:
    void setup() override;
    void update() override;
    void draw() override;
    void audioIn(ofSoundBuffer & input);

    // Audio & FFT
    vector<float> audioBuffer;
    ofxFft* fft;
    vector<float> fftMagnitude;

    // Particle System
    vector<Particle> particles;
    ofEasyCam cam;

    // Magnetic field simulation
    ofVec3f magneticField;

    // Shader for visuals
    ofShader fluidShader;
};
