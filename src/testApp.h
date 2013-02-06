#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofMesh mesh;
    ofEasyCam cam;
    ofVec3f center;
    ofShader sineShader, noiseShader;

    int shaderToApply; // 0 - none, 1 - sine, 2 - noise
    
    int waveDirection, waveFrequency;
    float noiseAmount;
};

