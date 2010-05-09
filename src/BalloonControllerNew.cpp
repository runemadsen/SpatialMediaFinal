#include "BalloonControllerNew.h"

/* Constructor
 ___________________________________________________________ */

BalloonControllerNew::BalloonControllerNew(Balloon * model) : BalloonController(model)
{
	int ranNum = ofRandom(1, 4);
	string imgName = "jorge" + ofToString(ranNum) + ".png";

	img.loadImage(imgName);
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
	ofRectangle bounds;
	
	ofFill();
	ofSetColor(0, 0, 0, 255);
	ofEllipse(_model->getCenterX(), _model->getCenterY(), _model->getWidth(), _model->getHeight());
	
	ofSetColor(255, 255, 255);
	
	ofEnableAlphaBlending();
	
	bounds = _model->getBoundsFromSize(img.getWidth(), img.getHeight());
	
	img.draw(bounds.x, bounds.y, bounds.width, bounds.height);
	
	ofDisableAlphaBlending();
}

/* Midi note on / off
 ___________________________________________________________ */

void BalloonControllerNew::noteOn()
{
	
}

void BalloonControllerNew::noteOff()
{

}