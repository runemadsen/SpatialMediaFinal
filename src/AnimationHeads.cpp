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
	//if(newPointScale())
	//{		
		//img.clone(orgImg);
		
	//img.resize(orgImg.getWidth() * _pointScale, orgImg.getHeight() * _pointScale);
	//}
}

/* Draw
___________________________________________________________ */

void AnimationHeads::draw()
{
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255);
	
	for(int i = 0; i < _points.size(); i++) 
	{
		img.clone(orgImg);
		img.resize(orgImg.getWidth() * _points[i]->getScale(), orgImg.getHeight() * _points[i]->getScale());
		img.draw(_points[i]->getX() - (img.getWidth() / 2), _points[i]->getY() - (img.getHeight() / 2));
	}
	
	ofDisableAlphaBlending();
}

