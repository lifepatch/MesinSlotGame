#ifndef OFXTIMING
#define OFXTIMING

#include "ofMain.h"

class ofxTiming
{
private:
    float start_timing;
    float timing_interval;
    bool timing_due;
    bool first_call;
public:
    bool enabled;


    ofxTiming()
    {
        first_call = true;
        timing_due = false;
        start_timing = 0;
        enabled = true;
    }

    void setup(float _interval)
    {
        //start_timing = ofGetElapsedTimef();
        timing_interval = _interval;
    }

    void setInterval (float _newInterval, bool _reSync = false)
    {
        timing_interval = _newInterval;
        if (_reSync) resync();
    }

    void reset()
    {
        first_call = true;
        timing_due = false;
        start_timing = 0;
        enabled = true;
    }
    
    void resync()
    {
        enabled = true;
        start_timing = ofGetElapsedTimef();
        timing_due = false;
    }

    float progress()
    {
        if (!enabled) return 0;
        return  (ofGetElapsedTimef() - start_timing)/timing_interval;
    }

    bool tick(bool _bOnce = false)
    {
        //if (!enabled) return false;
        //printf("tick: %f\n", ofGetElapsedTimef() - start_timing);
        if (first_call)
            {
                resync();
                first_call = false;
            }

        if (ofGetElapsedTimef() - start_timing > timing_interval)
            {
                start_timing = ofGetElapsedTimef();
                timing_due = true;
            }
        else
            {
                if (!_bOnce)
                    {
                        timing_due = false;
                    }
            }

        return timing_due;

    }

    bool isDue()
    {
        return timing_due;
    }

};

#endif // OFXTIMING

