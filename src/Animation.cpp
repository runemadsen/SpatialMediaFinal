#include "Animation.h"

/* Constructor
___________________________________________________________ */

Animation::Animation()
{
	_pointScale = 1;
}

/* Getter / Setter
___________________________________________________________ */

void Animation::setPoints(vector <ofPoint *> points)
{
	_points = points;
}

void Animation::setPointScale(float pointScale)
{
	_oldPointScale = _pointScale;
	
	_pointScale = pointScale;
}

bool Animation::newPointScale()
{
	return _oldPointScale != _pointScale;
}

