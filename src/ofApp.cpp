#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    jackpotAnimIdx = 0;
    
    for (int i=0; i< 3; i++) {
        Slot newSlot;
        slots.push_back( newSlot );     //Add this particle to array
    }
    
    
    bgSlot.loadImage("mesin_jekpot.png");
    
    bgJackpot[0].loadImage("slot_jackpot_a.png");
    bgJackpot[1].loadImage("slot_jackpot_b.png");
    
    bgJackpotFail.loadImage("slot_jackpot_zonk.png");
    
    bgsound.loadSound("");
    bgsound.setLoop(true);
    
    
    sndJackpot.loadSound("slot_jackpot.wav");
    sndJackpot.setLoop(false);
    
    sndJackpotFail.loadSound("slot_fail.wav");
    sndJackpotFail.setLoop(false);
    
    slots.at(0).moveIndex(1);
    slots.at(1).moveIndex(1);
    slots.at(2).moveIndex(1);
    
    slots.at(0).setup(0,10);
    slots.at(1).setup(116 + 36,10);
    slots.at(2).setup(304,10);
    
    fbo.allocate(420, 196);
    ofSetBackgroundColor(0);
    
    jackpotTime.setInterval(5);
    jackpotFailTime.setInterval(2);
    jackpotStartGame.setInterval(3);
    
    GAME_STATE = GAME_STATE_START;
    
//    ard.connect("/dev/cu.usbmodem1411", 57600);
//	ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
//	bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
    
    serial.setup("/dev/cu.usbmodem1411", 115200);
    
    cnt = 0;

}



//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {
	
//	// remove listener because we don't need it anymore
//	ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
//    
//    // it is now safe to send commands to the Arduino
//    bSetupArduino = true;
//    
//    // print firmware name and version to the console
//    ofLogNotice() << ard.getFirmwareName();
//    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
//    
//
//    // set pin D13 as digital output
//	ard.sendDigitalPinMode(13, ARD_OUTPUT);
//    // set pin A4 as digital output
    
}


//--------------------------------------------------------------
void ofApp::update(){
    
    
    if (GAME_STATE ==  GAME_STATE_START)
    {
        
        for(int i = 0; i < slots.size(); i++){
            slots[i].update();
        }
        
        //check if jackpot
        int allfinished = 0;
        for(int j = 0; j < slots.size(); j++){
            if (slots.at(j).finished)
            {
                allfinished++;
            }
        }
        if (allfinished == 3)
        {
            int idx = slots.at(0).getIndexFromYpos();
            if (slots.at(1).getIndexFromYpos() == idx && slots.at(2).getIndexFromYpos() == idx )
            {
                GAME_STATE = GAME_STATE_JACKPOT;
                jackpotTime.reset();
                jackpotStartGame.reset();
                sndJackpot.play();
                
            }else{
                
                
                if (jackpotFailTime.tick())
                {
                    GAME_STATE = GAME_STATE_FAIL;
                    jackpotFailTime.reset();
                    jackpotStartGame.reset();
                    sndJackpotFail.play();
                    serial.writeByte('0');
                }
                
                
            }
            
        }
        //end check if jackpot
        
    }
    else if (GAME_STATE == GAME_STATE_JACKPOT)
    {
        
        if (jackpotTime.tick()){
            GAME_STATE = GAME_STATE_START;
            cnt = 0;
            resetGame();        
        }
    }

    else if (GAME_STATE == GAME_STATE_FAIL)
    {
        
        if (jackpotStartGame.tick())
        {
            GAME_STATE = GAME_STATE_START;
            cnt = 0;
            resetGame();
        }
        
        
    }

    

}

void ofApp::resetGame()
{
    
    for(int i = 0; i < slots.size(); i++){
        slots[i].restart();
    }
}


//--------------------------------------------------------------
void ofApp::draw(){

    if (GAME_STATE ==  GAME_STATE_START)
    {
        
        ofBackground(0);
        
        bgSlot.draw(0, 0);
        
        fbo.begin();
            ofClear(0);
            for(int i = 0; i < slots.size(); i++){
                slots[i].draw();
            }
        fbo.end();
        
        fbo.draw(299, 170);
        
    }
        else if (GAME_STATE ==  GAME_STATE_JACKPOT)
    {
        
        if (playJackpot.once())
        {
            sndJackpot.play();
        }
        
        
        jackpotAnimTimer += ofGetLastFrameTime();
        
        if (jackpotAnimTimer > 0.125) {
            //printf("timer %i\n", jackpotAnimIdx);
            jackpotAnimIdx += 1;
            jackpotAnimTimer = 0;
            jackpotAnimIdx = jackpotAnimIdx % 2;
        }
        
        
        bgJackpot[jackpotAnimIdx].draw(0, 0);

        
    }
    
        else if (GAME_STATE ==  GAME_STATE_FAIL)
    
    {
        bgJackpotFail.draw(0,0);
        
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (GAME_STATE == GAME_STATE_START)
    {
    
        if (key == ' ')
        {
            if (cnt < 3)
            {
            slots.at(cnt).stopAtNextIndex();
            
            cnt = cnt + 1;
            cnt = cnt % 3;
            }
        }
        
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 't') ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
