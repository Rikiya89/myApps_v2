#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(30);

    box2d.init();
    box2d.setGravity(0, 10);
    box2d.createGround();
    box2d.setFPS(60.0);
}

void ofApp::update() {
    box2d.update();
    
    // Randomly add shapes
    if((int)ofRandom(0, 60) == 0) {
        addRandomShape();
    }

    // Add particles around shapes
    for(auto &circle : circles) {
        addParticlesAroundShape(circle);
    }
    for(auto &poly : polygons) {
        addParticlesAroundShape(poly);
    }

    // Update particles
    for(int i = particles.size()-1; i >= 0; i--) {
        particles[i].update();
        if(particles[i].isDead()) {
            particles.erase(particles.begin() + i);
        }
    }
}

void ofApp::draw() {
    drawGradientBackground();

    for(auto &circle : circles) {
        ofFill();
        ofSetColor(127, 127, 220); // You can adjust color based on speed or other properties
        circle->draw();
    }

    for(auto &poly : polygons) {
        ofFill();
        ofSetColor(220, 127, 127); // Adjust color as needed
        poly->draw();
    }

    // Draw particles
    for(auto &particle : particles) {
        particle.draw();
    }
}

void ofApp::mouseDragged(int x, int y, int button) {
    // Generate a burst of particles on mouse drag
    for(int i = 0; i < 10; i++) {
        ofVec2f vel(ofRandom(-3, 3), ofRandom(-3, 3));
        ofColor col(255, ofRandom(100, 255), ofRandom(100, 255), 200);
        particles.push_back(Particle(ofPoint(x, y), vel, col, ofRandom(2, 5)));
    }
}

void ofApp::addRandomShape() {
    int shapeType = ofRandom(0, 2); // 0 for circles, 1 for polygons
    
    if(shapeType == 0) {
        auto circle = make_shared<ofxBox2dCircle>();
        circle->setPhysics(1.0, 0.5, 0.3);
        circle->setup(box2d.getWorld(), ofRandom(ofGetWidth()), ofRandom(20, 100), ofRandom(10, 30));
        circles.push_back(circle);
    } else {
        auto poly = make_shared<ofxBox2dPolygon>();
        poly->setPhysics(1.0, 0.5, 0.3);

        // Manually create a polygon with random vertices
        int numVertices = 3 + int(ofRandom(3, 6)); // Polygons with 3 to 8 vertices
        float radius = ofRandom(20, 50); // Random radius for the vertices
        for (int i = 0; i < numVertices; i++) {
            float angle = 360.0 / numVertices * i;
            float x = cos(ofDegToRad(angle)) * radius;
            float y = sin(ofDegToRad(angle)) * radius;
            poly->addVertex(x + ofGetWidth()/2, y + ofGetHeight()/2); // Adjust position as needed
        }
        poly->create(box2d.getWorld()); // Finalize the polygon
        polygons.push_back(poly);
    }
}


void ofApp::drawGradientBackground() {
    // Gradient background implementation
    ofColor topColor(255, 122, 203);
    ofColor bottomColor(5, 12, 40);

    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mesh.addColor(topColor);
    mesh.addVertex(ofPoint(0, 0));
    mesh.addColor(topColor);
    mesh.addVertex(ofPoint(ofGetWidth(), 0));
    mesh.addColor(bottomColor);
    mesh.addVertex(ofPoint(0, ofGetHeight()));
    mesh.addColor(bottomColor);
    mesh.addVertex(ofPoint(ofGetWidth(), ofGetHeight()));

    mesh.draw();
}

void ofApp::addParticlesAroundShape(shared_ptr<ofxBox2dBaseShape> shape) {
    // This function intentionally left blank for simplicity
    // You can implement logic similar to mouseDragged for shape interaction
}
