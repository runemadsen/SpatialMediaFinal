#include "BalloonControllerLetter.h"

/* Constructor
 ___________________________________________________________ */

BalloonControllerLetter::BalloonControllerLetter(Balloon * model) : BalloonController(model)
{
	
}

void BalloonControllerLetter::loadImage(string imgPath)
{
	_img.loadImage(imgPath);
}

/* Update
 ___________________________________________________________ */

void BalloonControllerLetter::update()
{
	
}

/* Draw
 ___________________________________________________________ */

void BalloonControllerLetter::draw()
{
	ofRectangle bounds = _model->getBoundsFromSize(_img.getWidth(), _img.getHeight());
	
	_img.draw(bounds.x, bounds.y, bounds.width, bounds.height);
}

/* Midi note on / off
 ___________________________________________________________ */

void BalloonControllerLetter::noteOn()
{

}

void BalloonControllerLetter::noteOff()
{
	
}