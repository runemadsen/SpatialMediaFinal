#include "BalloonControllerNew.h"

/* Constructor
 ___________________________________________________________ */

BalloonControllerNew::BalloonControllerNew(Balloon * model) : BalloonController(model)
{
	_color = 0xFFFFFF;
}

/* Update
 ___________________________________________________________ */

void BalloonControllerNew::update()
{
	
}

/* Draw
 ___________________________________________________________ */

void BalloonControllerNew::draw()
{
	// color is either white or red depending on note played
	ofSetColor(_color);
	ofFill();
	
	// get the position and size of this ballon from the _model: a Balloon object created when you clicked
	ofEllipse(_model->getCenterX(), _model->getCenterY(), _model->getWidth(), _model->getHeight());
}

/* Midi note on / off
 ___________________________________________________________ */

void BalloonControllerNew::noteOn()
{
	_color = 0xFF0000;
}

void BalloonControllerNew::noteOff()
{
	_color = 0xFFFFFF;
}