#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);

    sceneFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB);
    sceneFbo.begin();
    ofClear(255, 255, 255, 0);
    sceneFbo.end();

    // Initialize particles with advanced properties
    for (int i = 0; i < numParticles; i++) {
        Particle newParticle;
        newParticle.position = ofPoint(ofRandomWidth(), ofRandomHeight());
        newParticle.radius = ofRandom(5, 20);
        newParticle.color = ofColor::fromHsb(ofRandom(255), 200, 255, 100);
        newParticle.velocity = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
        particles.push_back(newParticle);
    }
    lastUpdateTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
    float currentTime = ofGetElapsedTimef();
    float deltaTime = currentTime - lastUpdateTime;
    lastUpdateTime = currentTime;

    sceneFbo.begin();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(0, 0, 0, 10);  // Soften the trails over time
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    for (auto &particle : particles) {
        // Environmental reactions
        ofVec2f toMouse = mousePos - particle.position;
        float dist = toMouse.length();
        if (dist < 200) {
            toMouse.normalize();
            particle.velocity += toMouse * (200 - dist) / 200 * 0.1;  // Mouse attraction
        }

        particle.position += particle.velocity * deltaTime * 60;  // Movement with time smoothness
        particle.velocity *= 0.99;  // Damping

        // Trail effect
        if (particle.trail.size() > 20) {
            particle.trail.pop_back();
        }
        particle.trail.push_front(particle.position);

        // Bounce off edges
        if(particle.position.x < particle.radius || particle.position.x > ofGetWidth() - particle.radius) {
            particle.velocity.x *= -1;
        }
        if(particle.position.y < particle.radius || particle.position.y > ofGetHeight() - particle.radius) {
            particle.velocity.y *= -1;
        }
    }
    sceneFbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    sceneFbo.draw(0, 0);
    for (auto &particle : particles) {
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
        int numPoints = particle.trail.size();
        int count = 0;
        for (auto &point : particle.trail) {
            float brightness = ofMap(count++, 0, numPoints, 0, 255, true);  // Proper mapping from trail index to alpha
            ofColor c = particle.color;
            c.a = brightness;  // Fading alpha
            mesh.addColor(c);
            mesh.addVertex(point);
        }
        mesh.draw();
        ofSetColor(particle.color);
        ofDrawCircle(particle.position, particle.radius);
    }
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    mousePos = ofPoint(x, y);
}
