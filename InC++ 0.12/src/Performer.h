//
//  performer.h
//  InC++ 0.07
//
//  Created by Greg White on 30/03/2015.
//
//

#pragma once

#ifndef __InC___0_07__performer__
#define __InC___0_07__performer__

#include <stdio.h>

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxMaxim.h"

#endif /* defined(__InC___0_07__performer__) */

class Performer : public ofBaseApp {
    
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
    
    int arrayLength[54] = {1, 6, 4, 3, 3,     // How many pitches are in the bar
        3, 1, 3, 2,
        2, 2, 6, 4,
        6, 4, 1, 4,
        5, 6, 1, 10,
        1, 9, 9, 9,
        9, 9, 11, 6,
        3, 1, 6, 7,
        2, 2, 22, 6,
        2, 3, 6, 2,
        2, 4, 9, 4,
        3, 11, 3, 3,
        6, 2, 3, 2,
        2 };
    
    float beatsInBar[54] = {1, 3, 2, 2, 2,    // How many beats are in the bar
        
        2, 8, 9.5, 14,
        4.5, 1, 1.5, 6,
        6, 16, 4, 1,
        1.5, 2, 3, 3,
        3, 12.5, 12, 10.5,
        10.5, 9.5, 3, 2,
        9, 6, 1.5, 6,
        0.75, 0.5, 29, 1.5,
        0.5, 0.75, 1.5, 0.5,
        0.5, 16, 3, 3,
        3, 5, 0.5, 15,
        1.5, 0.5, 0.75, 0.5,
        0.5};
    
    vector< vector<int> > pitch;
    vector< vector<float> > time;
    
    
};