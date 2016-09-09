#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//  basic setup
    ofBackground(34, 34, 34);
    ofSetVerticalSync(false);
    ofEnableAlphaBlending();
    
//  shader stuff
    font.load("type/verdana.ttf", 100, true, false, true, 0.4, 72);
    shader.load("shaders/noise.vert", "shaders/noise.frag");
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    mesh.addVertex( ofPoint(0,0) );
    mesh.addTexCoord( ofPoint(0,0) );
    
    mesh.addVertex( ofPoint(ofGetWidth(),0) );
    mesh.addTexCoord( ofPoint(1,0) );
    
    mesh.addVertex( ofPoint(0,ofGetHeight()) );
    mesh.addTexCoord( ofPoint(0,1) );
    
    mesh.addVertex( ofPoint(ofGetWidth(),ofGetHeight()) );
    mesh.addTexCoord( ofPoint(1,1) );
    
//  audio setup
    sampleRate 	= 44100; /* Audio sampling rate */
    bufferSize	= 512; /* Audio buffer size */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
//  UI steup
    drawUI = true;
    //ZONE 0 SETUP
    //parameters: name, x, y, width, background color, foreground color, sound filename, sound buffer size
    zones[0].setup("zone1", 50, 50, 200, ofColor(0,0,0,255), ofColor(255,255,255,255), "sounds/sound.wav", bufferSize);
    //toggle parameters: caption, toggle (double tap) parameter name
    ofxAVUIToggle *toggle1 = new ofxAVUIToggle("Looping", ofxAVUIZone::TOGGLE_LOOPING);
    zones[0].addUI(toggle1, 50);
    //button parameters: caption, trigger (single tap) parameter name
    ofxAVUIButton *button1 = new ofxAVUIButton("Trigger", ofxAVUIZone::TRIGGER_PLAY);
    zones[0].addUI(button1, 50);
    //pad parameters: caption, trigger (single tap) parameter name, toggle (double tap) parameter name, x parameter name, y parameter name
    zones[0].addParameterFloat("SpeedX", -10,10,1);
    zones[0].addParameterFloat("SpeedY", -10,10,1);
    
    //  couldn't pass NULL
    ofxAVUIXYPad *pad1 = new ofxAVUIXYPad("Speed", "null",  "null", "SpeedX", "SpeedY");
    //pad additional parameter: height
    zones[0].addUI(pad1, 200);
    
//    //can't set size
    visual1 = new myAVUIFFT(bufferSize);
    zones[0].addVisual(visual1, ofColor(0,0,255,230));

    zones[1].setup("zone2", 300, 50, 200, ofColor(0,0,0,255), ofColor(255,255,255,255), "null", bufferSize);
    zones[1].addParameterBool("Effect1", 1);
    ofxAVUIToggle *toggle2 = new ofxAVUIToggle("Effect 1", "Effect1");
    zones[1].addUI(toggle2, 50);
    zones[1].addParameterBool("Effect2", 0);
    ofxAVUIToggle *toggle3 = new ofxAVUIToggle("Effect 2", "Effect2");
    zones[1].addUI(toggle3, 50);
    zones[1].addParameterBool("Effect3", 0);
    ofxAVUIToggle *toggle4 = new ofxAVUIToggle("Effect 3", "Effect3");
    zones[1].addUI(toggle4, 50);
    zones[1].addParameterBool("Effect4", 0);
    ofxAVUIToggle *toggle5 = new ofxAVUIToggle("Effect 4", "Effect4");
    zones[1].addUI(toggle5, 50);
    
    zones[2].setup("zone3", 550, 50, 150, ofColor(0,0,0,255), ofColor(255, 255, 255, 255), "null", bufferSize);
    zones[2].addParameterFloat("rValue", 0, 1.0, 0.5);
    zones[2].addParameterFloat("gValue", 0, 1.0, 0.5);
    zones[2].addParameterFloat("bValue", 0, 1.0, 0.5);
    ofxAVUISlider *redSlider = new ofxAVUISlider("Red Slider", "null", "null", "rValue");
    ofxAVUISlider *greenSlider = new ofxAVUISlider("Green Slider", "null", "null", "gValue");
    ofxAVUISlider *blueSlider = new ofxAVUISlider("Blue Slider", "null", "null", "bValue");
    zones[2].addUI(redSlider, 40);
    zones[2].addUI(greenSlider, 40);
    zones[2].addUI(blueSlider, 40);
    
    
    //START SOUND
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    /* this has to happen at the end of setup */
    /* why is that? */
    

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofParameter<float> x = zones[0].getParamValueFloat("SpeedX");
    ofParameter<float> y = zones[0].getParamValueFloat("SpeedY");

    ofParameter<float> fft1 = visual1->fourbins[0];
    ofParameter<float> fft2 = visual1->fourbins[1];
    ofParameter<float> fft3 = visual1->fourbins[2];
    ofParameter<float> fft4 = visual1->fourbins[3];
    
    ofParameter<bool> e1 = zones[1].getParamValueBool("Effect1");
    ofParameter<bool> e2 = zones[1].getParamValueBool("Effect2");
    ofParameter<bool> e3 = zones[1].getParamValueBool("Effect3");
    ofParameter<bool> e4 = zones[1].getParamValueBool("Effect4");
    
    ofParameter<float> c1 = zones[2].getParamValueFloat("rValue");
    ofParameter<float> c2 = zones[2].getParamValueFloat("gValue");
    ofParameter<float> c3 = zones[2].getParamValueFloat("bValue");
    
    ofSetColor(255);
    ofFill();
    
    shader.begin();
    shader.setUniform1f("timeValX", ofGetElapsedTimef() * x );
    shader.setUniform1f("timeValY", ofGetElapsedTimef() * y );
    shader.setUniform4f("bands", fft1, fft2, fft3, fft4);
    shader.setUniform4i("effect", (int)e1, (int)e2, (int)e3, (int)e4);
    shader.setUniform3f("colorIn", c1, c2, c3);
    
    
    mesh.draw();

    shader.end();

    if ( drawUI ) {
        for (int k=0; k<3; k++) {
            zones[k].draw();
        }
    }

}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
        output[i*nChannels    ] = 0;
        output[i*nChannels + 1] = 0;
        
        for (int k=0; k<3; k++) {
            zones[k].play(i);
            output[i*nChannels    ] += zones[k].getOutput(0);
            output[i*nChannels + 1] += zones[k].getOutput(1);
        }
    }
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        /* you can also grab the data out of the arrays*/
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key) {
        case 'u':
            drawUI = !drawUI;
            break;
            
        default:
            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
