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

	private:
		// Modes
		enum class Mode { Flow, Sunflower };
		Mode mode = Mode::Sunflower; // start with the sunflower

		// Flow-field particles
		std::vector<glm::vec2> positions;
		std::vector<glm::vec2> prevPositions;
		int numParticles = 3000;
		float noiseScale = 0.002f;   // spatial scale for noise
		float timeScale  = 0.10f;    // temporal evolution of the field
		float speed      = 2.0f;     // particle step size

		// Visual settings
		bool invertColors = false;   // false: black bg + white strokes, true: white bg + black strokes
		bool fadeTrails   = true;    // overlay translucent bg each frame for trails
		int  fadeAlpha    = 10;      // 0-255, higher = stronger fade

		// Helpers
		void resetParticles();
		void clearCanvas();

		// Sunflower (phyllotaxis)
		void drawSunflower();
		int sunflowerSeeds = 1200;
		int sunflowerShown = 0;   // for growth animation
		float sunflowerSeedRadius = 2.0f;
		bool sunflowerAnimate = true;
};
