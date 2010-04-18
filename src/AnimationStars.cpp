#include "AnimationStars.h"

/* Constructor
 ___________________________________________________________ */

AnimationStars::AnimationStars()
{
	_usingControllers = true;
}

/* Update
 ___________________________________________________________ */

void AnimationStars::update()
{
	for(int i = 0; i < _controllers.size(); i++)
	{
		//BalloonControllerStars * c = (BalloonControllerStars *) _controllers[i];
		//c->update();
		
		_controllers[i]->update();
	}
}

/* Draw
 ___________________________________________________________ */

void AnimationStars::draw()
{
	for(int i = 0; i < _controllers.size(); i++)
	{
		//BalloonControllerStars * c = (BalloonControllerStars *) _controllers[i];
		//c->draw();
		
		_controllers[i]->draw();
	}
}

/* Overrides
 ___________________________________________________________ */

BalloonController * AnimationStars::getNewController(Balloon * model)
{		
	return new BalloonControllerStars(model);
}