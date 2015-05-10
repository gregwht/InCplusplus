/*
 
 ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
 
 See main.cpp for acknolwedgements and detailed description of project aim, process, and evaluation.
 
 ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
 */

#pragma once

#ifndef __InC___0_07__Pulse__
#define __InC___0_07__Pulse__

#include <stdio.h>

// Include header files for ofMain, and ofXMidi and ofxMaxim addons
#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxMaxim.h"

#endif /* defined(__InC___0_07__Pulse__) */

// Pulse class
class Pulse : public ofBaseApp {
    
public:
    
    // Added functions
    void openVirtualPort(string portName);  // Opens a virtual MIDI port
    // (Adapted from ofxMIDI exampleOutput)
    void openPort(int _port);   // Opens a real MIDI port
    // (Adapted from ofxMIDI exampleOutput)
    void setup(int _channel, float _tempo); // Setup function, passing through desired MIDI channel and tempo
    void exit();    // Closes MIDI port
    // (Adapted from ofxMIDI exampleOutput)
    void play();    // Main function, determining what notes to play
    void loadBars(); // Load pitch and time information
    void setVelocity(); // Calculate appropriate velocity for current note
    void nextIndex();   // Move on to next note
    
    // Declare MIDI class and variables
    ofxMidiOut midiOut;
    int channel, note, velocity;
    int randVelocity, rVMin, rVMax;         // Used in setVelocity() to make the performers sound more interesting
    
    
    // Declare Counter class and variables
    ofxMaxiOsc metronome;                   // Phasor to count beats
    float freq;                             // Phasor frequency
    float currentTime;                      // The current time value
    float previousTime;                     // Stored time value, used to check when phasor resets
    bool noteCheck;                         // Turns off when we reach the end of pitch array, to stop false triggering
    
    int tempo;                              // Beats per minute
    
    float progress;                         // Number which increases at the end of each repetition of a bar. Resets when bar changes.
    float factor;                           // Factor by which progress increases
    float threshold;                        // When progress >= threshold, progress to next bar
    float margin;                           // A random positve or negative number, generated per bar, which is added to threshold
    float margMin;                          // for ofRandom( );
    float margMax;                          // for ofRandom( );
    bool finished;                          // Flag when Pulse player finishes last bar
    
    
    // Pattern stuff
    int currentBar;                         // Bar number
    int previousBar;                        // Store previous bar to compare to currentBar, to check if bar has changed and therefore if progress counter needs resetting
    int currentIndex;                       // Which pitch we are looking to play
    
    int arrayLength[4] = {1, 1, 1, 1};     // How many pitches are in the bar
    
    float beatsInBar[4] = {0.5, 0.5, 0.5, 0.5};    // How many beats are in the bar
    
    // Multidimensional vectors for storing pitch and time values
    vector< vector<int> > pitch;
    vector< vector<float> > time;
    
    
};