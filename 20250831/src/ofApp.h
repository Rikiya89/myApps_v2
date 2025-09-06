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

		// Modes
		enum class Mode { SUPERFORMULA = 1, LORENZ = 2, AIZAWA = 3 };
		Mode mode = Mode::SUPERFORMULA;

		// Superformula parameters
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
		void rebuildCurrent();

		// Drawing + interaction
		ofEasyCam cam;
		ofMesh mesh; // triangle mesh, rendered as wireframe
		ofVboMesh lineMesh; // for attractors
		int resU = 160; // longitude resolution
		int resV = 80;  // latitude resolution
		float scale = 140.0f;
		float lineScale = 8.0f; // attractor scaling
		int lineLuma = 230; // 0-255, softer than pure white
		int trailFade = 28; // alpha of black fade quad (higher = faster fade)
		bool animate = true;
		bool trails = true;
		float rotationSpeed = 8.0f; // degrees per second around Y

		SuperParams thetaParams; // for longitude angle
		SuperParams phiParams;   // for latitude angle
		float t0 = 0.0f;         // time offset

		// Lorenz parameters
		float lorenzSigma = 10.0f;
		float lorenzRho = 28.0f;
		float lorenzBeta = 8.0f / 3.0f;
		int lorenzSteps = 22000;
		float lorenzDt = 0.005f;
		glm::vec3 lorenzStart = {0.01f, 0.0f, 0.0f};

		// Aizawa parameters
		float aizawaA = 0.95f;
		float aizawaB = 0.7f;
		float aizawaC = 0.6f;
		float aizawaD = 3.5f;
		float aizawaE = 0.25f;
		float aizawaF = 0.1f;
		int aizawaSteps = 30000;
		float aizawaDt = 0.005f;
		glm::vec3 aizawaStart = {0.1f, 0.0f, 0.0f};

		void buildLorenz();
		void buildAizawa();
};
