#pragma once

#include "ofMain.h"

class Balloon
{
	
public:
	
	Balloon() { _scale = 1; }
	
	void setScale(float scale) { _scale = scale; }
	void setX(float x) { _loc.x = x; }
	void setY(float y) { _loc.y = y; }
	
	float getScale() { return _scale; }
	float getX() { return _loc.x; }
	float getY() { return _loc.y; }

private:
	
	ofPoint _loc;
	float _scale;
};