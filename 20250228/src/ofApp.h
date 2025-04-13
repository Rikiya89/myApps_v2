#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "Particle.h"
#include "Sparkle.h"

// Define available scene types
enum SceneType {
    SCENE_DAY,
    SCENE_NIGHT,
    SCENE_SPRING,
    SCENE_WINTER
};

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    // Webcam input
    ofVideoGrabber video;
    
    // OpenCV images for processing
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage grayImg;
    ofxCvGrayscaleImage grayPrev;
    ofxCvGrayscaleImage diffImg;
    ofxCvContourFinder contourFinder;
    
    // Motion detection threshold
    int thresholdVal;
    
    // Font for instructions
    ofTrueTypeFont font;
    
    // Containers for particles and sparkles
    vector<Particle> particles;
    vector<Sparkle> sparkles;
    
    // Flag for first frame capture
    bool bFirstFrame;
    
    // Scene transition variables
    SceneType currentScene;
    SceneType previousScene;
    bool transitioning;
    float transitionProgress;  // 0.0 to 1.0
};
