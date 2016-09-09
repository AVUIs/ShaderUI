//
//  myAVUIFFT.cpp
//  myAVUI
//
//  Created by Shawn Lawson on 8/15/16.
//
//

#include "myAVUIFFT.h"


myAVUIFFT::myAVUIFFT(int nRects){
    
    numRects=nRects;
    mfft.setup(numRects, 512, 256);
    
    fourbins[0] = 0.0;
    fourbins[1] = 0.0;
    fourbins[2] = 0.0;
    fourbins[3] = 0.0;
    
}

void myAVUIFFT::draw(float * buffer, float amplitude){
    
    fourbins[0] = 0.0;
    fourbins[1] = 0.0;
    fourbins[2] = 0.0;
    fourbins[3] = 0.0;
    //wave
    ofPushStyle();
    ofFill();
    ofSetColor(visColor);
    float x;
    for(int i=0; i<512; i++){

        mfft.process(buffer[i]);
        float y2 = mfft.magnitudes[i] * (shape.height)/3;
        float rectWidth = shape.width/512;
        x = i*rectWidth;
        ofDrawRectangle(x, 0, rectWidth, y2);

        
        if (i < 32){
            fourbins[0] += mfft.magnitudes[i];
        } else if (i < 96) {
            fourbins[1] += mfft.magnitudes[i];
        } else if (i < 256) {
            fourbins[2] += mfft.magnitudes[i];
        } else {
            fourbins[3] += mfft.magnitudes[i];
        }
        
    }    
    ofPopStyle();
    
//            cout << fourbins[0] << " " << fourbins[1] << " " << fourbins[2] << " " << fourbins[3] << " " <<  endl;
    fourbins[0] /= 32.0;
    fourbins[1] /= 64.0;
    fourbins[2] /= 160.0;
    fourbins[3] /= 256.0;
    
    
    
}


