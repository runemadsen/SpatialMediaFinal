#pragma once

#include "Animation.h"
#include "ofxMidi.h"
#include "BalloonController.h"
#include "Balloon.h"
#include "BalloonControllerHead.h"

class AnimationSingingHeads : public Animation
{
public:
    
	AnimationSingingHeads();
	
    void update();
	void draw();
	BalloonController * getNewController(Balloon * model);
	
private:

};


