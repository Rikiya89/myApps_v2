#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    // Camera for scene navigation.
    ofEasyCam cam;

    // Dynamic light.
    ofLight light;

    // Custom shader for coloring and glow.
    ofShader shader;

    // Mesh for our deformable sphere.
    ofMesh sphereMesh;

    // Copy of the original sphere vertices (using glm::vec3).
    vector<glm::vec3> baseVertices;

    // Sphere detail resolution.
    int sphereResolution = 100;

    // Time offset for noise variation.
    float noiseTimeOffset;

    // Global rotation angle.
    float rotationAngle;

    // Global scaling factor.
    float globalScale;

    // A function to calculate fractal Brownian motion.
    float fBm(const glm::vec3 &pos, float time, int octaves, float lacunarity, float gain);
};
