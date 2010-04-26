#pragma once

#include "Animation.h"
#include "BalloonControllerCircle.h"

class AnimationCircles : public Animation
{
public:
    
	AnimationCircles();
	
    void update();
	void draw();
	void newMidiMessage(ofxMidiEventArgs& eventArgs);
	
	BalloonController * getNewController(Balloon * model);
	
private:
	
	vector <int> _colors;
	
};


