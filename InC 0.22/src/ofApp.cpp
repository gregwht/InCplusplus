
#include "ofApp.h"



/*
 
 
 
 ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
 
 
 
 See main.cpp for acknolwedgements and detailed description of project aim, process, and evaluation.
 
 
 
 ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
 
 */



//--------------------------------------------------------------

void ofApp::setup() {
    
    
    
    // Boring drawing stuff
    
    ofSetVerticalSync(true);
    
    ofBackground(255);
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    
    allFinished = false;
    
    
    // Set tempo of Performer and Pulse objects
    
    tempo = 120;
    factor = 0.2;
    
    
    
    // Open a virtual MIDI port called "Pulse", for the pulse player...
    
    c.openVirtualPort("Pulse");
    
    // c.openPort(0);   // ...or open actual MIDI port 0
    
    c.setup(1, tempo, factor);    // Send to MIDI channel 1, set tempo to 120 bpm
    
    c.exit();           // Close the port
    
    c.loadBars();       // Load the pitch and time data to be played
    
    
    
    
    
    // Iterate through the number of Performers (defined in ofApp.h)
    
    // Note: Pulse players separate from Performers
    
    for (int i = 1; i < PERFORMER_NUM+1; i++){
        
        
        
        performer[i].openVirtualPort("Performer");  // Open virtual port called "Performer"
        
        performer[i].setup(i, tempo, factor);     // Send to MIDI channel i, set tempo to 120 bpm
        
        performer[i].exit();            // Close the port
        
        performer[i].loadBars();        // Load the pitch and time data to be played
        
    }
    
    
    
    
    
    // Audio settings for Maximillian (adapted from Maximilan examples)
    
    // As this app does not send any audio, variables like 'initChannels' shouldn't have too much of an impact.
    
    sampleRate = 44100;
    
    initialBufferSize = 1024;
    
    ofxMaxiSettings::setup(sampleRate, 2, initialBufferSize);
    
    
    
    // Make sure to call this at the end of setup!!
    
    ofSoundStreamSetup(2,0, this, maxiSettings::sampleRate, initialBufferSize, 4);
    
    
    // Load score image
    score.loadImage("images/score_small.png");
    
}


//--------------------------------------------------------------

void ofApp::update() {
    
    ofBackground(255);
}


//--------------------------------------------------------------

void ofApp::audioRequested  (float * output, int bufferSize, int nChannels){
    
    
    
    // This is the main function which calls all of the Pulse and Performer objects to play, keeping them within 3 bars of each other.
    
    // This function has been adapted from Maximilian examples
    
    
    
    for (int i = 0; i < bufferSize; i++){
        
     
        c.play();
        
        
        
        for (int i = 1; i < PERFORMER_NUM+1; i++){
            
            performer[i].play();
            
            
            
            // Check to see that performers haven't drifted too far apart:
            
            for (int j = 1; j < PERFORMER_NUM+1; j++){
                
                
                
                // If the distance between performers is 4 bars or greater...
                
                if (performer[i].currentBar - performer[j].currentBar >= 4){
                    
                    
                    
                    //...when the lagging performer finishes their bar, progress to the next one
                    
//                    if (performer[j].currentTime < performer[j].previousTime) {
                    
                            performer[j].currentBar++;
                        
//                    }
                    
                }
                
            }
    
        }
        
    } // end for (bufferSize)
    
    
    
}   // end audioRequested



//--------------------------------------------------------------

void ofApp::draw() {
    
    
    
    // Drawing information for each performer to the screen
    
    // This allows you to judge if everything is working correctly, and gives a sense of how the piece is progressing / how you are to the end.
    
    // This function has been adapted from Dan Wilcox's ofxMIDI 'exampleOutput' project file
    
    
    
    for (int i = 1; i < PERFORMER_NUM+1; i++){
        
        
        
        // WHen a performer finishes playing their bars, their text becomes red to indicate they are finished.
        
        
        
        if (performer[i].finished == false){ofSetColor(0);}
        
        else {ofSetColor(255, 0, 0);}
        
        
        
        stringstream text;
        
        text << "sending to channel " << performer[i].channel << endl << endl
        
        
        << "tempo: " << performer[i].tempo << endl
        
        << "freq: " << performer[i].freq << endl << endl
        
        
        
        << "factor: " << performer[i].factor << endl
        
        << "inital threshold: " << performer[i].initThreshold << endl
        
        << "margin: " << performer[i].margin << endl
        
        << "current threshold: " << performer[i].threshold << endl
        
        << "progress: " << performer[i].progress << endl << endl
        
        
       
        << "bar: " << performer[i].currentBar << endl
    
        
        << "beats in bar: " << performer[i].beatsInBar[performer[i].currentBar] << endl
        
        << "current time: " << performer[i].currentTime << endl
        
        << "pitches in bar: " << performer[i].arrayLength[performer[i].currentBar] << endl << endl
        
        
        
        << "note: " << performer[i].note << endl
        
        << "current index: " << performer[i].currentIndex << endl
        
        << "velocity: " << performer[i].velocity << endl << endl
        
    
        
        << "finished: " << performer[i].finished << endl;
        
        if (i <= 4){ ofDrawBitmapString(text.str(), 60 + ((i-1) * ofGetWidth()/4), 40); }
        
        else { ofDrawBitmapString(text.str(), 60 + ((i-5) * ofGetWidth()/4), 40 + (ofGetHeight()/2));}
        
    }
    ofSetColor(255);
   // score.draw(0, 0);
}



//--------------------------------------------------------------

void ofApp::keyPressed(int key) {
    
    
    
    // Allows control over Performers' progress using key presses.
    
    // This way, if the performance is going too slow / quick, you can adjust on-the-fly.
    
    // You can force each Performer to:
    
    //   - Go to the next or previous bar
    
    //   - Increase or decrease the threshold at which they progress to next bar
    
    //   - Increase or decrease the factor by which progress occurs
    
    
    
    for (int i = 1; i < PERFORMER_NUM+1; i++){
        
        
        
        switch(key) {
                
                
                
                
                
            case OF_KEY_UP:
                
                
                
                performer[i].currentBar++;
                
                
                
                break;
                
            case OF_KEY_DOWN:
                
                
                
                performer[i].currentBar--;
                
                
                
                break;
                
            case OF_KEY_LEFT:
                
                
                
                performer[i].threshold--;
                
                
                
                break;
                
            case OF_KEY_RIGHT:
                
                
                
                performer[i].threshold++;
                
                
                
                break;
                
            case '-':
                
                performer[i].factor *= 0.9;
                
                
                
                break;
                
            case '=':
                
                performer[i].factor *= 1.1;
                
                
                
        }
        
    }
    
}

