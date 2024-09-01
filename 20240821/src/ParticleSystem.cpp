#include "ParticleSystem.h"

void ParticleSystem::setup() {
    particles.clear(); // Initialize by clearing any existing particles
}

void ParticleSystem::update() {
    for (auto it = particles.begin(); it != particles.end(); ) {
        it->update();
        if (it->isDead()) {
            it = particles.erase(it); // Remove dead particles
        } else {
            ++it;
        }
    }
}

void ParticleSystem::draw() {
    for (auto& particle : particles) {
        particle.draw();
    }
}

void ParticleSystem::addParticle(ofVec2f position, ofVec2f velocity, ofColor color) {
    particles.emplace_back(position, velocity, color); // Add a new particle
}

void ParticleSystem::applyForce(const ofVec2f& force) {
    for (auto& particle : particles) {
        // Apply a force to each particle (e.g., fluid velocity)
        particle.applyForce(force);
    }
}
