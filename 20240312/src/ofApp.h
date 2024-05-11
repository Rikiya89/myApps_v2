#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void drawSeedOfLife(float x, float y, float baseRadius, float rotation, float timeOffset, ofColor color);
        void drawCircle(float x, float y, float radius, ofColor color);

        float centerX, centerY;
        float animSpeed;
        std::vector<float> rotationSpeeds;
        std::vector<float> scales;
        ofColor backgroundColor;
};
