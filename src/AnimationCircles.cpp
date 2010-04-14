#include "AnimationCircles.h"

/* Constructor
 ___________________________________________________________ */

AnimationCircles::AnimationCircles()
{
	
}

/* Update
 ___________________________________________________________ */

void AnimationCircles::update()
{
	
}

/* Draw
 ___________________________________________________________ */

void AnimationCircles::draw()
{
	ofSetColor(255, 255, 0);
	
	ofSetCircleResolution(40);
	
	for(int i = 0; i < _points.size(); i++) 
	{
		ofFill();
		ofEllipse(_points[i]->getX(), _points[i]->getY(), 150 * _points[i]->getScale(), 250 * _points[i]->getScale());
		ofNoFill();
		ofEllipse(_points[i]->getX(), _points[i]->getY(), 150 * _points[i]->getScale(), 250 * _points[i]->getScale());
	}
}

