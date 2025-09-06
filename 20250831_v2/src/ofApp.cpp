#include "ofApp.h"
#include <algorithm>

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundAuto(false); // allow trails
    ofBackground(0);
    ofEnableDepthTest();
    ofEnableSmoothing();
    ofSetLineWidth(2.0f);

    // Camera setup
    cam.setDistance(380.0f);
    cam.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
    cam.setNearClip(1.0f);
    cam.setFarClip(5000.0f);

    // Initial parameters for a balanced superformula sculpture
    thetaParams = {7.0f, 1.0f, 1.0f, 0.3f, 0.3f, 0.3f};
    phiParams   = {3.0f, 1.0f, 1.0f, 0.2f, 1.7f, 1.7f};
    buildMesh(thetaParams, phiParams);
    t0 = ofGetElapsedTimef();
    
    // Initialize particles for generative system
    particles.resize(maxParticles);
    particleVels.resize(maxParticles);
    particleLife.resize(maxParticles);
    
    for(int i = 0; i < maxParticles; i++) {
        particles[i] = glm::vec3(ofRandom(-200, 200), ofRandom(-200, 200), ofRandom(-200, 200));
        particleVels[i] = glm::vec3(ofRandom(-2, 2), ofRandom(-2, 2), ofRandom(-2, 2));
        particleLife[i] = ofRandom(0.0f, 1.0f);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    float t = ofGetElapsedTimef() - t0;
    if (animate) {
        // Different animation modes for varied beauty
        SuperParams a, b;
        switch(animationMode) {
            case 0: // Wave animation
                a = getWaveParams(t * morphSpeed, true);
                b = getWaveParams(t * morphSpeed, false);
                break;
            case 1: // Spiral animation
                a = getSpiralParams(t * morphSpeed, true);
                b = getSpiralParams(t * morphSpeed, false);
                break;
            case 2: // Organic growth
                a = getOrganicParams(t * morphSpeed, true);
                b = getOrganicParams(t * morphSpeed, false);
                break;
            case 3: // Musical rhythm
                a = getMusicalParams(t * morphSpeed, true);
                b = getMusicalParams(t * morphSpeed, false);
                break;
            default:
                a = getEvolvedParams(t * morphSpeed, true);
                b = getEvolvedParams(t * morphSpeed, false);
                break;
        }
        buildMesh(a, b);
    }
    
    updateParticles();
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Gentle fade to black for motion trails (black/white only)
    if (trails) {
        ofPushStyle();
        ofDisableDepthTest(); // avoid writing to depth buffer with the 2D fade quad
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofSetColor(0, 0, 0, trailFade);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        ofPopStyle();
        // Clear depth buffer so 3D geometry is visible this frame
        glClear(GL_DEPTH_BUFFER_BIT);
        ofEnableDepthTest();
    } else {
        ofBackground(0);
    }

    ofPushStyle();
    ofSetColor(lineLuma); // soft white lines

    cam.begin();

    drawElegantObject();

    cam.end();
    
    // Draw 2D generative patterns over the 3D scene
    if(showNoiseField) {
        drawNoiseField();
    }
    drawGenerativeLines();

    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f') ofToggleFullscreen();
    if (key == 'a') animate = !animate;
    if (key == 't') trails = !trails;
    if (key == 's') ofSaveScreen("screenshot_" + ofGetTimestampString() + ".png");

    if (key == ' ') {
        // Randomize base parameters and restart time
        thetaParams.m = ofRandom(2.0f, 10.0f);
        phiParams.m   = ofRandom(2.0f, 10.0f);

        thetaParams.n1 = ofRandom(0.15f, 1.8f);
        thetaParams.n2 = ofRandom(0.15f, 1.8f);
        thetaParams.n3 = ofRandom(0.15f, 1.8f);

        phiParams.n1 = ofRandom(0.15f, 1.8f);
        phiParams.n2 = ofRandom(0.15f, 1.8f);
        phiParams.n3 = ofRandom(0.15f, 1.8f);

        t0 = ofGetElapsedTimef();
    }
    if (key == '[') { lineLuma = std::max(80, lineLuma - 10); }
    if (key == ']') { lineLuma = std::min(255, lineLuma + 10); }
    if (key == '-') { trailFade = std::max(5, trailFade - 2); }
    if (key == '=') { trailFade = std::min(80, trailFade + 2); }
    if (key == 'n') { showNoiseField = !showNoiseField; }
    if (key == 'p') { showParticles = !showParticles; }
    if (key == 'c') { cameraAnimation = !cameraAnimation; }
    if (key == 'b') { breathingIntensity = (breathingIntensity > 0.1f) ? 0.0f : 0.4f; }
    if (key == '1') { animationMode = 0; } // Wave
    if (key == '2') { animationMode = 1; } // Spiral
    if (key == '3') { animationMode = 2; } // Organic
    if (key == '4') { animationMode = 3; } // Musical
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

// --------------------------------------------------------------
// Math helpers and mesh construction
float ofApp::superformula(float theta, const SuperParams& p) const {
    float t1 = powf(fabsf(cosf(p.m * theta * 0.25f) / p.a), p.n2);
    float t2 = powf(fabsf(sinf(p.m * theta * 0.25f) / p.b), p.n3);
    float r = powf(t1 + t2, -1.0f / p.n1);
    // Guard against numerical issues
    if (!std::isfinite(r)) r = 0.0f;
    return r;
}

void ofApp::buildMesh(const SuperParams& pTheta, const SuperParams& pPhi) {
    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    int nu = resU;
    int nv = resV;
    int cols = nu + 1;

    // Precompute vertices
    for (int j = 0; j <= nv; ++j) {
        float v = ofMap(j, 0, nv, -HALF_PI, HALF_PI); // latitude (phi)
        float r2 = superformula(v, pPhi);
        for (int i = 0; i <= nu; ++i) {
            float u = ofMap(i, 0, nu, -PI, PI); // longitude (theta)
            float r1 = superformula(u, pTheta);

            float x = r1 * cosf(u) * r2 * cosf(v);
            float y = r1 * sinf(u) * r2 * cosf(v);
            float z = r2 * sinf(v);
            mesh.addVertex(glm::vec3(x, y, z) * scale);
        }
    }

    // Build triangle indices for a regular grid
    for (int j = 0; j < nv; ++j) {
        for (int i = 0; i < nu; ++i) {
            int i0 = j * cols + i;
            int i1 = i0 + 1;
            int i2 = i0 + cols;
            int i3 = i2 + 1;

            // Two triangles per quad
            mesh.addIndex(i0);
            mesh.addIndex(i2);
            mesh.addIndex(i1);

            mesh.addIndex(i1);
            mesh.addIndex(i2);
            mesh.addIndex(i3);
        }
    }
}

//--------------------------------------------------------------
void ofApp::updateParticles() {
    float t = ofGetElapsedTimef() - t0;
    
    for(int i = 0; i < maxParticles; i++) {
        // Update particle life
        particleLife[i] += ofGetLastFrameTime() * 0.5f;
        
        // Reset particle when it dies
        if(particleLife[i] > 1.0f) {
            particles[i] = glm::vec3(ofRandom(-300, 300), ofRandom(-300, 300), ofRandom(-300, 300));
            particleVels[i] = glm::vec3(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)) * 2.0f;
            particleLife[i] = 0.0f;
        }
        
        // Apply noise-based force field
        float noiseX = ofNoise(particles[i].x * 0.01f, particles[i].y * 0.01f, t * 0.1f);
        float noiseY = ofNoise(particles[i].x * 0.01f + 100, particles[i].y * 0.01f, t * 0.1f);
        float noiseZ = ofNoise(particles[i].x * 0.01f, particles[i].y * 0.01f + 100, t * 0.1f);
        
        glm::vec3 noiseForce = glm::vec3(noiseX - 0.5f, noiseY - 0.5f, noiseZ - 0.5f) * 5.0f;
        particleVels[i] += noiseForce * ofGetLastFrameTime();
        particleVels[i] *= 0.98f; // damping
        
        // Update position
        particles[i] += particleVels[i];
    }
}

