#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Load the image
    image.load("dahlia.jpg");

    // Allocate the mesh
    mesh.setMode(OF_PRIMITIVE_POINTS);

    // Get the image dimensions
    int width = image.getWidth();
    int height = image.getHeight();

    // Reduce the vertex count by skipping pixels
    int skip = 4; // Number of pixels to skip

    // Loop through each pixel in the image with a step of 'skip'
    for (int y = 0; y < height; y += skip) {
        for (int x = 0; x < width; x += skip) {
            // Get the pixel color
            ofColor color = image.getColor(x, y);

            // Calculate brightness as a height value
            float brightness = color.getBrightness();
            float z = ofMap(brightness, 0, 255, -50, 50); // Map brightness to a height

            // Create a vertex with the x, y, z positions
            glm::vec3 position(x, y, z);
            mesh.addVertex(position);

            // Set the vertex color based on the image color
            mesh.addColor(color);
        }
    }

    // Enable depth testing for 3D effect
    ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update(){
    // Get the current time
    float time = ofGetElapsedTimef();

    // Update each vertex color and position to create a beautiful animation
    for (int i = 0; i < mesh.getNumVertices(); ++i) {
        // Get current vertex position and color
        glm::vec3 vertex = mesh.getVertex(i);
        ofColor color = mesh.getColor(i);

        // Calculate distance from the center
        float distance = glm::length(glm::vec2(vertex.x - image.getWidth() / 2, vertex.y - image.getHeight() / 2));

        // Apply a sine wave function for color shift
        float hueShift = sin(time * 0.5 + distance * 0.01) * 10; // Slight hue shift
        color.setHue(fmod(color.getHue() + hueShift, 255)); // Keep hue in the range [0, 255]

        // Add subtle movement to simulate a breeze or wave effect
        float wave = sin(time * 0.8 + distance * 0.02) * 2.0;
        vertex.z = mesh.getVertex(i).z + wave; // Apply wave effect to z position
        vertex.x += sin(time * 0.3 + vertex.y * 0.01) * 0.5; // Slight x movement
        vertex.y += cos(time * 0.3 + vertex.x * 0.01) * 0.5; // Slight y movement

        // Update vertex color and position in the mesh
        mesh.setColor(i, color);
        mesh.setVertex(i, vertex);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Set a layered background gradient for enhanced depth
    ofBackgroundGradient(ofColor(20, 20, 50), ofColor(5, 5, 20), OF_GRADIENT_CIRCULAR);

    // Begin camera
    cam.begin();

    // Translate the mesh to center
    ofPushMatrix();
    // Translate mesh to be centered in the view
    ofTranslate(-image.getWidth() / 2, -image.getHeight() / 2, 0);

    // Set point size for the vertices
    glEnable(GL_POINT_SMOOTH);
    glPointSize(3.0); // Use a single point size for all vertices

    // Draw the entire mesh
    mesh.draw();

    ofPopMatrix();

    // End camera
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
