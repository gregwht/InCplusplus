/*
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxMidi for documentation
 *
 */


// Special thanks to Rebecca Fiebrink for showing me how to make this project in a much simpler and cleverer way, and the general openFrameworks knowledge.
// Special thanks also to Kiona H. Niehaus, for helping me when my brain wouldn't math so good.
// Finally, thanks to the MA/MFA Computational Arts cohort at Goldsmiths for the continued support, ideas, critiques, and inspiration.

#pragma once

#include "ofMain.h"
#include "Performer.h"
#include "Pulse.h"
#include "maximilian.h"

#define PERFORMER_NUM 5

class ofApp : public ofBaseApp {
    
public:
    
    void setup();
    void update();
    void draw();
    void audioRequested 	(float * input, int bufferSize, int nChannels); /* output method */
    
    void keyPressed (int key);
    void keyReleased (int key);
    
    // Declare audio stuff used in audioRequested function and end of setup()
    int sampleRate;
    int initialBufferSize;
    
    
    Performer performer[PERFORMER_NUM];
    Performer port;
    int tempo;                              // Beats per minute
    Pulse c;
    
};

/* BUGS:
 - CHECK ALL BARS ARE CORRECT
 - Bar 32: Think last note isn't there
 - Bar 47: Think missing note
 - C pulse sounds out of time. Maybe other performers are out of time?
 - When changing bar in the middle of a bar, the next bar doesn't start until phasor has returned to 1? (Drops not _necessarily_ a bad thing, as the score dictates that performers are allowed to drop out if they wish. But here, this is not determined by choice).
 
 
 FEATURES:
 - Add velocity randomness (random walk?) - form a trajectory.
 - Add velocity randomness to pulse (more linear)
 - Performers don't all start at once - delay a random amount of beats before coming in OR start on C pulse and move on to bar 1 after a certain time OR mix both
 - Next bar 9/10 the next bar, 1/10 C pulse. If C pulse, save currentBar as savedBar, then after performer is finished with C pulse, play savedBar + 1.
 - Orchestrate end: "IN C is ended in this way: when each performer arrives at figure #53, he or she stays on it until the entire ensemble has arrived there. The group then makes a large crescendo and diminuendo a few times and each player drops out as he or she wishes."
 - Set tempo with constructor
 - Don't let repetitions go on for over 90 secs: "There is no fixed rule as to the number of repetitions a pattern may have, however, since performances normally average between 45 minutes and an hour and a half, it can be assumed that one would repeat each pattern from somewhere between 45 seconds and a minute and a half or longer."
 - Add functionality so that you can enter a time, and the program will play the piece over that amount of time
 - Add transposition feature: "It is OK to transpose patterns by an octave, especially to transpose up. Transposing down by octaves works best on the patterns containing notes of long durations. Augmentation of rhythmic values can also be effective."
 - Separate Performer's process into more functions?
 - Comment code
 - Multiple videos showing different Ableton instruments, real synth

 
 */
