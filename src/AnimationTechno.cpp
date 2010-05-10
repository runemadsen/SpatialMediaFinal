#include "AnimationTechno.h"

/* Constructor
 ___________________________________________________________ */

AnimationTechno::AnimationTechno()
{
	_usingControllers = true;
}

/* Update
 ___________________________________________________________ */

void AnimationTechno::update()
{	
	for(int i = 0; i < _controllers.size(); i++)
	{
		_controllers[i]->update();
	}
}

/* Draw
 ___________________________________________________________ */

void AnimationTechno::draw()
{
	for(int i = 0; i < _controllers.size(); i++)
	{
		_controllers[i]->draw();
	}
}

/* Overrides
 ___________________________________________________________ */

BalloonController * AnimationTechno::getNewController(Balloon * model)
{		
	BalloonControllerTechno * b = new BalloonControllerTechno(model);
	
	b->setStartNum(_controllers.size() * 20);
	
	return b;
}



