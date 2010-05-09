#include "BalloonControllerDog.h"

/* Constructor
 ___________________________________________________________ */

BalloonControllerDog::BalloonControllerDog(Balloon * model) : BalloonController(model)
{
	timer.setDuration(20);
}

void BalloonControllerDog::loadImage(string imgPath)
{
	_img.loadImage(imgPath);
}

/* Update
 ___________________________________________________________ */

void BalloonControllerDog::update()
{
	timer.tick();
}

/* Draw
 ___________________________________________________________ */

void BalloonControllerDog::draw()
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

void BalloonControllerDog::noteOn()
{
	timer.setState(1);
}

void BalloonControllerDog::noteOff()
{
	timer.setState(-1);
}