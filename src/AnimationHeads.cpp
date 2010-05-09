#include "AnimationHeads.h"

/* Constructor
 ___________________________________________________________ */

AnimationHeads::AnimationHeads()
{
	_usingControllers = true;
}

/* Update
 ___________________________________________________________ */

void AnimationHeads::update()
{	
	for(int i = 0; i < _controllers.size(); i++)
	{
		_controllers[i]->update();
	}
}

/* Draw
 ___________________________________________________________ */

void AnimationHeads::draw()
{
	ofSetColor(255, 255, 255);
	
	ofEnableAlphaBlending();
	
	for(int i = 0; i < _controllers.size(); i++)
	{ 
		_controllers[i]->draw();
	}
	
	ofDisableAlphaBlending();
}

/* Overrides
 ___________________________________________________________ */

BalloonController * AnimationHeads::getNewController(Balloon * model)
{		
	BalloonControllerNanna * b = new BalloonControllerNanna(model);
	
	return b;
}