//--------------------------------------------------------------
void ofApp::drawParticles() {
    ofPushStyle();
    ofSetLineWidth(1.0f);
    
    for(int i = 0; i < maxParticles; i++) {
        float alpha = (1.0f - particleLife[i]) * 255.0f * 0.6f;
        ofSetColor(255, alpha);
        
        // Draw particle as small cross
        glm::vec3 p = particles[i];
        float size = 3.0f;
        
        ofDrawLine(p.x - size, p.y, p.z, p.x + size, p.y, p.z);
        ofDrawLine(p.x, p.y - size, p.z, p.x, p.y + size, p.z);
        ofDrawLine(p.x, p.y, p.z - size, p.x, p.y, p.z + size);
        
        // Connect nearby particles with lines
        for(int j = i + 1; j < maxParticles; j++) {
            float dist = glm::distance(particles[i], particles[j]);
            if(dist < 80.0f) {
                float lineAlpha = ofMap(dist, 0, 80, 100, 0) * (1.0f - particleLife[i]) * (1.0f - particleLife[j]);
                ofSetColor(255, lineAlpha);
                ofDrawLine(particles[i], particles[j]);
            }
        }
    }
    
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawNoiseField() {
    ofPushStyle();
    ofDisableDepthTest();
    ofSetLineWidth(1.0f);
    
    float t = ofGetElapsedTimef() - t0;
    int step = 15;
    
    for(int x = 0; x < ofGetWidth(); x += step) {
        for(int y = 0; y < ofGetHeight(); y += step) {
            float noiseVal = ofNoise(x * noiseScale, y * noiseScale, t * 0.2f);
            
            if(noiseVal > 0.6f) {
                float alpha = ofMap(noiseVal, 0.6f, 1.0f, 50, 150);
                ofSetColor(255, alpha);
                
                float angle = noiseVal * TWO_PI * 4.0f;
                float length = ofMap(noiseVal, 0.6f, 1.0f, 5, 12);
                
                float x1 = x + cos(angle) * length;
                float y1 = y + sin(angle) * length;
                float x2 = x - cos(angle) * length;
                float y2 = y - sin(angle) * length;
                
                ofDrawLine(x1, y1, x2, y2);
            }
        }
    }
    
    ofEnableDepthTest();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawGenerativeLines() {
    ofPushStyle();
    ofDisableDepthTest();
    ofSetLineWidth(1.0f);
    
    float t = ofGetElapsedTimef() - t0;
    
    // Flowing vertical lines
    for(int x = 0; x < ofGetWidth(); x += (int)lineSpacing) {
        float wave = sin(x * 0.01f + t * 2.0f) * 30.0f;
        float alpha = ofMap(abs(wave), 0, 30, 80, 20);
        ofSetColor(255, alpha);
        
        ofDrawLine(x + wave, 0, x + wave, ofGetHeight());
    }
    
    // Flowing horizontal lines
    for(int y = 0; y < ofGetHeight(); y += (int)lineSpacing) {
        float wave = cos(y * 0.01f + t * 1.5f) * 25.0f;
        float alpha = ofMap(abs(wave), 0, 25, 60, 15);
        ofSetColor(255, alpha);
        
        ofDrawLine(0, y + wave, ofGetWidth(), y + wave);
    }
    
    ofEnableDepthTest();
    ofPopStyle();
}

//--------------------------------------------------------------
ofApp::SuperParams ofApp::getEvolvedParams(float time, bool isTheta) {
    SuperParams params = isTheta ? thetaParams : phiParams;
    
    // Gentle, elegant evolution with golden ratio relationships
    float phi = 1.618034f; // golden ratio
    
    if(isTheta) {
        // Theta parameters - control outer shape symmetry
        params.m = ofMap(sin(time * 0.13f), -1, 1, 4.0f, 8.0f);
        params.n1 = ofMap(sin(time * 0.17f / phi), -1, 1, 0.2f, 1.5f);
        params.n2 = ofMap(sin(time * 0.19f), -1, 1, 0.2f, 1.5f);
        params.n3 = ofMap(sin(time * 0.23f * phi), -1, 1, 0.2f, 1.5f);
    } else {
        // Phi parameters - control profile/silhouette
        params.m = ofMap(sin(time * 0.11f + 1.0f), -1, 1, 2.0f, 6.0f);
        params.n1 = ofMap(sin(time * 0.14f / phi + 0.5f), -1, 1, 0.3f, 2.0f);
        params.n2 = ofMap(sin(time * 0.16f + 1.2f), -1, 1, 0.3f, 2.0f);
        params.n3 = ofMap(sin(time * 0.12f * phi + 0.8f), -1, 1, 0.3f, 2.0f);
    }
    
    return params;
}

//--------------------------------------------------------------
void ofApp::drawElegantObject() {
    float t = ofGetElapsedTimef() - t0;
    
    // Smooth camera animation
    if(cameraAnimation) {
        float camRadius = 380.0f + sin(t * 0.25f) * 80.0f;
        float camAngle = t * 0.15f;
        float camHeight = sin(t * 0.3f) * 100.0f;
        cam.setPosition(sin(camAngle) * camRadius, camHeight, cos(camAngle) * camRadius);
        cam.lookAt(glm::vec3(0, 0, 0));
    }
    
    // Elegant rotation with multiple axes
    if(elegantRotation) {
        ofRotateDeg(t * rotationSpeed * 0.8f, 0, 1, 0);
        ofRotateDeg(sin(t * 0.3f) * 25.0f, 1, 0, 0);
        ofRotateDeg(cos(t * 0.2f) * 15.0f, 0, 0, 1);
    }
    
    // Subtle breathing effect
    float breathing = 1.0f + sin(t * 2.5f) * breathingIntensity;
    ofScale(breathing);
    
    // Draw the beautiful morphing mesh
    mesh.drawWireframe();
    
    // Draw particles in 3D space for added beauty
    if(showParticles) {
        drawParticles();
    }
}

//--------------------------------------------------------------
ofApp::SuperParams ofApp::getWaveParams(float time, bool isTheta) {
    SuperParams params = isTheta ? thetaParams : phiParams;
    
    // Wave-like undulation through parameter space
    float wave1 = sin(time * 0.8f) * waveAmplitude;
    float wave2 = cos(time * 0.6f + PI/3) * waveAmplitude;
    float wave3 = sin(time * 0.4f + PI/2) * waveAmplitude;
    
    if(isTheta) {
        // Create flowing wave patterns
        params.m = 6.0f + wave1;
        params.n1 = 0.7f + wave2 * 0.3f;
        params.n2 = 0.8f + wave3 * 0.2f;
        params.n3 = 0.6f + sin(time * 0.9f) * 0.4f;
    } else {
        // Complementary wave motion for depth
        params.m = 4.0f + wave2;
        params.n1 = 1.2f + wave1 * 0.4f;
        params.n2 = 1.0f + wave3 * 0.3f;
        params.n3 = 1.1f + cos(time * 0.7f) * 0.5f;
    }
    
    return params;
}

//--------------------------------------------------------------
ofApp::SuperParams ofApp::getSpiralParams(float time, bool isTheta) {
    SuperParams params = isTheta ? thetaParams : phiParams;
    
    // Spiral fibonacci-like growth patterns
    float spiral = time * spiralTightness;
    float fib1 = sin(spiral * 1.618f) * 1.5f; // golden ratio
    float fib2 = cos(spiral * 2.618f) * 1.2f; // golden ratio squared
    float fib3 = sin(spiral * 0.618f) * 0.8f; // golden ratio inverse
    
    if(isTheta) {
        // Outer spiral structure
        params.m = 5.0f + fib1;
        params.n1 = 0.5f + abs(fib2) * 0.4f;
        params.n2 = 0.3f + abs(fib3) * 0.6f;
        params.n3 = 0.4f + sin(spiral * 3.0f) * 0.3f;
    } else {
        // Inner spiral counter-rotation
        params.m = 3.0f + fib2;
        params.n1 = 1.0f + abs(fib1) * 0.5f;
        params.n2 = 1.5f + abs(fib3) * 0.4f;
        params.n3 = 0.8f + cos(spiral * 2.0f) * 0.7f;
    }
    
    return params;
}

//--------------------------------------------------------------
ofApp::SuperParams ofApp::getOrganicParams(float time, bool isTheta) {
    SuperParams params = isTheta ? thetaParams : phiParams;
    
    // Organic growth like plants and flowers
    float growth = pow(sin(time * 0.3f) * 0.5f + 0.5f, 2.0f) * organicGrowth;
    float bloom = sin(time * 0.5f + PI/4) * 0.8f + 1.0f;
    float pulse = (sin(time * 2.0f) * 0.1f + 1.0f);
    
    // Use noise for natural variation
    float noiseX = ofNoise(time * 0.1f) * 2.0f;
    float noiseY = ofNoise(time * 0.1f + 100) * 2.0f;
    
    if(isTheta) {
        // Petal-like symmetry that grows and blooms
        params.m = 4.0f + growth * 2.0f + noiseX;
        params.n1 = 0.2f + bloom * 0.8f;
        params.n2 = 0.3f + growth * 1.2f;
        params.n3 = 0.4f + pulse * 0.6f + noiseY * 0.2f;
    } else {
        // Stem-like profile that supports the bloom
        params.m = 2.0f + growth + noiseY;
        params.n1 = 1.0f + bloom * 0.5f;
        params.n2 = 1.8f + growth * 0.3f;
        params.n3 = 1.2f + pulse * 0.4f + noiseX * 0.1f;
    }
    
    return params;
}

//--------------------------------------------------------------
ofApp::SuperParams ofApp::getMusicalParams(float time, bool isTheta) {
    SuperParams params = isTheta ? thetaParams : phiParams;
    
    // Musical rhythm and harmony-based animation
    float beat = fmod(time, 4.0f); // 4-beat measure
    float measure = floor(time / 4.0f);
    
    // Create musical intervals (octaves, fifths, fourths)
    float octave = sin(time * 2.0f) * 1.5f; // 2:1 ratio
    float fifth = sin(time * 3.0f / 2.0f) * 1.2f; // 3:2 ratio
    float fourth = sin(time * 4.0f / 3.0f) * 0.8f; // 4:3 ratio
    float major_third = sin(time * 5.0f / 4.0f) * 0.6f; // 5:4 ratio
    
    // Add rhythmic accents
    float accent = (beat < 1.0f) ? 1.5f : 1.0f;
    float syncopation = sin(beat * PI * 2.0f) * 0.3f;
    
    if(isTheta) {
        // Melodic line - higher frequencies
        params.m = 6.0f + octave * accent;
        params.n1 = 0.5f + abs(fifth) * 0.4f + syncopation;
        params.n2 = 0.7f + abs(major_third) * 0.5f;
        params.n3 = 0.3f + abs(fourth) * 0.6f;
    } else {
        // Bass line - lower, more stable
        params.m = 3.0f + fifth * accent * 0.5f;
        params.n1 = 1.2f + abs(fourth) * 0.3f;
        params.n2 = 1.5f + abs(octave) * 0.2f + syncopation * 0.5f;
        params.n3 = 0.9f + abs(major_third) * 0.4f;
    }
    
    return params;
}
