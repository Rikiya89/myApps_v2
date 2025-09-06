#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowShape(720, 1080);
    ofSetWindowPosition(100, 100);
    ofSetFrameRate(60);
    ofBackground(20, 20, 30);
    ofSetVerticalSync(true);
    ofSetWindowTitle("Generative Typography Art");

    // Load font - smaller for portrait format
    font.load("Arial", 18);
    if (!font.isLoaded()) {
        font.load(OF_TTF_MONO, 18);
    }

    // Initialize variables
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%&*";
    words[0] = "GENERATIVE";
    words[1] = "TYPOGRAPHY";
    words[2] = "CREATIVE";
    words[3] = "DIGITAL";
    words[4] = "ARTFORM";

    time = 0.0f;
    waveSpeed = 2.0f;
    colorShift = 0.0f;
    showGrid = true;
    noiseScale = 0.01f;
    rotationSpeed = 1.0f;

    // Setup grid
    setupGrid();
}

//--------------------------------------------------------------
void ofApp::setupGrid() {
    // Dynamic grid based on actual window size
    int windowWidth = ofGetWidth();
    int windowHeight = ofGetHeight();

    // Calculate grid dimensions based on window size
    gridCols = windowWidth / 40;  // ~40px per column
    gridRows = windowHeight / 40; // ~40px per row

    // Ensure minimum grid size
    gridCols = max(gridCols, 10);
    gridRows = max(gridRows, 15);

    // Calculate cell size to fit the screen perfectly
    float availableWidth = windowWidth - 40;  // Leave margins
    float availableHeight = windowHeight - 80; // Leave margins

    float cellWidth = availableWidth / gridCols;
    float cellHeight = availableHeight / gridRows;
    cellSize = min(cellWidth, cellHeight) * 0.7f;

    gridSpacing = min(cellWidth, cellHeight);

    grid.clear();

    for (int row = 0; row < gridRows; row++) {
        for (int col = 0; col < gridCols; col++) {
            GridCell cell;
            cell.x = (col + 0.5f) * gridSpacing;
            cell.y = (row + 0.5f) * gridSpacing;
            cell.size = cellSize;
            cell.rotation = 0;
            cell.scale = 1.0f;
            cell.animationPhase = ofRandom(TWO_PI);
            cell.pulseSpeed = ofRandom(0.5f, 2.0f);

            generateRandomLetter(cell);
            grid.push_back(cell);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    time += ofGetLastFrameTime();
    colorShift += ofGetLastFrameTime() * 0.5f;

    updateGrid();
}

//--------------------------------------------------------------
void ofApp::updateGrid() {
    for (int i = 0; i < grid.size(); i++) {
        GridCell& cell = grid[i];

        // Wave animation
        float wave = sin(time * waveSpeed + cell.animationPhase);
        float noise = ofNoise(cell.x * noiseScale, cell.y * noiseScale, time * 0.3f);

        // Update rotation
        cell.rotation = wave * 45.0f + noise * 180.0f;

        // Update scale with pulse
        cell.scale = 0.8f + 0.4f * sin(time * cell.pulseSpeed + cell.animationPhase);

        // Update color based on position and time
        cell.color = getColorFromPosition(cell.x, cell.y, time);

        // Occasionally change letters
        if (ofRandom(1.0f) < 0.001f) {
            generateRandomLetter(cell);
        }

        // Add mouse interaction
        float mouseDistance = ofDist(mouseX, mouseY, cell.x, cell.y);
        if (mouseDistance < 100) {
            float influence = 1.0f - (mouseDistance / 100.0f);
            cell.scale += influence * 0.5f;
            cell.rotation += influence * 90.0f;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofPushMatrix();

    // Center the grid dynamically
    float offsetX = (ofGetWidth() - (gridCols * gridSpacing)) / 2;
    float offsetY = (ofGetHeight() - (gridRows * gridSpacing)) / 2;
    ofTranslate(offsetX, offsetY);

    // Draw grid lines if enabled
    if (showGrid) {
        ofSetColor(60, 60, 80, 100);
        ofSetLineWidth(1);

        // Vertical lines
        for (int col = 0; col <= gridCols; col++) {
            float x = col * gridSpacing;
            ofDrawLine(x, 0, x, gridRows * gridSpacing);
        }

        // Horizontal lines
        for (int row = 0; row <= gridRows; row++) {
            float y = row * gridSpacing;
            ofDrawLine(0, y, gridCols * gridSpacing, y);
        }
    }

    // Draw typography grid
    drawGrid();

    ofPopMatrix();

//    // Draw info - positioned dynamically
//    ofSetColor(255, 255, 255, 150);
//    int infoY = ofGetHeight() - 60;
//    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), 10, infoY);
//    ofDrawBitmapString("'g':grid 'r':regen SPACE:pause", 10, infoY + 20);
//    ofDrawBitmapString("Mouse to interact | Size: " + ofToString(ofGetWidth()) + "x" + ofToString(ofGetHeight()), 10, infoY + 40);
}

//--------------------------------------------------------------
void ofApp::drawGrid() {
    for (const GridCell& cell : grid) {
        ofPushMatrix();
        ofTranslate(cell.x, cell.y);
        ofRotateDeg(cell.rotation);
        ofScale(cell.scale);

        // Set color with some transparency for layering effect
        ofSetColor(cell.color, 180);

        // Draw letter
        string letter(1, cell.letter);
        ofRectangle bounds = font.getStringBoundingBox(letter, 0, 0);
        float x = -bounds.width / 2;
        float y = bounds.height / 2;

        font.drawString(letter, x, y);

        // Add subtle glow effect
        ofSetColor(cell.color, 60);
        ofScale(1.2f);
        font.drawString(letter, x, y);

        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::generateRandomLetter(GridCell& cell) {
    // Mix of random letters and word letters
    if (ofRandom(1.0f) < 0.3f) {
        // Use letter from word
        int wordIndex = ofRandom(5);
        int letterIndex = ofRandom(words[wordIndex].length());
        cell.letter = words[wordIndex][letterIndex];
    } else {
        // Random letter from alphabet
        cell.letter = alphabet[ofRandom(alphabet.length())];
    }
}

//--------------------------------------------------------------
ofColor ofApp::getColorFromPosition(float x, float y, float time) {
    // Create color based on position and time
    float normalizedX = x / (gridCols * gridSpacing);
    float normalizedY = y / (gridRows * gridSpacing);

    float hue = fmod((normalizedX * 360.0f + normalizedY * 180.0f + colorShift * 50.0f), 360.0f);
    float saturation = 150 + 50 * sin(time + normalizedX * TWO_PI);
    float brightness = 200 + 55 * cos(time * 0.7f + normalizedY * TWO_PI);

    return ofColor::fromHsb(hue, saturation, brightness);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch (key) {
        case 'g':
        case 'G':
            showGrid = !showGrid;
            break;

        case 'r':
        case 'R':
            setupGrid();
            break;

        case ' ':
            if (ofGetFrameRate() > 0) {
                ofSetFrameRate(0);
            } else {
                ofSetFrameRate(60);
            }
            break;

        case '+':
        case '=':
            waveSpeed = min(waveSpeed + 0.5f, 10.0f);
            break;

        case '-':
        case '_':
            waveSpeed = max(waveSpeed - 0.5f, 0.1f);
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    // Empty
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    // Mouse interaction is handled in updateGrid()
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    // Empty
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    // Add explosion effect at mouse position
    for (GridCell& cell : grid) {
        float distance = ofDist(x, y, cell.x, cell.y);
        if (distance < 150) {
            cell.animationPhase = ofRandom(TWO_PI);
            generateRandomLetter(cell);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    // Empty
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
    // Empty
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
    // Empty
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    // Recalculate grid for new window size
    setupGrid();
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    // Empty
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    // Empty
}
