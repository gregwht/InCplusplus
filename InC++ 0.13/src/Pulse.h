//
//  Pulse.h
//  InC++ 0.07
//
//  Created by Greg White on 27/04/2015.
//
//

#pragma once

#ifndef __InC___0_07__Pulse__
#define __InC___0_07__Pulse__

#include <stdio.h>

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxMaxim.h"

#endif /* defined(__InC___0_07__Pulse__) */

class Pulse : public ofBaseApp {
    
public:
    
    void setup(int _channel);
    
    // Added functions
    void openVirtualPort(string portName);    // For MIDI
    void openPort(int _port);    // For MIDI
    void exit();    // For MIDI
    void play(); /* output method */
    void loadBars(); // Load pitch and time information
    
    
    
    // MIDI stuff
    ofxMidiOut midiOut;
    int channel, note, velocity;
    
    
    //    // Declare audio stuff used in audioRequested function and end of setup()
    //    int sampleRate;
    //    int initialBufferSize;
    
    // Counter stuff
    ofxMaxiOsc metronome;                   // Phasor to count beats
    float currentTime;                      // The value used for time
    float previousTime;                     // Previous time - used to check when phasor resets
    bool beatCheck;                         // Turns off when reach end of pitch array to stop false triggering
    
    int tempo;                              // Beats per minute
    float freq;                             // Phasor frequency
    
    float progress;                         // Increases at the end of each bar
    float factor;                           // Factor by which progress increases
    
    float threshold;                        // When progress >= threshold, progress to next bar
    float margin;                           // random (per bar) +/- number added to threshold
    float margMin;                          // for ofRandom( );
    float margMax;                          // for ofRandom( );
    
    
    int previousBar;                        // Store previous bar to compare to currentBar, to check if bar has changed and progress counter needs resetting
    
    bool finished;                          // Flag when performer finishes last bar and is just repeating
    
    
    // Pattern stuff
    int currentBar;                         // Bar number
    int currentIndex;                       // Which pitch we are looking to play
    
    int arrayLength[4] = {1, 1, 1, 1};     // How many pitches are in the bar
    
    
    float beatsInBar[4] = {0.5, 0.5, 0.5, 0.5};    // How many beats are in the bar
    
    
    vector< vector<int> > pitch;
    vector< vector<float> > time;
    
    
};