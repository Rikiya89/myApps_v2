// ofApp.cpp
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Load the image
    image.load("rose.jpg");
    width = image.getWidth();
    height = image.getHeight();

    // Set up the mesh with a reduced number of vertices
    mesh.setMode(OF_PRIMITIVE_LINES);  // Use lines instead of triangles for lighter rendering

    int stepSize = 10;  // Adjust step size to control mesh density

    // Create vertices at larger intervals
    for (float y = 0; y < height; y += stepSize) {
        for (float x = 0; x < width; x += stepSize) {
            float z = ofRandom(-20, 20);  // Randomize z position for cloud effect
            ofVec3f position(x - width / 2, y - height / 2, z); // Center the mesh
            mesh.addVertex(position);                           // Add vertex to mesh
            mesh.addTexCoord(ofVec2f(x, y));                    // Map texture coordinates
            mesh.addColor(image.getColor(x, y));                // Add color based on image pixel
        }
    }

    // Create lines to connect vertices
    for (float y = 0; y < height - stepSize; y += stepSize) {
        for (float x = 0; x < width - stepSize; x += stepSize) {
            int i1 = (x / stepSize) + (width / stepSize) * (y / stepSize);
            int i2 = ((x + stepSize) / stepSize) + (width / stepSize) * (y / stepSize);
            int i3 = (x / stepSize) + (width / stepSize) * ((y + stepSize) / stepSize);

            // Connect vertices with lines
            mesh.addIndex(i1);
            mesh.addIndex(i2);
            mesh.addIndex(i1);
            mesh.addIndex(i3);
        }
    }

    // Initialize particles
    for (int i = 0; i < 150; i++) {  // Increased particle count
        particles.push_back(ofVec3f(ofRandom(-width/2, width/2), ofRandom(-height/2, height/2), ofRandom(-50, 50)));
        velocities.push_back(ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-0.5, 0.5)));
    }

    // Load and play audio
    music.load("background.mp3");
    music.setLoop(true);
    music.play();

    nBandsToGet = 128;
    spectrum.assign(nBandsToGet, 0.0);

    // Initialize mouse attractor
    mouseAttractor = ofVec3f(0, 0, 0);
    previousMouse = mouseAttractor;  // Initial previous mouse position
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef();
    float speed = 0.05;  // Slower speed for less frequent updates

    // Update audio spectrum
    float* currentSpectrum = ofSoundGetSpectrum(nBandsToGet);
    for (int i = 0; i < nBandsToGet; i++) {
        spectrum[i] *= 0.97;  // Smooth spectrum
        spectrum[i] = max(spectrum[i], currentSpectrum[i]);
    }

    for (int i = 0; i < mesh.getNumVertices(); i++) {
        ofVec3f vertex = mesh.getVertex(i);
        float noise = ofNoise(vertex.x * 0.1, vertex.y * 0.1, time * speed);

        // Create a smooth wave effect based on audio spectrum
        float audioFactor = spectrum[i % nBandsToGet] * 50;
        vertex.z = ofMap(noise, 0, 1, -20, 20) + 10 * sin(vertex.x * 0.1 + time * 0.5) + audioFactor;

        mesh.setVertex(i, vertex);

        // Update color to create a spiritual glow with color harmony
        ofColor color = image.getColor(vertex.x + width / 2, vertex.y + height / 2);
        float hueShift = fmod(time * 5 + vertex.z, 255);  // Slower hue shift
        color.setHue(hueShift);
        color.a = 150 + 105 * sin(time + vertex.x * 0.1); // Pulsating glow
        mesh.setColor(i, color);
    }

    // Update particle positions with interaction
    for (int i = 0; i < particles.size(); i++) {
        ofVec3f direction = (mouseAttractor - particles[i]).normalized();

        // Add spiraling and trail effect to particles
        particles[i].x += velocities[i].x + direction.x * 0.1 + 0.5 * sin(time * 0.2 + i);
        particles[i].y += velocities[i].y + direction.y * 0.1 + 0.5 * cos(time * 0.2 + i);
        particles[i].z += velocities[i].z + direction.z * 0.1 + 0.5 * sin(time * 0.2 + i);

        velocities[i] *= 0.98;  // Slight damping for smooth motion

        // Bound check
        if (particles[i].x < -width / 2 || particles[i].x > width / 2) velocities[i].x *= -1;
        if (particles[i].y < -height / 2 || particles[i].y > height / 2) velocities[i].y *= -1;
        if (particles[i].z < -50 || particles[i].z > 50) velocities[i].z *= -1;
    }

    // Update mouse attractor to follow the mouse with a trail effect
    mouseAttractor.x = ofGetMouseX() - ofGetWidth() / 2;
    mouseAttractor.y = ofGetMouseY() - ofGetHeight() / 2;
    mouseAttractor.z = 50 * sin(time);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(20, 20, 70), ofColor(5, 5, 30), OF_GRADIENT_CIRCULAR);  // Deep spiritual gradient background
    ofPushMatrix();                       // Save the current coordinate system
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);  // Move the origin to the center

    // Smooth scaling effect for spiritual growth
    float scale = 1.0 + 0.1 * sin(ofGetElapsedTimef() * 0.5);  // Slow scaling for subtle growth
    ofScale(scale, scale, scale);

    // Rotate mesh around the Y-axis and X-axis for multidimensional effect
    ofRotateYDeg(ofGetElapsedTimef() * 5);
    ofRotateXDeg(ofGetElapsedTimef() * 2);  // Added X-axis rotation

    image.bind();                         // Bind the image for texture mapping
    mesh.draw();                          // Draw the mesh
    image.unbind();                       // Unbind the image

    // Draw particles with a subtle glow and trails
    ofSetColor(255, 255, 255, 150);  // White glow
    for (auto& particle : particles) {
        ofDrawCircle(particle, 2);  // Small circle for each particle
    }

    // Draw trails between current and previous mouse position
    ofSetColor(255, 255, 150, 50);  // Light trail color
    ofDrawLine(previousMouse.x, previousMouse.y, mouseAttractor.x, mouseAttractor.y);
    previousMouse = mouseAttractor;  // Update previous mouse position

    ofPopMatrix();                        // Restore the previous coordinate system
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Move attractor with arrow keys
    if (key == OF_KEY_LEFT

        )  mouseAttractor.x -= 10;
        if (key == OF_KEY_RIGHT) mouseAttractor.x += 10;
        if (key == OF_KEY_UP)    mouseAttractor.y -= 10;
        if (key == OF_KEY_DOWN)  mouseAttractor.y += 10;
        }

        //–––––––––––––––––––––––––––––––
        void ofApp::mouseMoved(int x, int y ){
        // Update mouse attractor to follow mouse position smoothly
        mouseAttractor.x = x - ofGetWidth() / 2;
        mouseAttractor.y = y - ofGetHeight() / 2;
        }
