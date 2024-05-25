#include "ofApp.h"

void ofApp::setup(){
    ofBackground(0);
    birdImage.load("bird.jpg"); // Load the image

    imgWidth = birdImage.getWidth();
    imgHeight = birdImage.getHeight();

    mesh.setMode(OF_PRIMITIVE_POINTS);
    ofEnableDepthTest();
    glEnable(GL_POINT_SMOOTH); // Enable point smoothing
    glPointSize(3); // Set default point size

    // Reduce the number of vertices for better performance
    int stepSize = 4; // Adjust the step size to reduce vertices

    for (int y = 0; y < imgHeight; y += stepSize) {
        for (int x = 0; x < imgWidth; x += stepSize) {
            ofColor color = birdImage.getColor(x, y);
            if (color.a > 0) {
                float brightness = color.getBrightness();
                float z = ofMap(brightness, 0, 255, -100, 100);
                mesh.addVertex(glm::vec3(x - imgWidth / 2, y - imgHeight / 2, z));
                color.a = ofMap(brightness, 0, 255, 50, 255); // Vary alpha based on brightness
                mesh.addColor(color);
            }
        }
    }

    // Set up the light
    light.setPosition(200, 300, 300);
    light.setDiffuseColor(ofFloatColor(1.0, 1.0, 1.0)); // Increase the light intensity
    light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));
    light.setAmbientColor(ofFloatColor(0.3, 0.3, 0.3)); // Add ambient light
    light.enable();

    time = 0; // Initialize the time variable
    amplitude = 50; // Initial amplitude
    frequency = 0.05; // Initial frequency
    rotationAngle = 0; // Initial rotation angle
    colorCycle = 0; // Initialize color cycle variable
    animationSpeed = 1.0; // Initial animation speed
}

void ofApp::update(){
    time += ofGetLastFrameTime() * animationSpeed; // Update the time variable based on frame time and animation speed

    // Vary amplitude and frequency over time
    amplitude = 50 + 20 * sin(time * 0.5);
    frequency = 0.05 + 0.02 * cos(time * 0.3);

    // Animate the vertices with multiple waves
    for (int i = 0; i < mesh.getNumVertices(); ++i) {
        glm::vec3 vertex = mesh.getVertex(i);
        float z1 = amplitude * sin(time + vertex.x * frequency + vertex.y * frequency);
        float z2 = amplitude * cos(time + vertex.x * frequency * 1.5 + vertex.y * frequency * 1.5);
        vertex.z = (z1 + z2) / 2; // Combine multiple waves
        mesh.setVertex(i, vertex);
    }

    // Update rotation angle
    rotationAngle += 10 * ofGetLastFrameTime() * animationSpeed;

    // Cycle colors over time
    colorCycle += ofGetLastFrameTime() * animationSpeed;
    for (int i = 0; i < mesh.getNumColors(); ++i) {
        ofFloatColor color = mesh.getColor(i);
        color.setHue(fmod(colorCycle + i * 0.01, 1.0)); // Cycle hue over time
        mesh.setColor(i, color);
    }
}

void ofApp::draw(){
    cam.begin();
    ofEnableLighting(); // Enable lighting
    light.enable();
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotateDeg(rotationAngle, 0, 1, 0); // Rotate around the Y axis
    mesh.draw();
    ofPopMatrix();
    light.disable();
    ofDisableLighting(); // Disable lighting
    cam.end();
}

void ofApp::keyPressed(int key) {
    if (key == 'f') {
        ofToggleFullscreen();
    } else if (key == OF_KEY_UP) {
        animationSpeed += 0.1; // Increase animation speed
    } else if (key == OF_KEY_DOWN) {
        animationSpeed -= 0.1; // Decrease animation speed
        if (animationSpeed < 0.1) animationSpeed = 0.1; // Prevent negative speed
    } else if (key == OF_KEY_LEFT) {
        amplitude -= 5; // Decrease amplitude
        if (amplitude < 0) amplitude = 0; // Prevent negative amplitude
    } else if (key == OF_KEY_RIGHT) {
        amplitude += 5; // Increase amplitude
    }
}
