#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

    public:
        void setup() override;
        void update() override;
        void draw() override;

        float time = 0;
        ofEasyCam cam;
};
