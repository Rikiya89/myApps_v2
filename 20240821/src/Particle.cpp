#include "Particle.h"

Particle::Particle(ofVec2f position, ofVec2f velocity, ofColor color)
: position(position), velocity(velocity), color(color), lifespan(255), maxLifespan(255), initialSize(ofRandom(3, 6)) {
    size = initialSize;
}

void Particle::update() {
    // Update position based on velocity
    position += velocity;

    // Slowly reduce the particle's lifespan
    lifespan -= 2.0;
    if (lifespan < 0) lifespan = 0;

    // Gradually reduce the particle's size
    size = ofMap(lifespan, 0, maxLifespan, 0, initialSize);

    // Fade the color based on the lifespan
    color.a = ofMap(lifespan, 0, maxLifespan, 0, 255);

    // Add a slight decay to the velocity to simulate friction
    velocity *= 0.95;
}

void Particle::draw() {
    // Draw the particle as a smooth, semi-transparent circle
    ofSetColor(color);
    ofDrawCircle(position, size);
}

bool Particle::isDead() const {
    // A particle is considered "dead" when its lifespan reaches 0
    return lifespan <= 0;
}

void Particle::applyForce(const ofVec2f& force) {
    velocity += force;
}
