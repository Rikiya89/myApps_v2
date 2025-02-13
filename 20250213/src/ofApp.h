#pragma once
#include "ofMain.h"

// Structure representing a heart with additional trail data.
struct Heart {
    ofVec2f pos;              // Current position.
    float baseSize;           // Base scale factor for the heart.
    ofVec2f vel;              // Falling velocity.
    float phase;              // Phase offset for pulsation.
    vector<ofVec2f> trail;    // Recent positions for trailing effect.
};

// Structure representing a sparkle particle.
struct Sparkle {
    ofVec2f pos;
    ofVec2f vel;
    float life;     // Remaining life (in seconds).
    float maxLife;  // Maximum life (for fading calculations).
};

// Structure representing a petal.
struct Petal {
    ofVec2f pos;            // Current position.
    ofVec2f vel;            // Drifting velocity.
    float angle;            // Current rotation angle.
    float angularVelocity;  // Rotation speed.
    float scale;            // Scale factor.
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    // Draws a heart shape at (x, y) with a given scale using precomputed vertices.
    void drawHeart(float x, float y, float scale);

    // Draws a dynamic vertical gradient background.
    void drawGradientBackground();

    vector<Heart> hearts;
    int numHearts;

    // Precomputed heart shape vertices.
    vector<ofVec2f> heartShape;

    // Sparkle particles.
    vector<Sparkle> sparkles;

    // Petals.
    vector<Petal> petals;
    int numPetals;
};
