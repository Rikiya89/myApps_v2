#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(12, 10, 26, 255);
    ofEnableDepthTest();
    ofEnableAlphaBlending();

    numPoints = 180;  // Dense for flower/nebula
    generateFibonacciSphere();
    time = 0.0;
}

void ofApp::update(){
    time += 0.018;
}

void ofApp::generateFibonacciSphere(){
    geoPoints.clear();
    float offset = 2.0 / numPoints;
    float increment = PI * (3.0 - sqrt(5.0));
    for(int i=0; i<numPoints; i++) {
        float y = ((i * offset) - 1) + (offset / 2);
        float r = sqrt(1 - y * y);
        float phi = i * increment;
        float x = cos(phi) * r;
        float z = sin(phi) * r;
        geoPoints.push_back({glm::vec3(x, y, z), phi, acos(y)});
    }
}

ofColor ofApp::getCosmicColor(float t, float time){
    // Nebula rainbow + chakra accent
    float hue = fmod(t + time * 0.12 + 0.45 * sin(PI * t + time * 0.15), 1.0) * 255;
    float sat = 200 + 55 * sin(time * 0.33 + t * 7.0);
    float bri = 180 + 75 * sin(time * 0.19 - t * 13.0);
    return ofColor::fromHsb(hue, sat, bri, 192);
}

ofColor ofApp::getChakraColor(float t){
    ofColor chakra[7] = {
        ofColor(228,44,39),    // Red
        ofColor(247,148,29),   // Orange
        ofColor(255,239,60),   // Yellow
        ofColor(42,191,77),    // Green
        ofColor(41,120,206),   // Blue
        ofColor(120,82,180),   // Indigo
        ofColor(202,83,174)    // Violet
    };
    float idx = t * 6.0f;
    int i0 = floor(idx);
    int i1 = (i0 + 1) % 7;
    float frac = idx - i0;
    return chakra[i0].getLerped(chakra[i1], frac);
}

void ofApp::draw(){
    // Cinematic, floating camera motion
    float orbit = 200 + sin(time * 0.31) * 60;
    float tilt  = 70 + cos(time * 0.16) * 25;
    float dist  = 500 + 160 * sin(time * 0.22 + 1.1);
    cam.orbitDeg(orbit, tilt, dist, glm::vec3(0,0,0));
    cam.begin();

    // Glowing afterimage: draw transparent background for trail effect
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(12,10,26, 34); // semi-transparent
    ofDrawBox(0,0,0, 2200,2200,2200);

    // Main nebula / sacred geometry
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    float pulse = 0.55f + 0.45f * sin(time * 1.05);
    float rippleSpeed = 2.2 + 1.2 * sin(time*0.13);
    float ripplePhase = time * 0.73;

    for(int i=0; i<geoPoints.size(); i++){
        auto& gp = geoPoints[i];

        // Position with breathing and floating
        float baseR = 240 + 85 * sin(time*0.18 + i * 0.11);
        float radius = baseR + 40.0f * pulse * sin(i * 0.09 + time * 0.61);
        glm::vec3 pos = gp.pos * radius;

        // Ripple scale for heartbeat
        float d = glm::length(pos) / (baseR + 60);
        float ripple = 0.7 + 1.4 * exp(-pow((d - 0.5 - 0.5 * sin(ripplePhase + d * rippleSpeed)),2) * 8.5);

        float scale = 13.5 * ripple * (0.95 + 0.35 * sin(time*1.12 + i * 0.21));

        // Animate rotation/orientation
        float rotAmt = time*43 + 360*gp.phi + 50*ripple*d;
        ofPushMatrix();
        ofTranslate(pos);

        ofRotateYDeg(rotAmt * 0.21);
        ofRotateXDeg(rotAmt * 0.13);
        ofRotateZDeg(rotAmt * 0.09);

        // Color: rainbow/nebula plus chakra accent
        float t = float(i) / geoPoints.size();
        ofColor c = getCosmicColor(t, time).lerp(getChakraColor(t), 0.24f + 0.18f * sin(time + t*9.7));
        c.a = 170 + 70 * pulse * (1.0f - d);

        ofSetColor(c);

        // Morphing shape: box, sphere, torus, icosahedron
        float m = fmod(time*0.13 + i * 0.042, 1.0);
        if (m < 0.33)      ofDrawBox(scale, scale*0.8, scale*1.2);
        else if (m < 0.66) ofDrawSphere(scale*0.93);
        else               ofDrawIcoSphere(scale*0.8);

        // Add a small "star" for cosmic vibe
        ofSetColor(255,255,255, 38 + 78*pow(pulse,2));
        ofDrawSphere(scale*0.38);

        ofPopMatrix();
    }

    ofDisableBlendMode();
    cam.end();
}

void ofApp::keyPressed(int key){
    if (key == 's') ofSaveFrame();
}
