#pragma once

#include "Animation.h"
#include "ofxMidi.h"
#include "BalloonController.h"
#include "Balloon.h"
#include "BalloonControllerLetter.h"

class AnimationLetters : public Animation
{
public:
    
	AnimationLetters();
	
    void update();
	void draw();
	BalloonController * getNewController(Balloon * model);
	
private:
	
	vector <string> _imgNames;
	
};


