#include "AnimationSingingHeads.h"

/* Constructor
 ___________________________________________________________ */

AnimationSingingHeads::AnimationSingingHeads()
{
	_usingControllers = true;
}

/* Update
 ___________________________________________________________ */

void AnimationSingingHeads::update()
{	
	for(int i = 0; i < _controllers.size(); i++)
	{
		_controllers[i]->update();
	}
}

/* Draw
 ___________________________________________________________ */

void AnimationSingingHeads::draw()
{
	ofSetColor(255, 255, 255);
	
	for(int i = 0; i < _controllers.size(); i++)
	{ 
		_controllers[i]->draw();
	}
}

/* Overrides
 ___________________________________________________________ */

BalloonController * AnimationSingingHeads::getNewController(Balloon * model)
{		
	BalloonControllerHead * b = new BalloonControllerHead(model);
	return b;
}



