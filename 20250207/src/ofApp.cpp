#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(5, 5, 15);
    ofEnableDepthTest();

    glowShader.load("shaders/shader");

    // Load and play celestial sound
    cosmicSound.load("sounds/carina-stars-aug-3.wav");
    cosmicSound.setLoop(true);
    cosmicSound.play();
    cosmicSound.setVolume(0.8);

    generateTorus();
    generateSacredGeometry();
    generateParticles();
}

void ofApp::generateTorus() {
    torusMesh.clear();
    torusMesh.setMode(OF_PRIMITIVE_TRIANGLES);

    for (int i = 0; i < numRings; i++) {
        float theta = ofMap(i, 0, numRings, 0, TWO_PI);
        for (int j = 0; j < numSides; j++) {
            float phi = ofMap(j, 0, numSides, 0, TWO_PI);
            
            float x = (baseRadiusMajor + baseRadiusMinor * cos(phi)) * cos(theta);
            float y = (baseRadiusMajor + baseRadiusMinor * cos(phi)) * sin(theta);
            float z = baseRadiusMinor * sin(phi);

            glm::vec3 vertex(x, y, z);
            torusMesh.addVertex(vertex);
            torusMesh.addColor(ofFloatColor(1.0, 0.8, 0.3));

            int nextI = (i + 1) % numRings;
            int nextJ = (j + 1) % numSides;
            int current = i * numSides + j;
            int right = i * numSides + nextJ;
            int down = nextI * numSides + j;
            int diagonal = nextI * numSides + nextJ;

            torusMesh.addIndex(current);
            torusMesh.addIndex(right);
            torusMesh.addIndex(down);
            torusMesh.addIndex(right);
            torusMesh.addIndex(diagonal);
            torusMesh.addIndex(down);
        }
    }
}

void ofApp::generateSacredGeometry() {
    sacredGeometryMesh.clear();
    sacredGeometryMesh.setMode(OF_PRIMITIVE_LINES);

    float goldenRatio = 1.618;
    for (float angle = 0; angle < TWO_PI; angle += PI / 6) {
        for (float radius = 20; radius < baseRadiusMajor; radius *= goldenRatio) {
            float x = radius * cos(angle);
            float y = radius * sin(angle);
            float z = 0;
            sacredGeometryMesh.addVertex(glm::vec3(x, y, z));
            sacredGeometryMesh.addColor(ofFloatColor(0.8, 0.5, 1.0));
        }
    }
}

void ofApp::generateParticles() {
    particles.clear();
    for (int i = 0; i < 250; i++) {
        particles.push_back(glm::vec3(
            ofRandom(-400, 400),
            ofRandom(-400, 400),
            ofRandom(-400, 400)
        ));
    }
}

void ofApp::update() {
    timeOffset += 0.01;

    // Adjust torus size based on sound volume
    soundLevel = cosmicSound.getVolume() * 20;
    radiusMajor = baseRadiusMajor + sin(ofGetElapsedTimef() * 2) * soundLevel;
    radiusMinor = baseRadiusMinor + cos(ofGetElapsedTimef() * 1.5) * soundLevel;

    for (int i = 0; i < torusMesh.getVertices().size(); i++) {
        glm::vec3 original = glm::normalize(torusMesh.getVertex(i)) * (radiusMajor + radiusMinor);
        
        float noise = ofNoise(original.x * noiseFactor, original.y * noiseFactor, original.z * noiseFactor, timeOffset);
        float displacement = ofMap(noise, 0, 1, -20, 20);
        glm::vec3 newVertex = original + glm::normalize(original) * displacement;
        torusMesh.setVertex(i, newVertex);
    }
}

void ofApp::draw() {
    cam.begin();
    ofRotateYDeg(ofGetElapsedTimef() * rotationSpeed * 100);

    glowShader.begin();
    glowShader.setUniform1f("time", ofGetElapsedTimef());
    glowShader.setUniform3f("color1", 1.0, 0.5, 0.3);
    glowShader.setUniform3f("color2", 0.3, 0.8, 1.0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    torusMesh.drawWireframe();
    glowShader.end();

    ofSetColor(255, 255, 255, 120);
    sacredGeometryMesh.draw();

    for (auto &p : particles) {
        ofSetColor(255, 255, 180, ofRandom(150, 255));
        ofDrawSphere(p, 2);
    }

    cam.end();
}

void ofApp::keyPressed(int key) {
    if (key == 'r') {
        noiseFactor = ofRandom(0.05, 0.3);
    }
}
