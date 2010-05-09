#pragma once

#include "Animation.h"
#include "ofxMidi.h"
#include "BalloonController.h"
#include "Balloon.h"
#include "BalloonControllerDog.h"

class AnimationDogs : public Animation
{
public:
    
	AnimationDogs();
	
    void update();
	void draw();
	BalloonController * getNewController(Balloon * model);
	
private:
	
	vector <string> _imgNames;
};


