#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetBackgroundAuto(true);

    // Precompute the heart shape vertices (using a coarser step for performance).
    for (float t = 0; t <= TWO_PI; t += 0.05) {
        float px = 16 * pow(sin(t), 3);
        float py = 13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t);
        // Invert y to orient the heart correctly.
        heartShape.push_back(ofVec2f(px, -py));
    }

    // Initialize hearts.
    numHearts = 50;
    hearts.reserve(numHearts);
    for (int i = 0; i < numHearts; i++){
        Heart heart;
        heart.pos = ofVec2f(ofRandomWidth(), ofRandomHeight());
        heart.baseSize = ofRandom(0.5, 2.0);
        heart.vel = ofVec2f(0, ofRandom(0.5, 2.0));
        heart.phase = ofRandom(TWO_PI);
        hearts.push_back(heart);
    }

    // Initialize petals.
    numPetals = 30;
    petals.reserve(numPetals);
    for (int i = 0; i < numPetals; i++){
        Petal petal;
        petal.pos = ofVec2f(ofRandomWidth(), ofRandom(-ofGetHeight(), ofGetHeight()));
        petal.vel = ofVec2f(ofRandom(-0.2, 0.2), ofRandom(0.3, 1.0));
        petal.angle = ofRandom(0, 360);
        petal.angularVelocity = ofRandom(-0.5, 0.5);
        petal.scale = ofRandom(0.5, 1.5);
        petals.push_back(petal);
    }
}

void ofApp::update(){
    float deltaTime = ofGetLastFrameTime();

    // Update hearts and spawn sparkles.
    for (auto &heart : hearts) {
        // Append current position to the trail.
        heart.trail.push_back(heart.pos);
        if (heart.trail.size() > 15) {
            heart.trail.erase(heart.trail.begin());
        }

        // Update heart position.
        heart.pos += heart.vel;
        if (heart.pos.y - 100 * heart.baseSize > ofGetHeight()){
            heart.pos.y = -100 * heart.baseSize;
            heart.pos.x = ofRandomWidth();
            heart.trail.clear();
        }

        // Spawn sparkles near the heart.
        if (ofRandom(1) < 0.05) { // 5% chance each frame per heart
            Sparkle s;
            s.pos = heart.pos + ofVec2f(ofRandom(-10, 10), ofRandom(-10, 10));
            s.vel = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
            s.maxLife = s.life = ofRandom(0.5, 1.5);
            sparkles.push_back(s);
        }
    }

    // Update sparkles.
    for (auto it = sparkles.begin(); it != sparkles.end(); ) {
        it->pos += it->vel;
        it->life -= deltaTime;
        if (it->life <= 0) {
            it = sparkles.erase(it);
        } else {
            ++it;
        }
    }

    // Update petals.
    for (auto &petal : petals) {
        petal.pos += petal.vel;
        petal.angle += petal.angularVelocity;
        // If a petal drifts below the screen, reset it to the top.
        if (petal.pos.y > ofGetHeight() + 20) {
            petal.pos.y = -20;
            petal.pos.x = ofRandomWidth();
        }
    }
}

void ofApp::draw(){
    // Draw the animated gradient background.
    drawGradientBackground();

    // Draw petals behind the hearts.
    for (auto &petal : petals) {
        ofPushMatrix();
        ofTranslate(petal.pos.x, petal.pos.y);
        ofRotateDeg(petal.angle);
        ofScale(petal.scale, petal.scale);
        ofSetColor(255, 182, 193, 180); // Soft, light pink with transparency.
        ofFill();
        ofDrawEllipse(0, 0, 10, 20);
        ofPopMatrix();
    }

    // Draw trails for each heart.
    for (auto &heart : hearts) {
        int trailSize = heart.trail.size();
        for (int i = 0; i < trailSize; i++){
            float trailAlpha = ofMap(i, 0, trailSize - 1, 50, 200);
            float trailScale = heart.baseSize * (1.0 + 0.1 * (i / (float)trailSize));
            ofSetColor(255, 0, 0, trailAlpha);
            drawHeart(heart.trail[i].x, heart.trail[i].y, trailScale);
        }
    }

    // Draw each heart with pulsation, glow, and drop shadow.
    for (auto &heart : hearts) {
        float pulsate = 1.0 + 0.2 * sin(ofGetElapsedTimef() * 2 + heart.phase);
        float currentSize = heart.baseSize * pulsate;

        // Draw drop shadow.
        ofSetColor(0, 0, 0, 50);
        drawHeart(heart.pos.x + 5, heart.pos.y + 5, currentSize);

        // Draw layered glow effect.
        for (int i = 0; i < 5; i++){
            float glowScale = currentSize * (1.0 + i * 0.05);
            float glowAlpha = 200 / (i + 2);
            ofSetColor(255, 0, 0, glowAlpha);
            drawHeart(heart.pos.x, heart.pos.y, glowScale);
        }

        // Draw the main heart.
        ofSetColor(255, 0, 0, 255);
        drawHeart(heart.pos.x, heart.pos.y, currentSize);
    }

    // Draw sparkles with additive blending for extra luminosity.
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (auto &sparkle : sparkles) {
        float alpha = ofMap(sparkle.life, 0, sparkle.maxLife, 0, 255);
        ofSetColor(255, 255, 255, alpha);
        float radius = ofMap(sparkle.life, 0, sparkle.maxLife, 0, 3);
        ofDrawCircle(sparkle.pos.x, sparkle.pos.y, radius);
    }
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
}

void ofApp::drawGradientBackground(){
    float time = ofGetElapsedTimef();
    float variation = sin(time * 0.2) * 0.05;
    ofFloatColor topColor(1.0, 0.9 + variation, 0.95);
    ofFloatColor bottomColor(1.0, 0.7 + variation, 0.8);

    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mesh.addColor(topColor);
    mesh.addVertex(ofVec3f(0, 0, 0));
    mesh.addColor(topColor);
    mesh.addVertex(ofVec3f(ofGetWidth(), 0, 0));
    mesh.addColor(bottomColor);
    mesh.addVertex(ofVec3f(0, ofGetHeight(), 0));
    mesh.addColor(bottomColor);
    mesh.addVertex(ofVec3f(ofGetWidth(), ofGetHeight(), 0));
    mesh.draw();
}

void ofApp::drawHeart(float x, float y, float scale){
    ofPushMatrix();
    ofTranslate(x, y);
    // Apply a gentle rotation for added organic movement.
    float rotation = sin(ofGetElapsedTimef() + x * 0.01) * 5; // ±5° rotation.
    ofRotateDeg(rotation);
    ofScale(scale, scale);

    ofBeginShape();
    // Use the precomputed heart shape vertices.
    for (auto &pt : heartShape) {
        ofVertex(pt.x, pt.y);
    }
    ofEndShape();

    ofPopMatrix();
}
