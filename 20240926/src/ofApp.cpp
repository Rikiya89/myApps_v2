#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0); // Black background for contrast
    numPoints = 150; // More points for complexity
    symmetry = 8; // Slightly fewer divisions for a balanced radial pattern
    baseColor = ofColor(255, 100, 200); // Start with a base color
    hueOffset = 0; // Initialize the hue offset
    isMousePressed = false; // Mouse interaction toggle
    generateFractalPattern();

    // Setting up the FBO for motion blur (rendering trails)
    trailFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB);
    trailFbo.begin();
    ofClear(0, 0, 0, 255); // Clear the FBO with transparency
    trailFbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    // Update the hueOffset for smooth color cycling
    hueOffset += 0.15; // Slightly faster hue cycling for more dynamic changes
    if (hueOffset > 255) hueOffset = 0;

    // Enhance the baseColor by increasing brightness and saturation dynamically
    if (isMousePressed) {
        baseColor.setHueAngle(ofMap(sin(ofGetElapsedTimef() * 1.5), -1, 1, 0 + hueOffset, 360 + hueOffset));
        baseColor.setSaturation(255); // Max saturation for extremely vibrant colors
        baseColor.setBrightness(255); // Max brightness for strong glow effect
    } else {
        baseColor.setHueAngle(ofMap(sin(ofGetElapsedTimef() * 0.8), -1, 1, 0 + hueOffset, 360 + hueOffset));
        baseColor.setSaturation(230); // High saturation for rich color tones
        baseColor.setBrightness(230); // High brightness for more intense color visibility
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Begin drawing to the FBO for motion blur effect
    trailFbo.begin();

    // Create a fading trail by drawing a semi-transparent rectangle over the entire FBO
    ofSetColor(0, 0, 0, 30); // Slightly higher alpha to make the fading slower
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    // Translate to the center of the screen for radial symmetry
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

    for (int i = 0; i < points.size(); i++) {
        float angleStep = TWO_PI / symmetry;
        float size = sizes[i] + sin(ofGetElapsedTimef() * 0.5 + i) * 35; // Larger pulsating size for a more dramatic look

        for (int j = 0; j < symmetry; j++) {
            float angle = j * angleStep;

            // Rotate for radial symmetry
            ofPushMatrix();
            ofRotateRad(angle);

            // Apply more vivid colors by setting higher brightness and saturation
            ofColor dynamicColor = baseColor;
            dynamicColor.setHueAngle(ofMap(i, 0, numPoints, hueOffset, 360 + hueOffset));
            dynamicColor.setBrightness(255); // Max brightness for glowing effect
            drawGlow(points[i].x, points[i].y, size, dynamicColor);

            // Increase saturation and brightness for the stars
            ofColor starColor = ofColor::fromHsb(hueOffset + 100, 255, 255); // Strong color for the stars
            drawRotatingStar(points[i].x, points[i].y, size * 0.5, starColor);

            // Draw brighter particle trails at each point
            drawParticles(points[i], size * 0.25);

            ofPopMatrix();
        }
    }

    trailFbo.end();

    // Draw the FBO (with the trails) back to the screen
    ofSetColor(255); // Ensure FBO is drawn with full opacity
    trailFbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::generateFractalPattern() {
    points.clear();
    sizes.clear();

    for (int i = 0; i < numPoints; i++) {
        // Fractal-like distribution of points in polar coordinates
        float angle = i * (TWO_PI / numPoints);
        float radius = ofMap(i, 0, numPoints, 50, ofGetWidth() * 0.35); // More evenly distributed radius
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        points.push_back(ofPoint(x, y));
        sizes.push_back(ofRandom(25, 70)); // Increased initial size for bigger glow
    }
}

//--------------------------------------------------------------
void ofApp::drawGlow(float x, float y, float size, ofColor color) {
    // Draw more intense glow layers with higher brightness
    for (int i = 0; i < 6; i++) {
        ofSetColor(color, 150 - (i * 20)); // Reduce alpha more gradually for stronger glow layers
        ofDrawCircle(x, y, size + i * 16); // Increase the glow size slightly for a more pronounced glow effect
    }
}

//--------------------------------------------------------------
void ofApp::drawParticles(ofPoint p, float size) {
    // Draw particles with higher opacity and brightness for more pronounced effect
    ofSetColor(255, 255, 255, 150); // Bright white particles with higher opacity
    for (int i = 0; i < 8; i++) {
        float offsetX = ofRandom(-size, size);
        float offsetY = ofRandom(-size, size);
        ofDrawCircle(p.x + offsetX, p.y + offsetY, size * 0.1); // Slightly larger particle trails
    }
}

//--------------------------------------------------------------
void ofApp::drawRotatingStar(float x, float y, float size, ofColor color) {
    // Draw a star that rotates over time
    ofSetColor(color, 200); // Semi-transparent star
    ofPushMatrix();
    ofTranslate(x, y);
    ofRotateDeg(ofGetElapsedTimef() * 50); // Rotate the star dynamically

    ofBeginShape();
    for (int i = 0; i < 5; i++) {
        float angle = ofDegToRad(i * 72);
        float innerAngle = ofDegToRad((i + 0.5) * 72);
        float xOuter = size * cos(angle);
        float yOuter = size * sin(angle);
        float xInner = (size * 0.5) * cos(innerAngle);
        float yInner = (size * 0.5) * sin(innerAngle);

        ofVertex(xOuter, yOuter);
        ofVertex(xInner, yInner);
    }
    ofEndShape(true);

    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    isMousePressed = true; // Toggle the interaction effect when the mouse is pressed
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    isMousePressed = false; // Toggle back when the mouse is released
}
