/*
 
 ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
 
 See main.cpp for acknolwedgements and detailed description of project aim, process, and evaluation.
 
 ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
 */


#pragma once

// Include header files from other classes, and Maximilian
#include "ofMain.h"
#include "Performer.h"
#include "Pulse.h"
#include "maximilian.h"

// Define the number of Performer objects
#define PERFORMER_NUM 5

class ofApp : public ofBaseApp {
    
public:
    
    void setup();
    void audioRequested 	(float * input, int bufferSize, int nChannels); // Adapted from Maximilan examples
    void draw();
    void keyPressed (int key);
    
    
    // Declare variables for Maximilian setup and audioRequested function
    int sampleRate;
    int initialBufferSize;
    
    
    // Declare virtual players
    Performer performer[PERFORMER_NUM];     // Declare array of Performer objects
    Performer port;     // Additional performer needs to be declared otherwise I get a bad excess error - not sure why.
    Pulse c;            // Declare C pulse object
    int tempo;          // Beats per minute

    
};
