#include "BalloonControllerNanna.h"

/* Constructor
 ___________________________________________________________ */

BalloonControllerNanna::BalloonControllerNanna(Balloon * model) : BalloonController(model)
{
	_img.loadImage("head.png");
	
	timer.setDuration(20);
}

/* Update
 ___________________________________________________________ */

void BalloonControllerNanna::update()
{
	timer.tick();
}

/* Draw
 ___________________________________________________________ */

void BalloonControllerNanna::draw()
{
	ofFill();
	ofSetColor(0, 0, 0, 255);
	ofEllipse(_model->getCenterX(), _model->getCenterY(), _model->getWidth(), _model->getHeight());
	
	ofRectangle bounds = _model->getBoundsFromSize(_img.getWidth(), _img.getHeight());
	
	float alpha = Expo::easeOut(timer.getTime(), 0, 255, timer.getDuration());
	
	ofSetColor(255, 255, 255, alpha);
	
	_img.draw(bounds.x, bounds.y, bounds.width, bounds.height);
}

/* Midi note on / off
 ___________________________________________________________ */

void BalloonControllerNanna::noteOn()
{
	timer.setState(1);
}

void BalloonControllerNanna::noteOff()
{
	timer.setState(-1);
}