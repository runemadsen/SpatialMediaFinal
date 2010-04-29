#include "BalloonControllerLetter.h"

/* Constructor
 ___________________________________________________________ */

BalloonControllerLetter::BalloonControllerLetter(Balloon * model) : BalloonController(model)
{
	timer.setDuration(50);
}

void BalloonControllerLetter::loadImage(string imgPath, string imgPath2)
{
	_img.loadImage(imgPath);
	_img2.loadImage(imgPath2);
}

/* Update
 ___________________________________________________________ */

void BalloonControllerLetter::update()
{
	timer.tick();
}

/* Draw
 ___________________________________________________________ */

void BalloonControllerLetter::draw()
{
	ofFill();
	ofSetColor(0, 0, 0, 255);
	ofEllipse(_model->getCenterX(), _model->getCenterY(), _model->getWidth(), _model->getHeight());
	
	ofSetColor(255, 255, 255, 255);
	
	ofRectangle bounds = _model->getBoundsFromSize(_img.getWidth(), _img.getHeight());
	
	_img.draw(bounds.x, bounds.y, bounds.width, bounds.height);
	
	float alpha = Expo::easeOut(timer.getTime(), 0, 255, timer.getDuration());
	
	ofSetColor(255, 255, 255, alpha);
	
	_img2.draw(bounds.x, bounds.y, bounds.width, bounds.height);
}

/* Midi note on / off
 ___________________________________________________________ */

void BalloonControllerLetter::noteOn()
{
	timer.setState(1);
}

void BalloonControllerLetter::noteOff()
{
	timer.setState(-1);
}