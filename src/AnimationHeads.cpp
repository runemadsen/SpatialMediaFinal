#include "AnimationHeads.h"

/* Constructor
___________________________________________________________ */

AnimationHeads::AnimationHeads()
{
	orgImg.loadImage("head.png");
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
		bounds = _points[i]->getBoundsFromSize(orgImg.getWidth(), orgImg.getHeight());
		
		img.clone(orgImg);
		img.resize(bounds.width, bounds.height);
		img.draw(bounds.x, bounds.y);
	}
	
	ofDisableAlphaBlending();
}

