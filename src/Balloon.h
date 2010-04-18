#pragma once

#include "ofMain.h"

class Balloon
{
	
public:
	
	Balloon() 
	{ 
		_bounds.width = 200;
		_bounds.height = 250;
		
		_scaleWidth = 1; 
		_scaleHeight = 1; 
	}
	
	void setX(float x) { _bounds.x = x; }
	void setY(float y) { _bounds.y = y; }
	
	void setScaleWidth(float scale) 
	{ 
		_scaleWidth = scale; 
	}
	
	void setScaleHeight(float scale) { _scaleHeight = scale; }
		
	float getX() { return _bounds.x; }
	float getY() { return _bounds.y; }
	float getWidth() { return _bounds.width * _scaleWidth; }
	float getHeight() { return _bounds.height * _scaleHeight; }
	float getScaleWidth() { return _scaleWidth; }
	float getScaleHeight() { return _scaleHeight; }
	
	ofRectangle getBoundsFromSize(float width, float height)
	{
		ofRectangle bounds;
		
		float wDiff = getWidth() / width;
		float hDiff = getHeight() / height;
		
		if(wDiff < hDiff)
		{
			bounds.width = width * wDiff;
			bounds.height = height * wDiff;
		}
		else 
		{
			bounds.width = width * hDiff;
			bounds.height = height * hDiff;
		}
		
		bounds.x = _bounds.x - (bounds.width / 2);
		bounds.y = _bounds.y - (bounds.height / 2);
		
		return bounds;
	}

private:
	
	ofRectangle _bounds;
	float _scaleWidth;
	float _scaleHeight;
};