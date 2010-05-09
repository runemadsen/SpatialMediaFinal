#pragma once

#include "Animation.h"
#include "ofxMidi.h"
#include "BalloonController.h"
#include "Balloon.h"
#include "BalloonControllerNew.h"

class AnimationNew : public Animation
{
public:
    
	AnimationNew();
	
    void update();
	void draw();
	
	BalloonController * getNewController(Balloon * model);
	
private:
	
};


