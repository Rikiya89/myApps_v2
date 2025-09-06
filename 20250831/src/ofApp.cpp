#include "ofApp.h"

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

    // Seed parameters (Gielis superformula)
    thetaParams = {7.0f, 1.0f, 1.0f, 0.3f, 0.3f, 0.3f};
    phiParams   = {3.0f, 1.0f, 1.0f, 0.2f, 1.7f, 1.7f};

    buildMesh(thetaParams, phiParams);
    t0 = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
    float t = ofGetElapsedTimef() - t0;

    if (animate) {
        // Evolve parameters smoothly over time for generative motion
        SuperParams a = thetaParams;
        SuperParams b = phiParams;

        // Vary m terms around integers for symmetry-rich transitions
        a.m = ofMap(sin(t * 0.17f), -1, 1, 2.0f, 10.0f);
        b.m = ofMap(sin(t * 0.11f + 2.1f), -1, 1, 2.0f, 9.0f);

        // Morph shape sharpness
        a.n1 = ofMap(sin(t * 0.21f + 0.7f), -1, 1, 0.15f, 1.8f);
        a.n2 = ofMap(sin(t * 0.19f + 1.3f), -1, 1, 0.15f, 1.8f);
        a.n3 = ofMap(sin(t * 0.23f + 2.9f), -1, 1, 0.15f, 1.8f);

        b.n1 = ofMap(sin(t * 0.14f + 0.3f), -1, 1, 0.15f, 1.8f);
        b.n2 = ofMap(sin(t * 0.16f + 0.9f), -1, 1, 0.15f, 1.8f);
        b.n3 = ofMap(sin(t * 0.12f + 1.7f), -1, 1, 0.15f, 1.8f);

        buildMesh(a, b);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Gentle fade to black for motion trails (black/white only)
    if (trails) {
        ofPushStyle();
        ofDisableDepthTest(); // avoid writing to depth buffer with the 2D fade quad
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofSetColor(0, 0, 0, trailFade); // configurable alpha to control trail length
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        ofPopStyle();
        // Clear depth buffer so 3D geometry is visible this frame
        glClear(GL_DEPTH_BUFFER_BIT);
        ofEnableDepthTest();
    } else {
        ofBackground(0);
    }

    ofPushStyle();
    ofSetColor(lineLuma); // softer off-white lines

    cam.begin();

    // Slow rotation for dynamics
    float t = ofGetElapsedTimef() - t0;
    ofRotateDeg(t * rotationSpeed, 0, 1, 0);
    ofRotateDeg(sin(t * 0.37f) * 35.0f, 1, 0, 0);

    // Draw the mesh as wireframe
    mesh.drawWireframe();

    cam.end();

    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f') {
        ofToggleFullscreen();
    }
    if (key == 'a') {
        animate = !animate;
    }
    if (key == 't') {
        trails = !trails;
    }
    if (key == 's') {
        ofSaveScreen("screenshot_" + ofGetTimestampString() + ".png");
    }
    if (key == '[') { // dim lines
        lineLuma = std::max(80, lineLuma - 10);
    }
    if (key == ']') { // brighten lines
        lineLuma = std::min(255, lineLuma + 10);
    }
    if (key == '-') { // longer trails (dimmer overall)
        trailFade = std::max(5, trailFade - 2);
    }
    if (key == '=') { // shorter trails (faster fade)
        trailFade = std::min(80, trailFade + 2);
    }
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
        buildMesh(thetaParams, phiParams);
    }
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
    int rows = nv + 1;

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
