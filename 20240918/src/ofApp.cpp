#include "ofApp.h"

//--------------------------------------------------------------
// Particle Constructor
Particle::Particle(ofVec2f position, const std::vector<ofColor> &palette){
    pos = position;
    velocity = ofVec2f(0, 0);
    initialSize = ofRandom(2, 4); // Reduced initial size for clarity
    size = initialSize;

    // Assign color from palette
    int colorIndex = ofRandom(palette.size());
    color = palette[colorIndex];
    hueOffset = color.getHue(); // Initialize hueOffset based on assigned color

    lifespan = ofRandom(15, 25); // Lifespan between 15 to 25 seconds for longevity
    age = 0;
    opacity = 255;
    layer = ofRandom(1.0, 1.5); // Layer depth: affects speed and size changes
}

//--------------------------------------------------------------
// Update Particle Position, Size, Color, and Opacity
void Particle::update(float time, ofVec2f attractor){
    age += 1.0 / 60.0; // Assuming 60 FPS, increment age accordingly

    // Calculate direction towards attractor
    ofVec2f direction = attractor - pos;
    float distance = direction.length();
    direction.normalize();

    // Apply attraction force inversely proportional to distance
    float attractionStrength = 150.0 / (distance + 100.0); // Prevent division by zero
    velocity += direction * attractionStrength * 0.0008; // Slightly increased multiplier for dynamic movement

    // Use Perlin noise to determine additional movement
    float angle = ofMap(ofNoise(pos.x * 0.002, pos.y * 0.002, time * 0.02), 0, 1, 0, TWO_PI);
    velocity += ofVec2f(cos(angle), sin(angle)) * 0.015 * layer; // Adjusted for smoother motion
    velocity.limit(2.5 * layer); // Increased speed limit for visibility
    pos += velocity; // Update position

    // Wrap around the screen edges for seamless flow
    if(pos.x < 0) pos.x = ofGetWidth();
    if(pos.x > ofGetWidth()) pos.x = 0;
    if(pos.y < 0) pos.y = ofGetHeight();
    if(pos.y > ofGetHeight()) pos.y = 0;

    // Smoothly shift hue over time for dynamic color transitions
    hueOffset += 0.03 * layer; // Slower hue shift for harmonious transitions
    if(hueOffset > 255) hueOffset -= 255;
    color.setHue(ofWrap(hueOffset, 0, 255));

    // Adjust size and opacity based on age
    size = initialSize * ofMap(age, 0, lifespan, 1.0, 0.3, true); // Gradually decrease size more
    opacity = ofMap(age, 0, lifespan, 255, 80, true); // Adjusted opacity fade for better visibility
    color.a = opacity; // Update color opacity
}

