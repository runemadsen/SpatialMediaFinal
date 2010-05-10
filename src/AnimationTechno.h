#pragma once

#include "Animation.h"
#include "ofxMidi.h"
#include "BalloonController.h"
#include "Balloon.h"
#include "BalloonControllerTechno.h"

class AnimationTechno : public Animation
{
public:
    
	AnimationTechno();
	
    void update();
	void draw();
	BalloonController * getNewController(Balloon * model);
	
private:

};


