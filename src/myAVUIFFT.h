//
//  myAVUIFFT.h
//  myAVUI
//
//  Created by Shawn Lawson on 8/15/16.
//
//

#ifndef __myAVUI__myAVUIFFT__
#define __myAVUI__myAVUIFFT__

#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxAVUIVisualBase.h"

class myAVUIFFT : public ofxAVUIVisualBase {
public:
    // put any setup code in a custom constructor
    myAVUIFFT(int nRects);
    
    void draw(float *buffer, float amplitude);
    
    float fourbins[4];
    
private:
    ofxMaxiFFT mfft;
    int numRects;
    int fftSize;
    
};




#endif /* defined(__myAVUI__myAVUIFFT__) */
