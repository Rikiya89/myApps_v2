#include "Particle.h"

Particle::Particle(){
    position = glm::vec2(0);
    velocity = glm::vec2(0);
    lifespan = 255;
    color = ofColor::white;
    rotation = 0;
    angularVelocity = 0;
    scale = 1.0;
    bloom = 0.0;
    auraIntensity = 0.0;
}

Particle::Particle(glm::vec2 pos, ofColor col) {
    position = pos;
    color = col;
    float angle = ofRandom(0, TWO_PI);
    float speed = ofRandom(1, 3);
    velocity = glm::vec2(cos(angle), sin(angle)) * speed;
    lifespan = 255;
    rotation = ofRandom(0, 360);
    angularVelocity = ofRandom(-2, 2);
    scale = ofRandom(0.8, 1.2);
    bloom = 0.0;
    auraIntensity = 0.0;
}

void Particle::update(){
    position += velocity;
    lifespan -= 2.0;
    if(lifespan < 0) lifespan = 0;
    color.a = lifespan;
    rotation += angularVelocity;
    scale = ofMap(lifespan, 255, 0, scale, 0);
    bloom = sin((255 - lifespan) / 255.0 * PI);
    auraIntensity = bloom * 1.2;
    
    float hue = color.getHue();
    hue += 0.3;
    if(hue > 255) hue -= 255;
    color.setHue(hue);
}

void Particle::draw(){
    ofPushMatrix();
    ofTranslate(position);
    ofRotateDeg(rotation);
    ofScale(scale, scale);
    
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (int i = 0; i < 5; i++){
         float radius = (i + 1) * 15 * auraIntensity;
         ofSetColor(color, 50 - i * 10);
         ofDrawCircle(0, 0, radius);
    }
    ofDisableBlendMode();
    ofPopStyle();
    
    ofPushStyle();
    ofColor drawColor = color;
    drawColor.a = color.a;
    ofSetColor(drawColor);
    
    float basePetalLength = 20;
    float basePetalWidth  = 8;
    float petalLength = basePetalLength + bloom * 10;
    float petalWidth  = basePetalWidth  + bloom * 4;
    
    ofBeginShape();
        ofCurveVertex(0, petalLength);
        ofCurveVertex(-petalWidth, petalLength * 0.5);
        ofCurveVertex(-petalWidth * 0.8, 0);
        ofCurveVertex(0, -petalLength);
        ofCurveVertex(petalWidth * 0.8, 0);
        ofCurveVertex(petalWidth, petalLength * 0.5);
        ofCurveVertex(0, petalLength);
    ofEndShape();
    
    ofSetColor(255, 255, 255, color.a * 0.5);
    ofDrawCircle(0, -petalLength, petalWidth * 0.3);
    
    ofPopStyle();
    ofPopMatrix();
}

bool Particle::isDead(){
    return lifespan <= 0;
}
