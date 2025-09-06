#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;

		// Superformula parameters (Gielis)
		struct SuperParams {
			float m = 6.0f;
			float a = 1.0f;
			float b = 1.0f;
			float n1 = 0.3f;
			float n2 = 0.3f;
			float n3 = 0.3f;
		};

		float superformula(float theta, const SuperParams& p) const;
		void buildMesh(const SuperParams& pTheta, const SuperParams& pPhi);

		// Rendering and interaction
		ofEasyCam cam;
		ofMesh mesh; // wireframe surface
		int resU = 160;
		int resV = 80;
		float scale = 140.0f;
		bool animate = true;
		bool trails = true;
		float rotationSpeed = 8.0f; // deg/sec around Y
		int lineLuma = 230; // softer than pure white
		int trailFade = 28; // alpha of black fade quad
		
		// Enhanced animation
		bool cameraAnimation = true;
		float breathingIntensity = 0.2f;
		float morphSpeed = 0.8f;
		bool elegantRotation = true;
		
		// New animation modes
		int animationMode = 0; // 0=wave, 1=spiral, 2=organic, 3=musical
		float waveAmplitude = 2.0f;
		float spiralTightness = 1.5f;
		float organicGrowth = 1.0f;

		SuperParams thetaParams;
		SuperParams phiParams;
		float t0 = 0.0f;
		
		// Additional generative elements
		vector<glm::vec3> particles;
		vector<glm::vec3> particleVels;
		vector<float> particleLife;
		int maxParticles = 200;
		
		// Generative patterns
		void drawGenerativeLines();
		void drawNoiseField();
		void updateParticles();
		void drawParticles();
		
		// Enhanced 3D animation
		void drawElegantObject();
		SuperParams getEvolvedParams(float time, bool isTheta);
		SuperParams getWaveParams(float time, bool isTheta);
		SuperParams getSpiralParams(float time, bool isTheta);
		SuperParams getOrganicParams(float time, bool isTheta);
		SuperParams getMusicalParams(float time, bool isTheta);
		
		// Pattern variables
		float noiseScale = 0.005f;
		float lineSpacing = 20.0f;
		bool showNoiseField = true;
		bool showParticles = true;
};
