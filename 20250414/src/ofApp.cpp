#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofEnableSmoothing();
    ofSetLineWidth(1.2);

    sound.load("piano.mp3"); // Place in bin/data/
    sound.setLoop(true);
    sound.play();

    fftSmoothed.assign(nBandsToGet, 0.0f);
    createMesh();
}

void ofApp::update(){
    ofSoundUpdate();
    float *val = ofSoundGetSpectrum(nBandsToGet);
    for (int i = 0; i < nBandsToGet; i++) {
        fftSmoothed[i] *= 0.96f;
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
    }

    int w = 70;
    int h = 70;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int index = x + y * w;
            glm::vec3 v = mesh.getVertex(index);

            float freq = fftSmoothed[index % nBandsToGet];
            float wave = sin(ofGetElapsedTimef() * 0.2 + x * 0.3 + y * 0.3) * 8.0;
            float pulse = freq * 100.0;
            float curve = sin((float)x / w * PI) * 20.0;

            v.z = pulse + wave + curve;
            mesh.setVertex(index, v);

            float brightness = ofMap(freq, 0, 0.5, 100, 255, true);
            float zFade = ofMap(abs(v.z), 0, 300, 1.0, 0.1, true);
            mesh.setColor(index, ofColor(brightness * zFade));
        }
    }

    // ✨ Audio-reactive sparkles (lighter logic)
    for (int y = 0; y < h; y += 2) {
        for (int x = 0; x < w; x += 2) {
            int index = x + y * w;
            float freq = fftSmoothed[index % nBandsToGet];

            if (freq > sparkleThreshold && ofRandom(1.0) < freq * 3.0) {
                if (sparkles.size() < maxSparkles) {
                    Sparkle s;
                    s.pos = mesh.getVertex(index);
                    s.size = ofMap(freq, 0.2, 0.6, 1.5, 3.5, true);
                    s.alpha = 255;
                    sparkles.push_back(s);
                }
            }
        }
    }

    for (auto &s : sparkles) {
        s.pos.z += 0.25;
        s.alpha *= 0.94;
    }

    sparkles.erase(std::remove_if(sparkles.begin(), sparkles.end(),
        [](const Sparkle &s){ return s.alpha < 2; }),
        sparkles.end());
}

void ofApp::draw(){
    cam.begin();

    mesh.drawWireframe();

    for (auto &s : sparkles) {
        ofSetColor(255, s.alpha);
        ofDrawSphere(s.pos, s.size);

        // Optional soft glow (commented for performance)
        // ofSetColor(255, s.alpha * 0.3);
        // ofDrawSphere(s.pos, s.size * 2.0);
    }

    cam.end();
}

void ofApp::createMesh(){
    mesh.setMode(OF_PRIMITIVE_LINES);

    int w = 70;
    int h = 70;
    float spacing = 10.0;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            float xpos = (x - w / 2) * spacing;
            float ypos = (y - h / 2) * spacing;
            mesh.addVertex(glm::vec3(xpos, ypos, 0));
            mesh.addColor(ofColor::white);
        }
    }

    for (int y = 0; y < h - 1; y++) {
        for (int x = 0; x < w - 1; x++) {
            int i = x + y * w;
            mesh.addIndex(i);     mesh.addIndex(i + 1);
            mesh.addIndex(i);     mesh.addIndex(i + w);
        }
    }
}
