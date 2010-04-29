#include "AnimationNew.h"

/* Constructor
 ___________________________________________________________ */

AnimationNew::AnimationNew()
{
	_usingControllers = true;
}

/* Update
 ___________________________________________________________ */

void AnimationNew::update()
{	
	// update every balloon
	for(int i = 0; i < _controllers.size(); i++)
	{
		_controllers[i]->update();
	}
}

/* Draw
 ___________________________________________________________ */

void AnimationNew::draw()
{
	// draw every balloon
	for(int i = 0; i < _controllers.size(); i++)
	{ 
		_controllers[i]->draw();
	}
}

/* Overrides
 ___________________________________________________________ */

BalloonController * AnimationNew::getNewController(Balloon * model)
{		
	// this method gets called every time you click to create a new balloon
	// it returns a new ballooncontroller class specific for this AnimationNew class: a BalloonControllerNew object
	
	BalloonControllerNew * b = new BalloonControllerNew(model);
	
	return b;
}



