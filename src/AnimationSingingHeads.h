#pragma once

#include "Animation.h"
#include "ofxMidi.h"

class AnimationSingingHeads : public Animation
{
public:
    
	AnimationSingingHeads();
	
    void update();
	void draw();
	void newMidiMessage(ofxMidiEventArgs& eventArgs);
	
private:
	
	ofVideoPlayer head;
	
	int _headState; // 1 = blinking, 2 = opening, 3 = closing
	
	int _frameBlinkEnd;
	int _frameOpenEnd;
	int _frameCloseEnd;
};


