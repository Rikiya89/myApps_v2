#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);

    private:
        ofMesh mesh;          // The mesh will now represent a point cloud
        ofImage texture;      // The texture image (chry.jpg)
        float displacementAmount;  // Amount to displace vertices
};