//--------------------------------------------------------------
// Draw the Particle
void Particle::draw(){
    // Draw a soft glow by drawing multiple circles with decreasing opacity
    for(int i = 0; i < 4; i++){ // Increased layers for a more pronounced glow
        ofSetColor(color, opacity / (i + 1));
        ofDrawCircle(pos, size + i * 2.0); // Increased size increment for broader glow
    }

    // Optional: Draw different shapes based on layer (e.g., triangles for higher layers)
    /*
    if(layer > 1.3){
        ofPushMatrix();
        ofTranslate(pos);
        ofRotateDeg(ofGetElapsedTimef() * 10); // Rotate for dynamic shape orientation
        ofSetColor(color, opacity / 2);
        ofDrawTriangle(-size, size, size, size, 0, -size);
        ofPopMatrix();
    }
    */
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);       // Set frame rate to 60 FPS
    ofBackground(0);          // Set background to black
    maxParticles = 200;       // Adjusted for optimal performance and visibility
    resetProbability = 0.007; // Slightly increased probability for dynamic regeneration
    symmetryCount = 6;        // Number of symmetry axes (e.g., 6 for hexagonal symmetry)

    // Initialize color palette with harmonious colors
    colorPalette = {
        ofColor::fromHex(0x6A5ACD), // Slate Blue
        ofColor::fromHex(0x9370DB), // Medium Purple
        ofColor::fromHex(0xBA55D3), // Medium Orchid
        ofColor::fromHex(0xDDA0DD), // Plum
        ofColor::fromHex(0xEE82EE), // Violet
        ofColor::fromHex(0xFFD700)  // Gold
    };

    // Initialize attractor movement parameters
    attractorSpeed = 0.05;       // Slower speed for subtle movement
    attractorRadius = 150.0;     // Increased radius for broader influence
    attractorAngle = 0.0;        // Starting angle

    // Initialize attractor at the center
    attractor = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);

    // Initialize particles at random positions with symmetry
    for(int i = 0; i < maxParticles; i++){
        // Generate one particle
        ofVec2f randomPos(ofRandomWidth(), ofRandomHeight());
        particles.emplace_back(Particle(randomPos, colorPalette));

        // Create symmetric particles
        for(int j = 1; j < symmetryCount; j++){
            float angle = TWO_PI / symmetryCount * j;
            float cosA = cos(angle);
            float sinA = sin(angle);
            ofVec2f symPos = ofVec2f(
                (randomPos.x - attractor.x) * cosA - (randomPos.y - attractor.y) * sinA + attractor.x,
                (randomPos.x - attractor.x) * sinA + (randomPos.y - attractor.y) * cosA + attractor.y
            );
            particles.emplace_back(Particle(symPos, colorPalette));
        }
    }

    // Enable additive blending for glow effect and smooth drawing
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef(); // Get elapsed time

    // Update attractor position along a circular path
    attractorAngle += attractorSpeed * (1.0 / 60.0); // Increment angle based on speed and FPS
    attractor.x = ofGetWidth() / 2 + attractorRadius * cos(attractorAngle);
    attractor.y = ofGetHeight() / 2 + attractorRadius * sin(attractorAngle);

    // Update each particle
    for(auto &p : particles){
        p.update(time, attractor);
    }

    // Reset particles based on lifespan and reset probability
    for(auto &p : particles){
        if(p.getAge() >= p.getLifespan() || ofRandom(1.0) < resetProbability){
            // Reset particle to a new random position with symmetry
            ofVec2f newPos(ofRandomWidth(), ofRandomHeight());
            p = Particle(newPos, colorPalette);

            // Create symmetric particles
            for(int j = 1; j < symmetryCount; j++){
                float angle = TWO_PI / symmetryCount * j;
                float cosA = cos(angle);
                float sinA = sin(angle);
                ofVec2f symPos = ofVec2f(
                    (newPos.x - attractor.x) * cosA - (newPos.y - attractor.y) * sinA + attractor.x,
                    (newPos.x - attractor.x) * sinA + (newPos.y - attractor.y) * cosA + attractor.y
                );
                particles.emplace_back(Particle(symPos, colorPalette));
            }
        }
    }

    // Ensure the number of particles does not exceed the maximum
    while(particles.size() > maxParticles * symmetryCount){
        particles.erase(particles.begin());
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Dynamic background gradient shifting over time
    float time = ofGetElapsedTimef();
    for(int y = 0; y < ofGetHeight(); y++){
        float hue = ofMap(y + time * 5, 0, ofGetHeight(), 200, 220); // Soothing teal to blue hues
        ofSetColor(ofColor::fromHsb(ofWrap(hue, 0, 255), 60, 40, 10)); // Subtle hue shift with low opacity
        ofDrawLine(0, y, ofGetWidth(), y);
    }

    // Draw semi-transparent rectangle for trail effect
    ofSetColor(0, 0, 0, 25); // Adjusted alpha for balanced trail length
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    // Optional: Draw connections between nearby particles to emphasize fractal patterns
    /*
    ofSetColor(255, 50); // Semi-transparent white lines
    int connectionLimit = 5000; // Limit total connections to maintain performance
    int connections = 0;
    for(auto it1 = particles.begin(); it1 != particles.end(); ++it1){
        for(auto it2 = it1 + 1; it2 != particles.end(); ++it2){
            if(it1->pos.distance(it2->pos) < 100 && connections < connectionLimit){
                ofDrawLine(it1->pos, it2->pos);
                connections++;
            }
        }
        if(connections >= connectionLimit){
            break;
        }
    }
    */

    // Draw all particles
    for(auto &p : particles){
        p.draw();
    }

    // Optional: Display particle count and frame rate
    ofSetColor(255);
    std::string info = "Particle Count: " + ofToString(particles.size()) +
                       "\nFPS: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(info, 10, 20);

    // Note: The attractor point is no longer drawn to maintain aesthetic purity
}
