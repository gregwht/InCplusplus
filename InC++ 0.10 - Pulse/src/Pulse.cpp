//
//  Pulse.cpp
//  InC++ 0.07
//
//  Created by Greg White on 27/04/2015.
//
//

#include "Pulse.h"

//--------------------------------------------------------------
void Pulse::openPort(string portName) {
    
    // MIDI stuff
    
    // print the available output ports to the console
    midiOut.listPorts(); // via instance
    //ofxMidiOut::listPorts(); // via static too
    
    // connect
    //midiOut.openPort(0); // by number
    //midiOut.openPort("IAC Driver Pure Data In"); // by name
    midiOut.openVirtualPort(portName); // open a virtual port
    
    
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
            velocity = 64;
            note = pitch[currentBar][currentIndex];
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
                if (progress >= threshold + margin && currentBar != 53){currentBar++;}
                
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
    
    
    // Add pitch values to vectors
    
    // C pulse
    p00.push_back(96);
    
    
    // Add bar vectors to main pitch vector
    pitch.push_back(p00);
    
    
    // Vectors to store time values
    vector<float> t00;
    
    
    // Add time values to vectors
    
    // C pulse
    t00.push_back(1);
    
    
    // Add bar vectors to main time vector
    time.push_back(t00);
   
}