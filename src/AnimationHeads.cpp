#include "AnimationHeads.h"

/* Constructor
___________________________________________________________ */

AnimationHeads::AnimationHeads()
{
	img.loadImage("head.png");
}

/* Update
 ___________________________________________________________ */

void AnimationHeads::update()
{
	
}

/* Draw
___________________________________________________________ */

void AnimationHeads::draw()
{
	ofSetColor(255, 255, 255);
	
	ofRectangle bounds;
	
	for(int i = 0; i < _points.size(); i++) 
	{
		ofFill();
		ofSetColor(0, 0, 0, 255);
		ofEllipse(_points[i]->getCenterX(), _points[i]->getCenterY(), _points[i]->getWidth(), _points[i]->getHeight());
		
		ofSetColor(255, 255, 255);
		
		ofEnableAlphaBlending();
		
		bounds = _points[i]->getBoundsFromSize(img.getWidth(), img.getHeight());
		
		img.draw(bounds.x, bounds.y, bounds.width, bounds.height);
		
		ofDisableAlphaBlending();
	}
	
	
}