//
//  ofxOnce.h
//  mesinslotcoba
//
//  Created by xcorex on 6/18/15.
//
//

#ifndef mesinslotcoba_ofxOnce_h
#define mesinslotcoba_ofxOnce_h

class ofxOnce
{
public:
    
    ofxOnce()
    {
        enable = true;
    }
    
    void reset()
    {
        enable = true;
    }
    
    bool once()
    {
        
        if (enable)
        {
            enable = false;
            return true;
        }else{
            return false;
        }


    }
private:
    bool enable;
};

#endif
