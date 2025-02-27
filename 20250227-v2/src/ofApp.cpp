#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Increase window size or keep as is
    ofSetWindowShape(720, 1080);

    // Lighten the background gradient
    ofBackgroundGradient(ofColor(50), ofColor(90), OF_GRADIENT_CIRCULAR);
    ofSetFrameRate(60);

    // Enable 3D features
    ofEnableDepthTest();
    ofEnableSmoothing();
    ofEnableLighting();

    // First light (key light)
    light1.setup();
    // Keep diffuse at max white
    light1.setDiffuseColor(ofColor(255));
    // Raise ambient to illuminate the mesh more
    light1.setAmbientColor(ofColor(150));
    // Strong specular highlights
    light1.setSpecularColor(ofColor(255));

    // Second light (fill light)
    light2.setup();
    // Slightly lower diffuse than key light
    light2.setDiffuseColor(ofColor(230));
    // Increase ambient to fill in shadows
    light2.setAmbientColor(ofColor(120));
    light2.setSpecularColor(ofColor(255));

    // Material settings for reflective shine
    material.setShininess(64);
    material.setSpecularColor(ofColor(255));

    // Increase grid resolution for finer detail
    gridCols = 60;
    gridRows = 60;
    spacing = 15;

    // Set the mesh to draw filled triangles
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    // Build a centered grid of vertices with an initial white color
    for (int y = 0; y < gridRows; y++){
        for (int x = 0; x < gridCols; x++){
            float xpos = (x - gridCols / 2) * spacing;
            float ypos = (y - gridRows / 2) * spacing;
            mesh.addVertex(ofVec3f(xpos, ypos, 0));
            mesh.addColor(ofColor(255));
        }
    }

    // Create a triangulated grid: each cell forms two triangles
    for (int y = 0; y < gridRows - 1; y++){
        for (int x = 0; x < gridCols - 1; x++){
            int topLeft = y * gridCols + x;
            int topRight = topLeft + 1;
            int bottomLeft = topLeft + gridCols;
            int bottomRight = bottomLeft + 1;

            // First triangle
            mesh.addIndex(topLeft);
            mesh.addIndex(bottomLeft);
            mesh.addIndex(topRight);

            // Second triangle
            mesh.addIndex(topRight);
            mesh.addIndex(bottomLeft);
            mesh.addIndex(bottomRight);
        }
    }

    time = 0.0f;
}
//--------------------------------------------------------------
void ofApp::update(){
    // Update animation time
    time = ofGetElapsedTimef();

    // Animate light positions:
    // Light 1 follows a slow circular path
    float lx1 = sin(time * 0.5) * 250;
    float ly1 = cos(time * 0.5) * 250;
    float lz1 = 300 + sin(time * 0.3) * 100;
    light1.setPosition(lx1, ly1, lz1);

    // Light 2 moves along a complementary path for softer fill lighting
    float lx2 = cos(time * 0.4) * 200;
    float ly2 = sin(time * 0.4) * 200;
    float lz2 = 250 + cos(time * 0.5) * 80;
    light2.setPosition(lx2, ly2, lz2);

    // Parameters for vertex modulation
    float noiseScale = 0.12f;
    float amplitude = 120.0f;
    int numVertices = mesh.getNumVertices();

    for (int i = 0; i < numVertices; i++){
        ofVec3f v = mesh.getVertex(i);

        // Base noise displacement
        float noiseVal = ofNoise(v.x * noiseScale, v.y * noiseScale, time);

        // Sine-cosine modulation for organic, abstract motion
        float sineFactor = sin(v.x * 0.05 + time) * cos(v.y * 0.05 + time);
        float cosFactor = cos(v.y * 0.05 + time);

        // Additional radial ripple based on distance from the center
        float dist = v.length();
        float ripple = sin(dist * 0.1 + time) * 20;

        // Combine influences for the z-displacement
        v.z = ofMap(noiseVal, 0, 1, -amplitude, amplitude)
              + sineFactor * 50
              + cosFactor * 30
              + ripple;
        mesh.setVertex(i, v);

        // Set vertex color using thresholded brightness for striking contrast
        float brightness = ofMap(noiseVal, 0, 1, 0, 255);

        // Lower the bar for white
        if (brightness > 80) {
            // anything above 80 becomes white
            mesh.setColor(i, ofColor(255));
        }
        // optional mid range: from 40 to 80
        else if (brightness > 40) {
            mesh.setColor(i, ofColor(200)); // a light gray
        }
        // below 40, dark gray (not fully black)
        else {
            mesh.setColor(i, ofColor(80));
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Refresh background with gradient
    ofBackgroundGradient(ofColor(150), ofColor(255), OF_GRADIENT_CIRCULAR);
    cam.begin();

    ofPushMatrix();
    // Apply multi-axis rotations for a dynamic, shifting perspective
    ofRotateDeg(time * 20, 0, 1, 0);       // Y-axis rotation
    ofRotateDeg(sin(time) * 30, 1, 0, 0);    // X-axis oscillation
    ofRotateDeg(cos(time) * 15, 0, 0, 1);    // Z-axis subtle twist

    // Apply the material before drawing the mesh to get reflective lighting
    material.begin();
    mesh.draw();
    material.end();

    // Overlay a glowing wireframe for an ethereal effect
    // Overlay a glowing wireframe
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    // Full alpha for a bright white
    ofSetColor(255, 255);
    for (int i = 0; i < 3; i++){
        ofPushMatrix();
        ofTranslate(sin(time * (i+1)) * 2, cos(time * (i+1)) * 2, 0);
        mesh.drawWireframe();
        ofPopMatrix();
    }
    ofDisableBlendMode();

    ofPopMatrix();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::exit(){
    ofDisableLighting();
    ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){ }
void ofApp::keyReleased(int key){ }
void ofApp::mouseMoved(int x, int y){ }
void ofApp::mouseDragged(int x, int y, int button){ }
void ofApp::mousePressed(int x, int y, int button){ }
void ofApp::mouseReleased(int x, int y, int button){ }
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){ }
void ofApp::mouseEntered(int x, int y){ }
void ofApp::mouseExited(int x, int y){ }
void ofApp::windowResized(int w, int h){ }
void ofApp::dragEvent(ofDragInfo dragInfo){ }
void ofApp::gotMessage(ofMessage msg){ }
