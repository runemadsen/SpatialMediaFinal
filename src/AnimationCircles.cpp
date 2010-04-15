#include "AnimationCircles.h"

/* Constructor
 ___________________________________________________________ */

AnimationCircles::AnimationCircles()
{
	_colors.push_back(0x7eff00);
	_colors.push_back(0xf000ff);
	_colors.push_back(0x8a00ff);
	_colors.push_back(0x1800ff);
	_colors.push_back(0x0072ff);
	_colors.push_back(0x00ccff);
	_colors.push_back(0x00ffae);
	_colors.push_back(0x00ff1e);
	_colors.push_back(0x7eff00);
	_colors.push_back(0xfffc00);
	_colors.push_back(0xff8400);
	_colors.push_back(0xff0000);
	_colors.push_back(0xf000ff);
	_colors.push_back(0xf000ff);
	_colors.push_back(0xf000ff);
	_colors.push_back(0xf000ff);
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
	ofSetCircleResolution(40);
	
	for(int i = 0; i < _points.size(); i++) 
	{
		ofSetColor(_colors[i]);
		ofFill();
		ofEllipse(_points[i]->getX(), _points[i]->getY(), _points[i]->getWidth(), _points[i]->getHeight());
		ofNoFill();
		ofEllipse(_points[i]->getX(), _points[i]->getY(), _points[i]->getWidth(), _points[i]->getHeight());
	}
}

