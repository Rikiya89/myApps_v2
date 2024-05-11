#include "Particle.h"

Particle::Particle() : age(0), maxLifeTime(100) {}

void Particle::setup(ofVec2f startPosition, ofVec2f startVelocity, ofColor _startColor, ofColor _endColor, float startRadius, float maxLife) {
    position = startPosition;
    velocity = startVelocity;
    startColor = _startColor;
    endColor = _endColor;
    radius = startRadius;
    maxLifeTime = maxLife;
}

void Particle::update() {
    position += velocity;
    applyForces();
    age++;
    if(age > maxLifeTime) {
        age = 0; // Reset age if it exceeds its lifetime, could also regenerate the particle
    }
}

void Particle::draw() {
    float lifeRatio = age / maxLifeTime;
    ofColor currentColor = startColor.getLerped(endColor, lifeRatio);
    currentColor.a = 255 * (1 - lifeRatio); // Fade out as it ages

    // Draw glow effect
    int glowSteps = 5;
    for (int i = 0; i < glowSteps; i++) {
        float alpha = (1 - (float)i / glowSteps) * 255;
        float size = radius + (radius * 0.5 * i);
        ofSetColor(currentColor, alpha);
        ofDrawCircle(position, size);
    }
}

void Particle::applyForces() {
    // Add any environmental forces here, like wind or oscillation
    // Example: Oscillate based on Perlin noise
    float noise = ofNoise(position.x * 0.05, position.y * 0.05, ofGetElapsedTimef() * 0.1);
    velocity.x += cos(noise * TWO_PI) * 0.2;
    velocity.y += sin(noise * TWO_PI) * 0.2;
}
