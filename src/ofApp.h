#pragma once

#include "ofMain.h"
#include "Slot.h"
#include "ofxOnce.h"
#include "ofxtiming.h"


#define GAME_STATE_OPENING 0
#define GAME_STATE_START 1
#define GAME_STATE_JACKPOT 2
#define GAME_STATE_FAIL 3


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void resetGame();
        void setupArduino(const int & version);

    
private:
    
    ofSoundPlayer bgsound;
    ofSoundPlayer sndJackpot;
    ofSoundPlayer sndJackpotFail;
    
    
    ofxOnce playJackpot;
    
    ofxTiming jackpotTime; //
    ofxTiming jackpotFailTime; //
    ofxTiming jackpotStartGame; //
    //ofxTiming jackpot; //
    

    double jackpotAnimTimer;
    int jackpotAnimIdx;
    
    int GAME_STATE;
    
    vector<Slot> slots; // declare the vector

    
    ofFbo fbo;
    int cnt;
    
    ofImage bgSlot;
    ofImage bgJackpot[2];
    ofImage bgJackpotFail;

    ofSerial	serial;

    

		
};
