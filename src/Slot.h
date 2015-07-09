//
//  Slot.h
//  mesinslotcoba
//
//  Created by xcorex on 6/17/15.
//
//

#ifndef mesinslotcoba_Slot_h
#define mesinslotcoba_Slot_h

#include "ofMain.h"

class Slot {
public:
    Slot()
    {
        slotpos_x = 0;
        slotpos_y = 0;
        slot_height = 196;
        slot_width = 116;
        total_slot = 5;
        cur_index = 0;
        speed = 10;
        finished = false;
        
        slotImg.loadImage("slot_img.png");
        slotImgCover.loadImage("slot_img_cover.png");
        
        ispaused = false;
        stopnext = false;
        
        sndSpin.loadSound("slot_spin.wav");
        sndSpin.setLoop(true);
        sndSpin.play();
        
        
        sndStop.loadSound("slot_stop.wav");
        sndStop.setLoop(false);
        //sndStop.play();
        
        
        
    }
    
    void restart()
    {
        ispaused = false;
        stopnext = false;
        finished = false;
        slotpos_y = 0;
        sndSpin.play();
    }
    
    void setup(int x, int _speed = 10)
    {
        slotpos_x = x;
        speed = _speed;
    }
    
    void moveIndex(int index)
    {
        if (index != 0)
        {
            slotpos_y = - ((index) * slot_height);
        }else{
            slotpos_y = -0.4;
        }
    }
    
    
    void update()
    {
        if (stopnext)
        {
            if (!ispaused)
            {
                sndSpin.stop();
                if (next_stop_index  == getIndexFromYpos()){
                    finished = true;
                    stop(true);
                };
            }
        }
        if (!ispaused){
            slotpos_y = slotpos_y - speed;
            if( abs(slotpos_y) >  (slot_height * total_slot) )
            {
                moveIndex(0);
            }
        }
    }
    
    
    int getIndexFromYpos(bool half = false)
    {
        int slot_accum;

        for (int i = 1; i < (total_slot+1); i++)
        {
            slot_accum = slot_height * (i);
            
            if (half)
            {
                
                if (abs(slotpos_y) < slot_accum - (slot_height * 0.8))
                {
                    return i;
                }
                
            }else{
                
                if (abs(slotpos_y) < slot_accum - (0))
                {
                    return i;
                }
                
            }
        }
    }
    
    void stopAtNextIndex()
    {
        
       next_stop_index = (getIndexFromYpos()) % total_slot;
        next_stop_index += 1;
        
       printf("%i\n",next_stop_index);
        sndStop.play();

       stopnext = true;
        
    }
    
    void stop(bool _pause)
    {
        ispaused = _pause;
    }
    
    void nextIndex()
    {
        cur_index = cur_index + 1;
        cur_index = cur_index % total_slot;
        moveIndex(cur_index);
    }
    
    void draw(int x = 0 , int y = 0)
    {
        
        slotImg.draw(slotpos_x, slotpos_y, slot_width, slotImg.height);
        slotImg.draw(slotpos_x, slotpos_y + slotImg.height, slot_width, slotImg.height);
       // slotImgCover.draw(slotpos_x, 0);
        
        //ofDrawBitmapString( ofToString(slotpos_y) + " " + ofToString(getIndexFromYpos()), 400, 100);
    }
    bool finished;

private:
    float slot_width;
    float slot_height;
    int total_slot;
    ofImage slotImg;
    
    ofImage slotImgCover;
    
    float slotpos_x;
    float slotpos_y;
    int cur_index;
    int next_stop_index;
    int speed;
    bool ispaused;
    bool stopnext;
    
    ofSoundPlayer sndSpin;
    ofSoundPlayer sndStop;
    
};

#endif
