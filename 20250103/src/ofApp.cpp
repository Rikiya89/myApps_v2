#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0); // Set the background to black
    baseRadius = 10.0f; // Base radius
    timeOffset = 0.0f;  // Initial time offset
    backgroundColor = ofColor(0, 0, 20); // Start with a dark blue background
}

//--------------------------------------------------------------
void ofApp::update() {
    // Update the time offset for radius oscillation
    timeOffset += 0.05f;

    // Update particles' life and apply Perlin noise for motion
    for (auto it = particles.begin(); it != particles.end();) {
        it->life -= 1.0f; // Decrease life for fading effect
        if (it->life <= 0) {
            it = particles.erase(it); // Remove expired particles
        } else {
            it->velocity += getPerlinNoise(it->position.x, it->position.y) * 0.1; // Apply Perlin noise to velocity
            it->position += it->velocity; // Update position
            ++it;
        }
    }

    // Gradually change background color
    backgroundColor.lerp(ofColor(20, 0, 40), 0.01f);
    ofBackground(backgroundColor);
}

//--------------------------------------------------------------
void ofApp::draw() {
    // Enable blending for glow effect
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    for (const auto& particle : particles) {
        float t = 1.0f - particle.life / 255.0f; // Interpolation factor
        ofColor currentColor = particle.startColor.getLerped(particle.endColor, t);
        ofSetColor(currentColor, particle.life); // Fading effect with life

        // Draw outer glow
        for (float scale = 1.0f; scale <= 1.5f; scale += 0.1f) {
            ofSetColor(currentColor, particle.life * (1.5f - scale)); // Reduce alpha for glow layers
            float dynamicRadius = particle.radius * scale + sin(timeOffset + particle.depth) * 5.0f; // Oscillating radius
            ofDrawCircle(particle.position, dynamicRadius);
        }

        // Draw the particle shape
        drawShape(particle);
    }

    ofDisableBlendMode(); // Disable blending after drawing
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    // Add a new particle with gradient colors and varying depth
    Particle particle;
    particle.position = ofVec2f(x, y);
    particle.velocity = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1)); // Add slight random velocity
    particle.startColor = ofColor::fromHsb(ofRandom(255), 200, 255); // Vibrant starting color
    particle.endColor = ofColor::fromHsb(ofRandom(255), 100, 200);   // Softer ending color
    particle.radius = baseRadius + ofRandom(-5.0f, 5.0f); // Slightly random size
    particle.depth = ofRandom(0.1f, 1.0f); // Random depth for parallax effect
    particle.life = 255.0f; // Full opacity life
    particle.shapeType = ofRandom(0, 3); // Randomly select shape type (0, 1, 2)

    particles.push_back(particle);

    // Limit the number of particles to avoid overloading
    if (particles.size() > 500) {
        particles.erase(particles.begin());
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    // Generate a burst of particles
    for (int i = 0; i < 50; ++i) {
        Particle particle;
        particle.position = ofVec2f(x, y);
        particle.velocity = ofVec2f(ofRandom(-5, 5), ofRandom(-5, 5)); // Random burst velocity
        particle.startColor = ofColor::fromHsb(ofRandom(255), 255, 255);
        particle.endColor = ofColor::fromHsb(ofRandom(255), 100, 200);
        particle.radius = baseRadius + ofRandom(-10.0f, 10.0f);
        particle.depth = ofRandom(0.1f, 1.0f);
        particle.life = 255.0f;
        particle.shapeType = ofRandom(0, 3);
        particles.push_back(particle);
    }
}

//--------------------------------------------------------------
void ofApp::drawShape(const Particle& particle) {
    switch (particle.shapeType) {
        case 0: // Circle
            ofDrawCircle(particle.position, particle.radius);
            break;
        case 1: // Triangle
            ofDrawTriangle(
                particle.position + ofVec2f(0, -particle.radius),
                particle.position + ofVec2f(particle.radius, particle.radius),
                particle.position + ofVec2f(-particle.radius, particle.radius)
            );
            break;
        case 2: // Star
            for (int i = 0; i < 10; ++i) {
                float angle = ofDegToRad(i * 36);
                float r = (i % 2 == 0) ? particle.radius : particle.radius * 0.5;
                float x = particle.position.x + r * cos(angle);
                float y = particle.position.y + r * sin(angle);
                if (i == 0) {
                    ofBeginShape();
                }
                ofVertex(x, y);
                if (i == 9) {
                    ofEndShape(true);
                }
            }
            break;
    }
}

//--------------------------------------------------------------
ofVec2f ofApp::getPerlinNoise(float x, float y) {
    return ofVec2f(
        ofNoise(x * 0.01, timeOffset) - 0.5,
        ofNoise(y * 0.01, timeOffset + 1000) - 0.5
    );
}
