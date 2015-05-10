/*
 
 ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
 
 See main.cpp for acknolwedgements and detailed description of project aim, process, and evaluation.
 
 ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
 */

#include "Pulse.h"

/* 
 
 The Pulse class is much the same as the Performer class, but I have changed the loadBars() and nextIndex() functions so that it loops over four bars of C notes.
 
 At first I tried an alternative, simplified method that got rid of the loadBars() function, with the C pitches loaded directly in play(). However this caused timing issues compared to the Performers.

 In fact, the Pulse class still sounds slightly out of time with the Performer classes, which seem to be in time with themselves. I am still trying to work out why this might be the case.
*/


//--------------------------------------------------------------
void Pulse::openVirtualPort(string portName) {
    
    
    // This function opens a virtual MIDI port
    // This function has been adapted from Dan Wilcox's ofxMIDI 'exampleOutput' project file
    
    // print the available output ports to the console
    midiOut.listPorts(); // via instance
    ofxMidiOut::listPorts(); // via static too
    
    // connect
    midiOut.openVirtualPort(portName); // Open the virtual port
    
}

//--------------------------------------------------------------
void Pulse::openPort(int _port) {
    
    // This function opens a real MIDI port
    // This function has been adapted from Dan Wilcox's ofxMIDI 'exampleOutput' project file
    
    // print the available output ports to the console
    midiOut.listPorts(); // via instance
    ofxMidiOut::listPorts(); // via static too
    
    // connect
    midiOut.openPort(0); // Open the real port
}


//--------------------------------------------------------------
void Pulse::setup(int _channel, float _tempo) {
   
    
    // Initialise MIDI values
    channel = _channel;
    note = 0;
    velocity = 0;
    rVMin = -10;
    rVMax = 10;
    randVelocity = ofRandom(rVMin, rVMax);  // Generate a random number between rVMin and rVMax to add to velocity in setVeloicty() function
    
    // Initialise counter values
    currentTime = 0;
    previousTime = 0;
    noteCheck = true;
    
    tempo = _tempo;
    freq = (tempo/60)/beatsInBar[0];
    
    progress = 0;
    factor = 1;
    
    threshold = 10;
    margMin = -10;
    margMax = 10;
    margin = (int) ofRandom(margMin, margMax);
    
    previousBar = 0;
    
    finished = false;
    
    // Initialise pattern values
    currentBar = 0;
    currentIndex = 0;

    
}

//--------------------------------------------------------------
void Pulse::exit() {
    
    
    // This function has been adapted from Dan Wilcox's ofxMIDI 'exampleOutput' project file
    midiOut.closePort();
}

//--------------------------------------------------------------
void Pulse::play() {
    
    // This is the main function in which the Pulse player decides which notes to play and when.
    
    // It uses a phasor, called currentTime, that ramps from 1 to the number of beats in the current bar.
    // The Pulse player checks to see if the phasor is equal to or has passed the 'time' value for the next note to be played. (See loadBars() function for more information on how this data is stored).
    // E.g. if the first beat in a particular bar is to be played on beat 2, the Pulse player looks for currentTime >= 2.
    // If this is true, the pitch and velocity are calculated, and the Pulse player progresses to check for the next note in the bar (or, if the last note in the bar has been played, stops checking for notes and resets currentIndex to 0)
    // At the end of the loop, currentTime is stored as previousTime, so that it can be compared at the top of the next loop. If currentTime < previousTime, this tells us that the phasor has reset back to 1, and that the Pulse player needs to start checking for notes again.
    // Finally, we also check whether the Pulse player has finished playing all of their bars, so that we can flag them as finished by drawing their text in red in ofApp.draw().
    
    // Calculate speed of phasor
    freq = (tempo/60)/beatsInBar[currentBar]; // Thanks to Kiona H. Niehaus for figuring this calculation out!
    
    // Set phasor
    currentTime = metronome.phasor(freq, 1, beatsInBar[currentBar]+1);
    
    //-------------------------------------------------------------------------------------
    
    // Check to see if the phasor has reset back to 1
    if (currentTime < previousTime){
        
        // If so, check again for notes
        noteCheck = true;
    }
    
    
    
    if (noteCheck == true){
        
        
        // If the last bar played is not the same as the current bar, reset the progress counter
        if (previousBar != currentBar){
            progress = 0;
            margin = ofRandom(margMin, margMax); // Generate a random number to be added to 'threshold' (see nextIndex() for more details)
        }
        
        
        
        // Check if it's time to play a note
        if (currentTime >= time[currentBar][currentIndex]){
            
            // If so, prepare the C pulse...
            note = pitch[currentBar][currentIndex];
            setVelocity();
            
            // ...and send it
            midiOut.sendNoteOn(channel, note, velocity);
            
            // Also play the octave below
            note = 72;
            midiOut.sendNoteOn(channel, note, velocity);
            
            // Then figure out what note to play next (Hint:...it's a C)
            nextIndex();
        }
        
    }
    
    // Record the current time as previousTime, so we can check when the phasor restarts above
    previousTime = currentTime;
    
    //midiOut << NoteOff(channel, note, velocity);
    
    // Flag when Pulse player has finished the last bar (only goes up to 03 for Pulse player, before resetting)
    if (progress >= threshold && currentBar == 03) {finished = true;}
    
}

