#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

// Define the Particle class for enhanced visual effects.
class Particle {
public:
    ofPoint position;
    ofVec2f velocity;
    ofColor color;
    float radius;
    float lifespan; // Lifespan of the particle

    Particle(ofPoint pos, ofVec2f vel, ofColor col, float rad)
        : position(pos), velocity(vel), color(col), radius(rad), lifespan(255) {}

    void update() {
        position += velocity;
        lifespan -= 2; // Decrease the lifespan
        color.a = lifespan; // Update alpha based on lifespan
    }

    void draw() {
        ofSetColor(color);
        ofDrawCircle(position, radius);
    }

    bool isDead() {
        return lifespan < 0;
    }
};

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void mouseDragged(int x, int y, int button);
    void addRandomShape();
    void drawGradientBackground();
    void addParticlesAroundShape(shared_ptr<ofxBox2dBaseShape> shape);

    ofxBox2d box2d; // The Box2D world
    vector<shared_ptr<ofxBox2dCircle>> circles; // Default box2d circles
    vector<shared_ptr<ofxBox2dPolygon>> polygons; // box2d polygons for variety
    vector<Particle> particles; // Particles for visual effects
};
