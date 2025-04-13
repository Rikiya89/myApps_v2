#include "ofApp.h"

// Helper function: draw the background for a given scene with a specified alpha
void drawBackground(SceneType scene, float alpha = 255){
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    if(scene == SCENE_DAY){
        mesh.addVertex(glm::vec3(0, 0, 0));
        mesh.addColor(ofColor(135,206,250, alpha));  // sky blue
        mesh.addVertex(glm::vec3(ofGetWidth(), 0, 0));
        mesh.addColor(ofColor(255,255,255, alpha));    // white
        mesh.addVertex(glm::vec3(ofGetWidth(), ofGetHeight(), 0));
        mesh.addColor(ofColor(255,255,255, alpha));
        mesh.addVertex(glm::vec3(0, ofGetHeight(), 0));
        mesh.addColor(ofColor(135,206,250, alpha));
    }
    else if(scene == SCENE_NIGHT){
        mesh.addVertex(glm::vec3(0, 0, 0));
        mesh.addColor(ofColor(10,10,50, alpha));
        mesh.addVertex(glm::vec3(ofGetWidth(), 0, 0));
        mesh.addColor(ofColor(0,0,0, alpha));
        mesh.addVertex(glm::vec3(ofGetWidth(), ofGetHeight(), 0));
        mesh.addColor(ofColor(0,0,0, alpha));
        mesh.addVertex(glm::vec3(0, ofGetHeight(), 0));
        mesh.addColor(ofColor(10,10,50, alpha));
    }
    else if(scene == SCENE_SPRING){
        mesh.addVertex(glm::vec3(0, 0, 0));
        mesh.addColor(ofColor(255,230,250, alpha));  // light pink
        mesh.addVertex(glm::vec3(ofGetWidth(), 0, 0));
        mesh.addColor(ofColor(230,255,250, alpha));  // mint green
        mesh.addVertex(glm::vec3(ofGetWidth(), ofGetHeight(), 0));
        mesh.addColor(ofColor(230,255,250, alpha));
        mesh.addVertex(glm::vec3(0, ofGetHeight(), 0));
        mesh.addColor(ofColor(255,230,250, alpha));
    }
    else if(scene == SCENE_WINTER){
        mesh.addVertex(glm::vec3(0, 0, 0));
        mesh.addColor(ofColor(200,225,255, alpha));  // soft blue
        mesh.addVertex(glm::vec3(ofGetWidth(), 0, 0));
        mesh.addColor(ofColor(255,255,255, alpha));    // white
        mesh.addVertex(glm::vec3(ofGetWidth(), ofGetHeight(), 0));
        mesh.addColor(ofColor(255,255,255, alpha));
        mesh.addVertex(glm::vec3(0, ofGetHeight(), 0));
        mesh.addColor(ofColor(200,225,255, alpha));
    }
    mesh.draw();
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    
    video.setDeviceID(0);
    video.setup(640,480);
    
    colorImg.allocate(640,480);
    grayImg.allocate(640,480);
    grayPrev.allocate(640,480);
    diffImg.allocate(640,480);
    
    thresholdVal = 40;
    font.load("verdana.ttf", 20);
    bFirstFrame = true;
    
    // Start in Spring Mode
    currentScene = SCENE_SPRING;
    previousScene = currentScene;
    transitioning = false;
    transitionProgress = 0.0;
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    
    if(video.isFrameNew()){
        colorImg.setFromPixels(video.getPixels());
        grayImg = colorImg;
        
        if(bFirstFrame){
            grayPrev = grayImg;
            bFirstFrame = false;
        }
        
        diffImg.absDiff(grayImg, grayPrev);
        diffImg.threshold(thresholdVal);
        grayPrev = grayImg;
        contourFinder.findContours(diffImg, 20, (640*480)/3, 10, false);
        
        int offsetX = (ofGetWidth()-640) / 2;
        int offsetY = (ofGetHeight()-480) / 2;
        
        for (int i = 0; i < contourFinder.nBlobs; i++){
            if(!contourFinder.blobs[i].pts.empty()){
                for (int j = 0; j < 3; j++){
                    int index = ofRandom(0, contourFinder.blobs[i].pts.size());
                    glm::vec2 pos = contourFinder.blobs[i].pts[index];
                    pos.x += offsetX;
                    pos.y += offsetY;
                    ofColor col;
                    col.setHsb((ofGetFrameNum()*2 + i*30) % 255, 200, 255);
                    Particle p(pos, col);
                    particles.push_back(p);
                }
                if(ofRandom(1.0) < 0.15){
                    glm::vec2 centroid = contourFinder.blobs[i].centroid;
                    centroid.x += offsetX;
                    centroid.y += offsetY;
                    sparkles.push_back(Sparkle(centroid));
                }
            }
        }
    }
    
    // Update particles
    for (int i = particles.size()-1; i >= 0; i--){
        particles[i].update();
        if(particles[i].isDead()){
            particles.erase(particles.begin() + i);
        }
    }
    const int MAX_PARTICLES = 500;
    if(particles.size() > MAX_PARTICLES){
        particles.erase(particles.begin(), particles.begin() + (particles.size() - MAX_PARTICLES));
    }
    
    // Update sparkles
    for (int i = sparkles.size()-1; i >= 0; i--){
        sparkles[i].update();
        if(sparkles[i].isDead()){
            sparkles.erase(sparkles.begin() + i);
        }
    }
    
    // Handle scene transition (if active, progress transition)
    if(transitioning){
        transitionProgress += 0.02; // adjust speed as desired
        if(transitionProgress >= 1.0){
            transitioning = false;
            transitionProgress = 1.0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Draw background:
    // If transitioning, draw previous scene fully then overlay new scene with alpha
    if(transitioning){
        drawBackground(previousScene, 255);
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        drawBackground(currentScene, transitionProgress * 255);
        ofDisableBlendMode();
    }
    else{
        drawBackground(currentScene, 255);
    }
    
    // Optionally draw motion contours
    int offsetX = (ofGetWidth()-640) / 2;
    int offsetY = (ofGetHeight()-480) / 2;
    ofSetLineWidth(2);
    for (int i = 0; i < contourFinder.nBlobs; i++){
        ofColor dynamicColor;
        dynamicColor.setHsb((ofGetFrameNum()*2 + i*30) % 255, 200, 255);
        ofSetColor(dynamicColor);
        ofPolyline polyline;
        for(auto &pt : contourFinder.blobs[i].pts){
            polyline.addVertex(pt.x + offsetX, pt.y + offsetY);
        }
        polyline.close();
        polyline.draw();
    }
    
    // Draw particles with additive blending
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for(auto &p : particles){
        p.draw();
    }
    ofDisableBlendMode();
    
    // Draw sparkles with additive blending
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for(auto &s : sparkles){
        s.draw();
    }
    ofDisableBlendMode();
    
    // Draw scene indicator and instructions
    ofSetColor(255);
    string sceneText;
    switch(currentScene){
        case SCENE_DAY: sceneText = "Day Mode"; break;
        case SCENE_NIGHT: sceneText = "Night Mode"; break;
        case SCENE_SPRING: sceneText = "Spring Mode"; break;
        case SCENE_WINTER: sceneText = "Winter Mode"; break;
    }
    font.drawString(sceneText, 20, 40);
    
    string info = "Press UP/DOWN to adjust threshold: " + ofToString(thresholdVal) + "\n";
    info += "Particles: " + ofToString(particles.size()) + "\n";
    info += "Sparkles: " + ofToString(sparkles.size()) + "\n";
    info += "Press SPACE to change scene";
    font.drawString(info, 20, ofGetHeight()-40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_UP){
        thresholdVal += 5;
        if(thresholdVal > 255) thresholdVal = 255;
    }
    else if(key == OF_KEY_DOWN){
        thresholdVal -= 5;
        if(thresholdVal < 0) thresholdVal = 0;
    }
    else if(key == ' '){
        // Begin smooth transition: store current scene as previous and choose next scene
        previousScene = currentScene;
        if(currentScene == SCENE_WINTER)
            currentScene = SCENE_DAY;
        else
            currentScene = static_cast<SceneType>(currentScene + 1);
        transitioning = true;
        transitionProgress = 0.0;
    }
}
