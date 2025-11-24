#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofEnableSmoothing();
    ofSetCircleResolution(64);
    ofEnableLighting();

    // Initialize color palette
    colors.push_back(ofColor::fromHex(0x362d78));
    colors.push_back(ofColor::fromHex(0x523fa3));
    colors.push_back(ofColor::fromHex(0x916ccc));
    colors.push_back(ofColor::fromHex(0xbda1e5));
    colors.push_back(ofColor::fromHex(0xc8c0e9));
    colors.push_back(ofColor::fromHex(0x84bae7));
    colors.push_back(ofColor::fromHex(0x516ad4));
    colors.push_back(ofColor::fromHex(0x333f87));
    colors.push_back(ofColor::fromHex(0x293039));
    colors.push_back(ofColor::fromHex(0x283631));

    // Setup lighting
    pointLight.setPointLight();
    pointLight.setPosition(0, 0, 200);
    pointLight.setDiffuseColor(colors[5]);
    pointLight.setSpecularColor(colors[3]);

    material.setShininess(64);
    material.setSpecularColor(colors[3]);

    // Setup camera
    cam.setDistance(600);
    cam.setNearClip(0.1);
    cam.setFarClip(10000);

    // Initialize parameters
    numParticles = 1200;
    numLayers = 7;
    numRibbons = 8;
    numOrbs = 15;
    noiseScale = 0.004;
    flowSpeed = 0.25;
    time = 0;
    rotationAngle = 0;
    cameraRotation = 0;
    maxTrailLength = 40;

    // Create particles
    for(int i = 0; i < numParticles; i++){
        float angle = ofRandom(TWO_PI);
        float radius = ofRandom(50, 350);
        float height = ofRandom(-500, 500);

        ofVec3f pos(
            cos(angle) * radius + ofRandom(-20, 20),
            height,
            sin(angle) * radius + ofRandom(-20, 20)
        );

        particles.push_back(pos);
        velocities.push_back(ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)));
        particleColors.push_back(colors[i % colors.size()]);
        particleSizes.push_back(ofRandom(1.5, 6));
        particlePhases.push_back(ofRandom(TWO_PI));

        // Initialize trail
        deque<ofVec3f> trail;
        trail.push_back(pos);
        particleTrails.push_back(trail);
    }

    // Create ribbon meshes
    for(int r = 0; r < numRibbons; r++){
        ofMesh ribbon;
        ribbon.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

        int segments = 100;
        float radius = 200 + r * 20;
        float heightOffset = r * 50 - 200;

        for(int i = 0; i <= segments; i++){
            float t = i / (float)segments;
            float angle = t * TWO_PI * 3;

            float x = cos(angle) * radius;
            float y = sin(t * TWO_PI * 2) * 100 + heightOffset;
            float z = sin(angle) * radius;

            ribbon.addVertex(ofVec3f(x, y, z));
            ribbon.addVertex(ofVec3f(x * 0.95, y + 10, z * 0.95));

            ofColor col = colors[r % colors.size()];
            col.a = 120;
            ribbon.addColor(col);
            col.a = 60;
            ribbon.addColor(col);
        }

        ribbonMeshes.push_back(ribbon);
    }

    // Create orbital rings
    for(int o = 0; o < 5; o++){
        ofMesh ring;
        ring.setMode(OF_PRIMITIVE_LINE_STRIP);

        int segments = 100;
        float radius = 300 + o * 40;

        for(int i = 0; i <= segments; i++){
            float angle = (i / (float)segments) * TWO_PI;
            float x = cos(angle) * radius;
            float y = sin(angle * 3 + o) * 50;
            float z = sin(angle) * radius;

            ring.addVertex(ofVec3f(x, y, z));
            ofColor col = colors[(o * 2) % colors.size()];
            col.a = 100;
            ring.addColor(col);
        }

        orbitalRings.push_back(ring);
    }

    // Create floating orbs
    for(int i = 0; i < numOrbs; i++){
        float angle = (i / (float)numOrbs) * TWO_PI;
        float radius = 250 + ofRandom(-50, 50);
        float height = ofRandom(-300, 300);

        floatingOrbs.push_back(ofVec3f(
            cos(angle) * radius,
            height,
            sin(angle) * radius
        ));

        orbColors.push_back(colors[i % colors.size()]);
        orbPhases.push_back(ofRandom(TWO_PI));
    }
}

