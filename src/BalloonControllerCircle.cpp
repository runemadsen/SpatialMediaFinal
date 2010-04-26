#include "BalloonControllerCircle.h"

/* Constructor
 ___________________________________________________________ */

BalloonControllerCircle::BalloonControllerCircle(Balloon * model) : BalloonController(model)
{
	
}

void BalloonControllerCircle::setColor(int color)
{
	_color = color;
}

/* Update
 ___________________________________________________________ */

void BalloonControllerCircle::update()
{
	
}

/* Draw
 ___________________________________________________________ */

void BalloonControllerCircle::draw()
{
	ofSetColor(_color);
	ofFill();
	ofEllipse(_model->getCenterX(), _model->getCenterY(), _model->getWidth(),_model->getHeight());
	ofNoFill();
	ofEllipse(_model->getCenterX(), _model->getCenterY(), _model->getWidth(), _model->getHeight());
}

/* Midi note on / off
 ___________________________________________________________ */

void BalloonControllerCircle::noteOn()
{
	
}

void BalloonControllerCircle::noteOff()
{
	
}