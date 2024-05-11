#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup(){
        ofBackground(0);
        ofSetFrameRate(60);
        ofEnableDepthTest();
        ofSetSmoothLighting(true);
        light.setup();
        light.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 400);
    }

    void update(){

    }

    void draw(){
        // カメラの透視法を設定
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        float time = ofGetElapsedTimef();

        // 回転する3D形状を作成
        float radius = 200;
        float numPoints = 300;
        float angleIncrement = TWO_PI / numPoints;

        for (float angle = 0; angle < TWO_PI; angle += angleIncrement) {
            float x = radius * cos(angle + time);
            float y = radius * sin(angle + time);
            float z = ofMap(sin(angle * 5 + time), -1, 1, -100, 100);

            // 位置に基づいたカラーグラデーションを適用
            ofColor color;
            color.setHsb(ofMap(x, -radius, radius, 0, 255), 255, 255);
            ofSetColor(color);

            // サイズが異なる球体を描画
            float sphereSize = ofMap(z, -100, 100, 2, 10);
            ofDrawSphere(x, y, z, sphereSize);
        }

        ofPopMatrix();

        // シーンに照明を追加
        light.enable();
        cam.begin();
        cam.end();
        light.disable();
    }

private:
    ofLight light;
    ofEasyCam cam;
};

int main(){
    ofSetupOpenGL(1024, 768, OF_WINDOW);
    ofRunApp(new ofApp());
}
