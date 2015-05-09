//
//  Pulse.cpp
//  InC++ 0.07
//
//  Created by Greg White on 27/04/2015.
//
//

#include "Pulse.h"

//--------------------------------------------------------------
void Pulse::openVirtualPort(string portName) {
    
    // MIDI stuff
    
    // print the available output ports to the console
    midiOut.listPorts(); // via instance
    //ofxMidiOut::listPorts(); // via static too
    
    // connect
    midiOut.openVirtualPort(portName); // open a virtual port
    
    
}

//--------------------------------------------------------------
void Pulse::openPort(int _port) {
    
    // MIDI stuff
    
    // print the available output ports to the console
    midiOut.listPorts(); // via instance
    //ofxMidiOut::listPorts(); // via static too
    
    // connect
    midiOut.openPort(_port); // by number
    
}


//--------------------------------------------------------------
void Pulse::setup(int _channel) {
    
    // Initialise MIDI values
    channel = _channel;
    note = 0;
    velocity = 0;
    
    // Initialise counter values
    currentTime = 0;
    previousTime = 0;
    beatCheck = true;
    
    tempo = 120;
    freq = (tempo/60)/beatsInBar[currentBar];
    
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
    
    // Remember to note where you have imported code!!!
    // Like here!!
    // clean up
    midiOut.closePort();
}

//--------------------------------------------------------------
void Pulse::play() {
    
    
    // Calculate speed of phasor
    freq = (tempo/60)/beatsInBar[currentBar]; // Thanks to Kiona H. Niehaus for figuring this calculation out!
    
    // Set phasor
    currentTime = metronome.phasor(freq, 1, beatsInBar[currentBar]+1);
    
    //-------------------------------------------------------------------------------------
    
    // Check to see if phasor has restarted
    // If so, check again for beats
    
    if (currentTime < previousTime){
        
        beatCheck = true;
    }
    
    
    if (beatCheck == true){
        
        
        // Check to see if progress counter needs resetting
        if (previousBar != currentBar){
            progress = 0;
            margin = ofRandom(margMin, margMax);
        }
        
        
        // Check if it's time to play a note
        if (currentTime >= time[currentBar][currentIndex]){
            
            
            // Send MIDI notes
            velocity = 100;
            note = pitch[currentBar][currentIndex];
            
            midiOut.sendNoteOn(channel, note, velocity);
            
            note = 72;
            midiOut.sendNoteOn(channel, note, velocity);
            
            
            // If there are more notes in the bar, increment current index
            if (currentIndex < pitch[currentBar].size()){
                
                currentIndex++;
                // Had to put inside an if statement, because when currentIndex went above pitch[currentBar].size(), it would send an extra MIDI note (value of 1)
            }
            
            
            // If there are no more notes in the bar, reset current index
            if (currentIndex >= pitch[currentBar].size()){
                
                beatCheck = false;
                currentIndex = 0;
                
                
                progress += beatsInBar[currentBar] * factor; // Using beatsInBar instead of pitch[currentBar].size() because otherwise ghost notes count as full beats
                previousBar = currentBar;
                
                
                // Check to see if we progress to next bar
                if (progress >= threshold + margin && currentBar < 3){
                    currentBar++;
                } else { currentBar = 0; }
                
            }
        }
        
    }
    
    // Set previousTime as the current time, so we can check at beginning of the loop
    previousTime = currentTime;
    
    //midiOut << NoteOff(channel, note, velocity);
    
    // Flag when performer has finished last bar
    if (progress >= threshold && currentBar == 53) {finished = true;}
    

    
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