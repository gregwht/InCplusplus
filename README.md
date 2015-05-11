# InCplusplus
Workshops in Creative Coding Project 2

IN C++ README
In C++ works on Mac OS X Yosemite 10.10.3, and should work on any operating system that supports the ofxMidi and ofxMaxim addons.

***
REQUIRES:
	•	Dan Wilcox’s ofxMIDI addon: https://github.com/danomatika/ofxMidi
	•	Mick Grierson’s ofxMaxim addon: https://github.com/micknoise/Maximilian

***
HOW TO RUN:
	•	Please put the InC++ master folder in your apps folder.
	•	When running the code, choose the number of virtual performers in ofApp.h, under #define PERFORMER_NUM
	•	Determine the tempo in ofApp.setup()
	•	Open your DAW of choice / prepare your MIDI hardware
	•	Route each MIDI track in your DAW to a separate Performer port (there should be one for each Performer)
	•	Allow monitoring / record-arm your tracks to hear incoming MIDI
	•	See video documentation on www.whitenoises.co.uk for example of how to run the program
	•	Feel free to direct any questions to @gregwht on Twitter.

***
Please enjoy In C++.

***


 ----------------------------------------------------
 ||                                                ||
 ||                    In  C++                     ||
 ||                 Version  0.15                  ||
 ||                 Gregory White                  ||
 ||                                                ||
 ----------------------------------------------------
 
 Workshops in Creative Coding Term 2 Project
 
 IS571015B
 
 MA in Computational Arts
 
 Goldsmiths' College
 
 Special thanks to Rebecca Fiebrink for showing me how to make this project in a much simpler and cleverer way, and for the wealth of general openFrameworks knowledge.
 
 Special thanks also to Kiona H. Niehaus, for helping me when my brain wouldn't math so good.

 Thanks to the MA/MFA Computational Arts cohort at Goldsmiths for the continued support, ideas, critiques, and inspiration.
 
 Thanks to Dan Wilcox, Chris O'Shea, Arturo Castro, and Kyle McDonald for the ofxMIDI addon ( https://github.com/danomatika/ofxMidi ), and Mick Grierson for Maximillian ( https://github.com/micknoise/Maximilian ).
 
 And finally, thanks to Terry Riley -- without you, this project could not exist. I hope it is on its way to doing your piece justice.
 
 
 ***
 
 Please note: All work for this project can be downloaded from https://github.com/gregcw/InCplusplus
 Further documentation, including a video, can be seen at www.whitenoises.co.uk 
 
 ***
 
 
 Aim
 ---
 The aim of my project this term was to create a program that would allow me to perform Terry Riley's 'In C' on my own. The program was to create a number of virtual performers that would independently make their own decisions about which notes to play, how hard or soft to play, when to progress to the next bar, and so on. The program would produce MIDI notes, which could be sent to software instruments, hardware instruments, or any other MIDI controlled devices (possibility for including lights etc).
 
 I decided to choose the piece 'In C' for a number of reasons, but primarily because when performing it, I realised that my thought process was rather algorithmic: I had 53 cells of information, each I would repeatedly excecute until I decided that I had passed a certain threshold -- at which point I would progress to the next cell. When all cells had been played, I would repeat the last until I decided to stop performing (terminate the program). 
 
 I thought it would be interesting to take the ensemble element out of the piece, and see how it could change, or what new ideas could be explored, when the decisions about which pitches to play were taken care of. What is the human performer's role? They could perform with an instrument alongside the machine; they could act as a conductor, influencing volume, pattern changes, the texture of the piece, the timbre of each performer, effects processing, and so on. And how is one person's interpretation of the piece different to an ensembles?
 
 But really, I wanted to make this project so that I could make a pun and call it 'In C++'.
 
 
 Process
 -------
 (For more detailed descriptions of what each individual function does, please see the main code).
 
 First, a number of virtual performers are created, given a MIDI channel and tempo. The pitch and time informtation for each of In C's 53 bars (and one extra bar for a C pulse - not yet fully implemented) are loaded with the loadBars() function. Their play() function is then called, which is where the performer calculates which pitch to play and when. The performers are kept within 3 bars of each other by comparing each performer's currentBar to the others -- if the distance is 3 or more, the lagging performer progresses when it finishes its current bar.
 
 A column of text is drawn to the screen for each performer, providing the user with details like the currentBar, what note is being played, how fast the performer is progressing, etc. This allows the user to make sure everything is progressing as it should, and make decisions about the length of the performance (using the commands in the keyPressed() function).
 
 Once a performer has reached the end of the last bar, it will keep repeating it, and its column of text will be drawn red. Once all of the performers have finished (or, not - be a creative snowflake) the user can then fade out the performers using their DAW/hardware instruments.
 
 
 Comments
 --------
 I'm very happy with the results so far, and am excited to keep working on this project, perhaps to be performed in the final exhibition.
 Currently I have explored a number of different interpretations of the piece:
    - One using mallet and chime software instruments (a more traditional approach, like others I have heard)
    - A more droney version heavy in reverb, where individual notes aren't heard -- instead, a small number of software instruments create amorphous clouds of sound
    - A percussion-only version, which does away with the pitch aspect of this piece. I thought this would be an interesting avenue to explore, since In C is very tonal (I mean, just look at the title), and using MIDI notes opens the piece up to a whole new interpretation. This version focuses on the polyrhytmic aspects of the piece, and the interaction and space between performers. (It is worth noting that not all of the pitches are mapped to sounds in Ableton, due to the sample banks I am using. I have left it this way, partly out of laziness, but partly because I like the space it brings to the piece: (From the Performing Directions) "It is very important that performers listen very carefully to one another and this means occasionally to drop out and listen."
    - I have also started looking at using external devices, namely my little MeeBlip Anode synth. I can't afford an ensemble of them however (unless someone wants to give me a grant???)
 
 
 Evaluation
 ----------

 Let's take a look at what I set out to complete at the beginning of term:
 
    > Minimum Deliverable:
        * Software that sends pre-programmed patterns of MIDI notes to DAWs
        * It should be able to play through the piece, selecting patterns without requiring human interaction
 
 I can comfortably say that the minimum deliverable has been achieved. Let's look at the desired deliverable:
 
    > Desired Deliverable:
        * Multiple simultaneous channels of MIDI notes (performers)                     -- Yes
        * Performers follow/influence each other RE: pattern selection                  -- Yes
        * Performers adjust volume automatically                                        -- Kind of - velocity adjusts. but not volume. Would benefit from more general dynamic movement
        * Ability to start from different sections of the piece (for debugging)         -- Kind of - user can progress through the bars with the UP and DOWN keys
 
 So overall, quite successful. I'm pleased with my submission, but there are definitely areas for improvement. Here's a list of the bugs to fix and features to implement over the next few versions:
 
 
    BUGS:
        - C pulse sounds out of time. Maybe other performers are out of time? But perhaps more interesting without the pulse, in percussion version (and droney version?)
        - When changing bar in the middle of a bar, the next bar doesn't start until phasor has returned to 1? (Drops not _necessarily_ a bad thing, as the score dictates that performers are allowed to drop out if they wish. But here, this is not determined by choice).
        - Whenever I try and rename the project, XCode crashes and deletes the project file. Therefore it is stuck at InC++ 0.07
        - Window displaying Performer information doesn't dynamically resize depending on how many Performers there are to display
        - Method of keeping Performers together doesn't work so well - try restraining the rushing Performers too
 
    FEATURES:
        - Make Performers not all start at once - delay a random amount of beats before coming in OR start on C pulse and move on to bar 1 after a certain time OR mix both
        - When determining next bar to play, make it a  9/10 chance that it'll be the next bar, and a 1/10 chance to play the C pulse. If C pulse, save currentBar as savedBar, then after performer is finished with C pulse, play savedBar + 1. Make it more likely that the others will play the pulse too (for example, it one other Performer is playing it, chance increases to 2/10. If two performers are playing it, chance indreases to 3/10 etc - perhaps likelihood should increase exponentionally?) Also requires some method of getting out of the C pulse, so all performers don't just get stuck there.
        - Orchestrate end: (Performance directions:) "IN C is ended in this way: when each performer arrives at figure #53, he or she stays on it until the entire ensemble has arrived there. The group then makes a large crescendo and diminuendo a few times and each player drops out as he or she wishes."
        - Form a trajacectory (random walk?) for volume/velocity, so that you get crescendos and diminuendos
        - Add functionality so that you can enter a time, and the program will play the piece over that amount of time
        - Add transposition feature: (Performance directions:) "It is OK to transpose patterns by an octave, especially to transpose up. Transposing down by octaves works best on the patterns containing notes of long durations. Augmentation of rhythmic values can also be effective."

