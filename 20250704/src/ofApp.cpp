#include "ofApp.h"

void ofApp::setup() {
    width = 200;
    height = 200;
    img.allocate(width, height, OF_IMAGE_GRAYSCALE);

    a.resize(width, std::vector<float>(height, 1.0f));
    b.resize(width, std::vector<float>(height, 0.0f));
    nextA = a;
    nextB = b;

    seed();

    // GUI
    gui.setup("Reaction-Diffusion Controls");
    gui.setPosition(10, 10);
    gui.add(feedParam.set("Feed", 0.055, 0.0, 0.1));
    gui.add(killParam.set("Kill", 0.062, 0.0, 0.1));
    gui.add(stepsPerFrameParam.set("Speed", 10, 1, 100));
    gui.add(resetButton.setup("Reset"));
    resetButton.addListener(this, &ofApp::resetSimulation);
}

void ofApp::seed() {
    for (int y = height / 2 - 10; y < height / 2 + 10; ++y) {
        for (int x = width / 2 - 10; x < width / 2 + 10; ++x) {
            b[x][y] = 1.0f;
        }
    }
}

void ofApp::resetSimulation() {
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x) {
            a[x][y] = 1.0f;
            b[x][y] = 0.0f;
            nextA[x][y] = 1.0f;
            nextB[x][y] = 0.0f;
        }
    seed();
}

void ofApp::update() {
    feed = feedParam;
    kill = killParam;
    int stepsPerFrame = stepsPerFrameParam;

    for (int s = 0; s < stepsPerFrame; ++s) {
        for (int y = 1; y < height - 1; ++y) {
            for (int x = 1; x < width - 1; ++x) {
                float aVal = a[x][y];
                float bVal = b[x][y];
                float lapA = laplace(a, x, y);
                float lapB = laplace(b, x, y);

                float newA = aVal + (dA * lapA - aVal * bVal * bVal + feed * (1 - aVal));
                float newB = bVal + (dB * lapB + aVal * bVal * bVal - (kill + feed) * bVal);

                nextA[x][y] = ofClamp(newA, 0.0f, 1.0f);
                nextB[x][y] = ofClamp(newB, 0.0f, 1.0f);
            }
        }
        a = nextA;
        b = nextB;
    }

    ofPixels& pixels = img.getPixels();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float c = (a[x][y] - b[x][y]) * 255.0f;
            pixels[y * width + x] = ofClamp(c, 0.0f, 255.0f);
        }
    }
    img.update();
}

void ofApp::draw() {
    ofBackground(0);
    img.draw(0, 0, ofGetWidth(), ofGetHeight());
    gui.draw();
}

float ofApp::laplace(const std::vector<std::vector<float>>& grid, int x, int y) {
    float sum = 0.0f;
    sum += grid[x][y] * -1.0f;
    sum += grid[x - 1][y] * 0.2f;
    sum += grid[x + 1][y] * 0.2f;
    sum += grid[x][y - 1] * 0.2f;
    sum += grid[x][y + 1] * 0.2f;
    sum += grid[x - 1][y - 1] * 0.05f;
    sum += grid[x + 1][y - 1] * 0.05f;
    sum += grid[x - 1][y + 1] * 0.05f;
    sum += grid[x + 1][y + 1] * 0.05f;
    return sum;
}
