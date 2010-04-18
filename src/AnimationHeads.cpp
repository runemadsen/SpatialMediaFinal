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
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255);
	
	ofRectangle bounds;
	
	for(int i = 0; i < _points.size(); i++) 
	{
		bounds = _points[i]->getBoundsFromSize(img.getWidth(), img.getHeight());
		
		img.draw(bounds.x, bounds.y, bounds.width, bounds.height);
	}
	
	ofDisableAlphaBlending();
}