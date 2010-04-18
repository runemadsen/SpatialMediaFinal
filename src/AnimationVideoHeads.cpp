#include "AnimationVideoHeads.h"

/* Constructor
 ___________________________________________________________ */

AnimationVideoHeads::AnimationVideoHeads()
{
	head.loadMovie("head.mov");
	head.play();
}

/* Update
 ___________________________________________________________ */

void AnimationVideoHeads::update()
{
	head.idleMovie();
}

/* Draw
 ___________________________________________________________ */

void AnimationVideoHeads::draw()
{
	ofSetColor(255, 255, 255);
	
	ofRectangle bounds;
	
	for(int i = 0; i < _points.size(); i++) 
	{
		bounds = _points[i]->getBoundsFromSize(head.getWidth(), head.getHeight());
		
		head.draw(bounds.x, bounds.y, bounds.width, bounds.height);
	}
}