void ofApp::update(){
    time += flowSpeed;
    rotationAngle += 0.15;
    cameraRotation += 0.08;

    // Update light position
    pointLight.setPosition(
        cos(time * 0.1) * 300,
        sin(time * 0.15) * 200,
        sin(time * 0.1) * 300 + 200
    );

    // Update particles with flowing motion
    for(int i = 0; i < particles.size(); i++){
        float noiseX = ofNoise(particles[i].x * noiseScale, particles[i].y * noiseScale, time * 0.08 + particlePhases[i]);
        float noiseY = ofNoise(particles[i].y * noiseScale, particles[i].z * noiseScale, time * 0.08 + particlePhases[i] + 100);
        float noiseZ = ofNoise(particles[i].z * noiseScale, particles[i].x * noiseScale, time * 0.08 + particlePhases[i] + 200);

        // Add spiral motion
        float spiralAngle = atan2(particles[i].z, particles[i].x);

        velocities[i].x += (noiseX - 0.5) * 0.6 + cos(spiralAngle + time * 0.02) * 0.3;
        velocities[i].y += (noiseY - 0.5) * 0.6 + sin(time * 0.03) * 0.2;
        velocities[i].z += (noiseZ - 0.5) * 0.6 + sin(spiralAngle + time * 0.02) * 0.3;

        velocities[i] *= 0.93;
        particles[i] += velocities[i];

        // Boundary check
        float dist = particles[i].length();
        if(dist > 450){
            particles[i] = particles[i].getNormalized() * 450;
            velocities[i] *= -0.5;
        }

        // Update trail
        particleTrails[i].push_front(particles[i]);
        if(particleTrails[i].size() > maxTrailLength){
            particleTrails[i].pop_back();
        }
    }

    // Update ribbons
    for(int r = 0; r < ribbonMeshes.size(); r++){
        ofMesh& ribbon = ribbonMeshes[r];

        int segments = 100;
        float radius = 200 + r * 20;
        float heightOffset = r * 50 - 200;

        for(int i = 0; i <= segments; i++){
            float t = i / (float)segments;
            float angle = t * TWO_PI * 3 + time * 0.1 * (r % 2 == 0 ? 1 : -1);

            float noise = ofNoise(t * 5 + time * 0.05 + r, r * 0.5);
            float dynamicRadius = radius + noise * 40;

            float x = cos(angle) * dynamicRadius;
            float y = sin(t * TWO_PI * 2 + time * 0.15) * 100 + heightOffset;
            float z = sin(angle) * dynamicRadius;

            ribbon.setVertex(i * 2, ofVec3f(x, y, z));
            ribbon.setVertex(i * 2 + 1, ofVec3f(x * 0.95, y + 10, z * 0.95));
        }
    }

    // Update orbital rings
    for(int o = 0; o < orbitalRings.size(); o++){
        ofMesh& ring = orbitalRings[o];

        int segments = 100;
        float radius = 300 + o * 40;

        for(int i = 0; i <= segments; i++){
            float angle = (i / (float)segments) * TWO_PI + time * 0.05 * (o % 2 == 0 ? 1 : -1);
            float x = cos(angle) * radius;
            float y = sin(angle * 3 + o + time * 0.1) * 50;
            float z = sin(angle) * radius;

            ring.setVertex(i, ofVec3f(x, y, z));
        }
    }

    // Update floating orbs
    for(int i = 0; i < floatingOrbs.size(); i++){
        float angle = (i / (float)numOrbs) * TWO_PI + time * 0.05;
        float radius = 250 + sin(time * 0.1 + orbPhases[i]) * 50;
        float height = sin(time * 0.08 + orbPhases[i] + i) * 300;

        floatingOrbs[i] = ofVec3f(
            cos(angle) * radius,
            height,
            sin(angle) * radius
        );
    }
}