//--------------------------------------------------------------
void Pulse::setVelocity() {
    
    // This function determines what velocity each note should be played at, giving a more interesting, and hopefully more 'human' feel.
    
    // First, generate a random number between rVMin and rVMax. This is added to the velocities below to provide an element of variety
    randVelocity = ofRandom(rVMin, rVMax);
    
    // If the note is the first to be played in the bar, give it emphasis
    if (currentIndex == 0){
        
        velocity = 110 + randVelocity;
        
        // If the note is on an offbeat, play it softer
    } else if (currentIndex % 2 == 0){
        
        velocity = 64 + randVelocity;
        
        // If the note is on an onbeat, play it harder (but not as hard as the first beat of the bar)
    } else {
        
        velocity = 80 + randVelocity;
    }
}

//--------------------------------------------------------------
void Pulse::nextIndex() {
    
    // This function determines what note to check for next, using the variable 'currentIndex'

    // If there are more notes in the bar, increment current index
    if (currentIndex < pitch[currentBar].size()){
        
        currentIndex++;
        // Had to put inside an if statement, because when currentIndex went above pitch[currentBar].size(), it would send an extra MIDI note (value of 1)
    }
    
    
    // If there are no more notes in the bar, reset current index
    if (currentIndex >= pitch[currentBar].size()){
        
        noteCheck = false;
        currentIndex = 0;
        
        // When the whole bar has been played, add to the progress value
        progress += beatsInBar[currentBar] * factor; // Here I am using beatsInBar instead of pitch[currentBar].size() because otherwise ghost notes count as full beats
        
        // Store the played bar as previousBar, so that we can check if we have reached a new bar at the top of Pulse player.play()
        previousBar = currentBar;
        
        
        // Check to see if we progress to next bar, or reset back to the beginning
        if (progress >= threshold + margin && currentBar < 3){
            currentBar++;
        } else { currentBar = 0; }
    }
}


//--------------------------------------------------------------
void Pulse::loadBars() {
    
    // Pitch and time data
    
    // Vectors to store pitch values
    vector<int> p00;
    vector<int> p01;
    vector<int> p02;
    vector<int> p03;
    
    // Add pitch values to vectors
    p00.push_back(84);
    p01.push_back(84);
    p02.push_back(84);
    p03.push_back(84);
    
    // Add bar vectors to main pitch vector
    pitch.push_back(p00);
    pitch.push_back(p01);
    pitch.push_back(p02);
    pitch.push_back(p03);
    
    // Vectors to store time values
    vector<float> t00;
    vector<float> t01;
    vector<float> t02;
    vector<float> t03;
    
    // Add time values to vectors
    t00.push_back(1);
    t00.push_back(1.125);
    t00.push_back(1.25);
    t00.push_back(1.375);
    t00.push_back(1.5);
    t00.push_back(1.625);
    t00.push_back(1.75);
    t00.push_back(1.875);
    
    t01.push_back(1);
    t01.push_back(1.125);
    t01.push_back(1.25);
    t01.push_back(1.375);
    t01.push_back(1.5);
    t01.push_back(1.625);
    t01.push_back(1.75);
    t01.push_back(1.875);
    
    t02.push_back(1);
    t02.push_back(1.125);
    t02.push_back(1.25);
    t02.push_back(1.375);
    t02.push_back(1.5);
    t02.push_back(1.625);
    t02.push_back(1.75);
    t02.push_back(1.875);
    
    t03.push_back(1);
    t03.push_back(1.125);
    t03.push_back(1.25);
    t03.push_back(1.375);
    t03.push_back(1.5);
    t03.push_back(1.625);
    t03.push_back(1.75);
    t03.push_back(1.875);
    
    // Add bar vectors to main time vector
    time.push_back(t00);
    time.push_back(t01);
    time.push_back(t02);
    time.push_back(t03);
   
}