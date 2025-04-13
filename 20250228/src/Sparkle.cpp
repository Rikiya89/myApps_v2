#include "Sparkle.h"

Sparkle::Sparkle(){
    position = glm::vec2(0);
    velocity = glm::vec2(0, -1);
    lifespan = 60;
    age = 0;
    size = 4;
    hue = ofRandom(0, 255);
}

Sparkle::Sparkle(glm::vec2 pos){
    position = pos;
    velocity = glm::vec2(ofRandom(-0.5, 0.5), ofRandom(-2, -1));
    lifespan = ofRandom(40, 80);
    age = 0;
    size = ofRandom(2, 5);
    hue = ofRandom(0, 255);
}

void Sparkle::update(){
    age++;
    position += velocity;
}

void Sparkle::draw(){
    float alpha = ofMap(age, 0, lifespan, 255, 0);
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(ofColor::fromHsb(hue, 200, 255, alpha));
    ofDrawCircle(position, size);
    ofDisableBlendMode();
    ofPopStyle();
}

bool Sparkle::isDead(){
    return age >= lifespan;
}
