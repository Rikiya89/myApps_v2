#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    displacementAmount = 100.0;

    // Load the texture
    texture.load("chry.jpg");

    // Setup the mesh as a point cloud with reduced resolution
    int step = 4; // Increase the step to reduce the number of points
    int width = texture.getWidth();
    int height = texture.getHeight();
    mesh.setMode(OF_PRIMITIVE_POINTS);

    // Create vertices and texture coordinates with step size
    for (int y = 0; y < height; y += step){
        for (int x = 0; x < width; x += step){
            ofVec3f vertex = ofVec3f(x - width/2, y - height/2, 0);
            mesh.addVertex(vertex);
            mesh.addTexCoord(ofVec2f(x, y));
        }
    }

    // Enable point smoothing
    glEnable(GL_POINT_SMOOTH);
    glPointSize(4); // Set the point size larger to compensate for fewer points
}

//--------------------------------------------------------------
void ofApp::update(){
    // Displace the vertices to create a generative effect with optimized noise
    float time = ofGetElapsedTimef(); // Get elapsed time for animation dynamics
    for (int i = 0; i < mesh.getNumVertices(); i++) {
        ofVec3f vertex = mesh.getVertex(i);

        // Animate vertices with a spiral pattern combined with noise
        float noise = ofNoise(vertex.x * 0.01, vertex.y * 0.01, time * 0.3);
        float radius = 50 + noise * displacementAmount;

        // Spiral motion
        vertex.x += cos(time + vertex.y * 0.05) * radius * 0.01;
        vertex.y += sin(time + vertex.x * 0.05) * radius * 0.01;
        vertex.z = noise * displacementAmount;

        mesh.setVertex(i, vertex);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0); // Black background
    ofEnableDepthTest();

    // Apply texture
    texture.bind();

    // Center and rotate the point cloud for a better view
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);

    // Dynamic rotation and scaling
    ofRotateXDeg(ofGetElapsedTimef() * 20);
    ofRotateYDeg(ofGetElapsedTimef() * 30);
    float scale = 1.0 + 0.5 * sin(ofGetElapsedTimef() * 0.5); // Smooth scaling effect
    ofScale(scale, scale, scale);

    // Set a static color for the points
    ofSetColor(255, 255, 255);  // White points for contrast

    mesh.drawVertices();  // Draw the mesh as points

    ofPopMatrix();

    texture.unbind();
    ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Increase/decrease displacement amount with UP/DOWN keys
    if (key == OF_KEY_UP) displacementAmount += 10;
    if (key == OF_KEY_DOWN) displacementAmount -= 10;
}