void ofApp::draw(){
    ofBackgroundGradient(colors[8], colors[9]);

    cam.begin();

    ofPushMatrix();
    ofRotateDeg(cameraRotation * 0.2, 0, 1, 0);

    pointLight.enable();
    material.begin();

    // Draw orbital rings
    ofDisableLighting();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetLineWidth(2);
    for(int o = 0; o < orbitalRings.size(); o++){
        ofPushMatrix();
        ofRotateDeg(time * (1 + o * 0.3), o % 2, 1, o % 3);
        orbitalRings[o].draw();
        ofPopMatrix();
    }

    // Draw ribbons
    ofDisableLighting();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for(int r = 0; r < ribbonMeshes.size(); r++){
        ofPushMatrix();
        ofRotateDeg(time * (0.8 + r * 0.2), 0, 1, 0);
        ofRotateDeg(r * 15, 1, 0, 0);
        ribbonMeshes[r].draw();
        ofPopMatrix();
    }

    // Draw floating orbs with halos
    ofEnableLighting();
    for(int i = 0; i < floatingOrbs.size(); i++){
        ofPushMatrix();
        ofTranslate(floatingOrbs[i]);

        float pulse = sin(time * 0.15 + orbPhases[i]) * 0.5 + 0.5;
        float size = 15 + pulse * 10;

        material.setDiffuseColor(orbColors[i]);
        material.setEmissiveColor(orbColors[i] * 0.4);

        ofDrawSphere(size);

        ofPopMatrix();
    }

    // Draw particle trails
    ofDisableLighting();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for(int i = 0; i < particleTrails.size(); i++){
        if(particleTrails[i].size() > 1){
            ofMesh trailMesh;
            trailMesh.setMode(OF_PRIMITIVE_LINE_STRIP);

            for(int j = 0; j < particleTrails[i].size(); j++){
                trailMesh.addVertex(particleTrails[i][j]);

                float alpha = ofMap(j, 0, particleTrails[i].size(), 180, 0);
                ofColor col = particleColors[i];
                col.a = alpha;
                trailMesh.addColor(col);
            }

            trailMesh.draw();
        }
    }

    // Draw particles
    for(int i = 0; i < particles.size(); i++){
        float pulse = sin(time * 0.12 + particlePhases[i]) * 0.5 + 0.5;
        float size = particleSizes[i] * (0.7 + pulse * 0.6);

        // Draw particle
        ofSetColor(particleColors[i], 200);
        ofDrawSphere(particles[i], size);

        // Draw connections to nearby particles
        if(i % 3 == 0){
            for(int j = i + 1; j < min(i + 8, (int)particles.size()); j++){
                float dist = particles[i].distance(particles[j]);
                if(dist < 70){
                    float alpha = ofMap(dist, 0, 70, 120, 0);
                    ofSetColor(particleColors[i], alpha);
                    ofSetLineWidth(1 + (1.0 - dist / 70.0) * 2);
                    ofDrawLine(particles[i], particles[j]);
                }
            }
        }
    }

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    material.end();
    pointLight.disable();

    ofPopMatrix();

    cam.end();

    // Draw info
    ofDisableLighting();
    ofSetColor(colors[3]);
//    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 1), 20, 20);
//    ofDrawBitmapString("Press SPACE to regenerate", 20, 40);
}

void ofApp::keyPressed(int key){
    if(key == ' '){
        // Regenerate everything
        particles.clear();
        velocities.clear();
        particleColors.clear();
        particleSizes.clear();
        particlePhases.clear();
        particleTrails.clear();

        for(int i = 0; i < numParticles; i++){
            float angle = ofRandom(TWO_PI);
            float radius = ofRandom(50, 350);
            float height = ofRandom(-500, 500);

            ofVec3f pos(
                cos(angle) * radius + ofRandom(-20, 20),
                height,
                sin(angle) * radius + ofRandom(-20, 20)
            );

            particles.push_back(pos);
            velocities.push_back(ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)));
            particleColors.push_back(colors[i % colors.size()]);
            particleSizes.push_back(ofRandom(1.5, 6));
            particlePhases.push_back(ofRandom(TWO_PI));

            deque<ofVec3f> trail;
            trail.push_back(pos);
            particleTrails.push_back(trail);
        }
    }
}

void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}
