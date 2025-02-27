#include "ofApp.h"

// Particle Update Function
void Particle::update(ofVec3f force) {
    velocity += force / mass;
    position += velocity;
    velocity *= 0.95; // Damping effect
}

// Particle Draw Function
void Particle::draw() {
    ofDrawSphere(position, mass * 2.0);
}

// Setup Function
void ofApp::setup() {
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);

    // Setup Audio Input Stream
    ofSoundStreamSettings settings;
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.bufferSize = 512;
    ofSoundStreamSetup(settings);

    // Initialize FFT
    fft = ofxFft::create(512, OF_FFT_WINDOW_HAMMING);
    fftMagnitude.resize(fft->getBinSize(), 0.0f);

    // Load the Shader
    fluidShader.load("shadersGL3/fluid");

    // Initialize Particles
    for (int i = 0; i < 500; i++) {
        Particle p;
        p.position = ofVec3f(ofRandom(-200, 200), ofRandom(-200, 200), ofRandom(-200, 200));
        p.velocity = ofVec3f(0, 0, 0);
        p.mass = ofRandom(1.0, 3.0);
        particles.push_back(p);
    }

    magneticField = ofVec3f(0, 0, 0); // Initial magnetic field center
}

// Audio Input Processing
void ofApp::audioIn(ofSoundBuffer & input) {
    int nSamples = input.getNumFrames() * input.getNumChannels();
    audioBuffer.assign(input.getBuffer(), input.getBuffer() + nSamples);

    fft->setSignal(&audioBuffer[0]);

    // FFTの振幅データを vector にコピー
    float* fftData = fft->getAmplitude();
    int fftSize = fft->getBinSize();

    if (fftData && fftSize > 0) {  // 安全チェックを追加
        fftMagnitude.assign(fftData, fftData + fftSize);
    } else {
        fftMagnitude.clear(); // データが無効ならクリア
    }

    // 低音域を使って磁場の強さを制御
    if (!fftMagnitude.empty()) {
        float bassIntensity = fftMagnitude[0] * 50.0;
        magneticField = ofVec3f(0, 0, -bassIntensity);
    }
}

// Update Simulation
void ofApp::update() {
    for (auto &p : particles) {
        float distance = p.position.distance(magneticField);
        float attractionForce = ofClamp(1000.0 / (distance + 10.0), 0, 10.0);
        ofVec3f force = (magneticField - p.position).normalize() * attractionForce;

        // FFTデータが空でないかチェックしてからアクセス
        if (!fftMagnitude.empty()) {
            int fftSize = static_cast<int>(fftMagnitude.size()); // int にキャスト
            float turbulence = fftMagnitude[ofRandom(fftSize)] * 10.0;

            force += ofVec3f(ofRandom(-turbulence, turbulence),
                             ofRandom(-turbulence, turbulence),
                             ofRandom(-turbulence, turbulence));
        }

        p.update(force);
    }
}

// Draw Function
void ofApp::draw() {
    cam.begin();
    fluidShader.begin();

    // Pass FFT data to the shader
    fluidShader.setUniform1fv("fftSpectrum", &fftMagnitude[0], fftMagnitude.size());

    // Draw Particles
    for (auto &p : particles) {
        p.draw();
    }

    fluidShader.end();
    cam.end();
}
