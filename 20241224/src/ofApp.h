#pragma once
#include "ofMain.h"
#include "Snowflake.h"

class ofApp : public ofBaseApp {
public:
    void setup() override;
    void update() override;
    void draw() override;

private:
    std::vector<Snowflake> snowflakes; // Collection of snowflakes
    void drawDynamicGradientBackground();

    float timeElapsed; // For dynamic background animation
};
