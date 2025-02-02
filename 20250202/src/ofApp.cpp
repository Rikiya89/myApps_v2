#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    // We will draw a background gradient later, so set a default background color.
    ofBackground(10);
    ofEnableDepthTest();
    ofEnableSmoothing();

    // Setup a dynamic light.
    light.setup();
    light.setPosition(600, 600, 600);
    light.enable();
    ofEnableLighting();

    // Load the custom shader.
    // Make sure shader files are located in bin/data/shaders/
    shader.load("shaders/shader");

    // Create a high-resolution sphere.
    ofSpherePrimitive sphere;
    sphere.setRadius(200);
    sphere.setResolution(sphereResolution);

    // Get the sphere mesh and store a copy of its original vertices.
    sphereMesh = sphere.getMesh();
    baseVertices = sphereMesh.getVertices();

    // Initialize noise time offset.
    noiseTimeOffset = ofRandom(1000);

    // Initialize rotation and scaling.
    rotationAngle = 0.0f;
    globalScale = 1.0f;
}

//--------------------------------------------------------------
// This function computes fractal Brownian motion (fBm) by summing several octaves of noise.
float ofApp::fBm(const glm::vec3 &pos, float time, int octaves, float lacunarity, float gain) {
    float amplitude = 1.0;
    float frequency = 1.0;
    float sum = 0.0;
    for (int i = 0; i < octaves; i++){
        // Use ofNoise with position multiplied by the frequency and time added for animation.
        sum += amplitude * ofNoise(pos.x * frequency, pos.y * frequency, pos.z * frequency, time);
        amplitude *= gain;
        frequency *= lacunarity;
    }
    return sum;
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef();

    // Slowly increment the rotation angle.
    rotationAngle += 0.15;

    // Global scale pulsates gently.
    globalScale = 1.0 + 0.05 * sin(time * 1.5);

    // Update each vertex with multiple noise layers including fBm.
    vector<glm::vec3>& vertices = sphereMesh.getVertices();
    for (size_t i = 0; i < vertices.size(); i++){
        // Retrieve the original vertex position.
        glm::vec3 basePos = baseVertices[i];
        float originalLength = glm::length(basePos);

        // --- Dual Noise Deformation (Coarse and Fine) ---
        float noiseScale1 = 0.005;
        float noiseVal1 = ofNoise(basePos.x * noiseScale1,
                                  basePos.y * noiseScale1,
                                  basePos.z * noiseScale1,
                                  time * 0.3 + noiseTimeOffset);

        float noiseScale2 = 0.02;
        float noiseVal2 = ofNoise(basePos.x * noiseScale2,
                                  basePos.y * noiseScale2,
                                  basePos.z * noiseScale2,
                                  time * 0.8 + noiseTimeOffset);

        float offset1 = ofMap(noiseVal1, 0, 1, -20, 20);
        float offset2 = ofMap(noiseVal2, 0, 1, -5, 5);
        float combinedNoiseOffset = offset1 + offset2;

        // --- Fractal Noise (fBm) Deformation ---
        // Sum several octaves of noise to get fractal detail.
        // You can tweak octaves, lacunarity, and gain to achieve different textures.
        float fractalNoise = fBm(basePos, time * 0.5 + noiseTimeOffset, 4, 2.0, 0.5);
        float fractalOffset = ofMap(fractalNoise, 0, 1, -15, 15);

        // --- Pulsation Effect ---
        float pulsate = 10.0 * sin(time * 3.0 + originalLength * 0.1);

        // New radius: combine the original vertex length with all offsets.
        float newRadius = originalLength + combinedNoiseOffset + fractalOffset + pulsate;

        // Compute the new position along the original direction.
        glm::vec3 newPos = glm::normalize(basePos) * newRadius;

        // --- Enhanced Twist Effect ---
        // Vary the twist angle based on the vertex's Y value and time.
        float twistAngle = ofMap(sin(time * 2.0 + basePos.y * 0.02), -1, 1, -PI/6, PI/6);
        newPos = glm::rotate(newPos, twistAngle, glm::vec3(0, 1, 0));

        // Apply the global scaling.
        newPos *= globalScale;

        vertices[i] = newPos;
    }

    // Animate the light’s position for dynamic highlights.
    light.setPosition(600 * sin(time * 0.5), 600 * cos(time * 0.5), 600);
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Draw a soft background gradient.
    ofBackgroundGradient(ofColor(20, 20, 40), ofColor(0, 0, 0), OF_GRADIENT_CIRCULAR);

    // Enable additive blend mode for an ethereal glow.
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    cam.begin();

    // Activate the shader and pass uniform variables.
    shader.begin();
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    shader.setUniform3f("u_lightPos", light.getPosition());

    ofPushMatrix();
        // Center and rotate the sphere.
        ofTranslate(0, 0, 0);
        ofRotateDeg(rotationAngle, 0.3, 1.0, 0.2);

        // Draw the deformed sphere with slight translucency.
        ofSetColor(255, 255, 255, 200);
        sphereMesh.draw();
    ofPopMatrix();

    shader.end();
    cam.end();

    // Reset blend mode.
    ofDisableBlendMode();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Press 's' to save a screenshot.
    if(key == 's'){
        ofSaveScreen("fractal_screenshot_" + ofGetTimestampString() + ".png");
    }
}
