#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxAVUI.h"
#include "myAVUIFFT.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofTrueTypeFont font;
    ofShader shader;
    ofMesh  mesh;

    // Audio output and input methods
    
    void audioOut(float * output, int bufferSize, int nChannels);
    void audioIn(float * input, int bufferSize, int nChannels);
    
    int		bufferSize;
    int		sampleRate;
    
    //ofxAVUI
    ofxAVUIZone             zones[4];
    myAVUIFFT               *visual1;
    bool                    drawUI;

    
};