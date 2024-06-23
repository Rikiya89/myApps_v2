#include "ofApp.h"

void ofApp::setup(){
    // Load the image
    image.load("jellyfish.jpg");

    // Create a grid mesh
    int width = image.getWidth();
    int height = image.getHeight();
    int stepSize = 5;  // Decreasing step size for more detail

    for (int y = 0; y < height; y += stepSize) {
        for (int x = 0; x < width; x += stepSize) {
            // Get the color of the pixel
            ofColor color = image.getColor(x, y);
            // Use the brightness of the pixel to set the z coordinate
            float z = ofMap(color.getBrightness(), 0, 255, -100, 100);
            // Add the vertex to the mesh
            mesh.addVertex(ofPoint(x - width / 2, y - height / 2, z));
            mesh.addColor(color);
        }
    }

    // Create indices for the mesh
    for (int y = 0; y < height - stepSize; y += stepSize) {
        for (int x = 0; x < width - stepSize; x += stepSize) {
            int i1 = x / stepSize + y / stepSize * (width / stepSize);
            int i2 = (x + stepSize) / stepSize + y / stepSize * (width / stepSize);
            int i3 = x / stepSize + (y + stepSize) / stepSize * (width / stepSize);
            int i4 = (x + stepSize) / stepSize + (y + stepSize) / stepSize * (width / stepSize);

            mesh.addIndex(i1);
            mesh.addIndex(i2);
            mesh.addIndex(i3);
            mesh.addIndex(i2);
            mesh.addIndex(i4);
            mesh.addIndex(i3);
        }
    }

    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    // Set up lighting
    light1.setPosition(0, 0, 600);  // Position the first light source
    light1.setDiffuseColor(ofColor(255, 204, 204));  // Soft red light
    light1.setSpecularColor(ofColor(255, 255, 255));  // White specular highlight

    light2.setPosition(600, 600, 600);  // Position the second light source
    light2.setDiffuseColor(ofColor(204, 204, 255));  // Soft blue light
    light2.setSpecularColor(ofColor(255, 255, 255));  // White specular highlight

    light1.enable();
    light2.enable();

    // Initialize time for animation
    time = 0.0;

    // Set up GUI
    gui.setup();  // Default setup
    gui.add(camPosX.setup("Camera X", 0, -1000, 1000));
    gui.add(camPosY.setup("Camera Y", 0, -1000, 1000));
    gui.add(camPosZ.setup("Camera Z", 600, -1000, 2000));
    gui.add(camRotX.setup("Camera Rotate X", 0, -180, 180));
    gui.add(camRotY.setup("Camera Rotate Y", 0, -180, 180));
    gui.add(camRotZ.setup("Camera Rotate Z", 0, -180, 180));
}

void ofApp::update(){
    time += ofGetLastFrameTime();  // Update time based on frame time

    int width = image.getWidth();
    int height = image.getHeight();
    int stepSize = 5;

    // Update vertices to create a complex wave-like animation
    for (int y = 0; y < height; y += stepSize) {
        for (int x = 0; x < width; x += stepSize) {
            int index = x / stepSize + y / stepSize * (width / stepSize);
            ofPoint vertex = mesh.getVertex(index);
            float z = ofMap(image.getColor(x, y).getBrightness(), 0, 255, -100, 100);
            float wave1 = sin(x * 0.05 + time) * 10.0;
            float wave2 = cos(y * 0.05 + time) * 10.0;
            vertex.z = z + wave1 + wave2;
            mesh.setVertex(index, vertex);

            // Add subtle color change over time
            ofColor color = image.getColor(x, y);
            int hue = (int(color.getHue()) + int(time * 10)) % 255;  // Ensure hue is an integer and within 0-255
            color.setHue(hue);
            mesh.setColor(index, color);
        }
    }
}

void ofApp::draw(){
    ofBackground(0);

    // Enable depth testing to render 3D correctly
    ofEnableDepthTest();

    // Adjust camera based on GUI input
    easyCam.setPosition(camPosX, camPosY, camPosZ);
    easyCam.setTarget(ofVec3f(0, 0, 0));  // Optional, keep camera looking at the origin
    easyCam.setOrientation(ofVec3f(camRotX, camRotY, camRotZ));

    easyCam.begin();
    light1.enable();
    light2.enable();
    mesh.draw();
    light1.disable();
    light2.disable();
    easyCam.end();

    ofDisableDepthTest();

    // Draw the GUI
    gui.draw();
}

void ofApp::keyPressed(int key) {
    // You can add specific key controls here if needed
}

void ofApp::keyReleased(int key) {
    // You can add specific key controls here if needed
}

void ofApp::mouseDragged(int x, int y, int button) {
    // Let the easyCam handle the mouse dragging
}

void ofApp::mousePressed(int x, int y, int button) {
    // Let the easyCam handle the mouse press
}

void ofApp::mouseReleased(int x, int y, int button) {
    // Let the easyCam handle the mouse release
}
