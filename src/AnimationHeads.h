#pragma once

#include "Animation.h"
#include "ofxMidi.h"
#include "BalloonController.h"
#include "Balloon.h"
#include "BalloonControllerNanna.h"

class AnimationHeads : public Animation
{
public:
    
	AnimationHeads();
	
    void update();
	void draw();
	BalloonController * getNewController(Balloon * model);
	
private:

};


