#pragma once

#include "ofMain.h"

class Point
{
	
public:
	
	Point();
	
	void setScale(float scale) { _scale = scale }
	void setX(float x) { _loc.x = x }
	void setY(float y) { _loc.y = y }
	
	float getScale() { return _scale }
	float getX() { return _loc.x }
	float getY() { return _loc.y }

private:
	
	ofPoint _loc;
	float _scale;
};