#pragma once
#include "ofMain.h"

class Sparkle {
public:
    Sparkle();
    Sparkle(glm::vec2 pos);
    
    void update();
    void draw();
    bool isDead();
    
    glm::vec2 position;
    glm::vec2 velocity;
    float lifespan;
    float age;
    float size;
    float hue;
};
