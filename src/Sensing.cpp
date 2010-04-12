#include "Sensing.h"

/* Constructor
 ___________________________________________________________ */

Sensing::Sensing()
{
	_enabled = true;
	_mapFromScreen = false;
	_scale = 1;
	_xDisplace = 0;
	_yDisplace = 0;
	_pointScale = 1;
	
	_camera.initGrabber(VIDEO_WIDTH, VIDEO_HEIGHT);
	
	gui.addTitle("Video");
	gui.addFPSCounter();
	
	gui.addPage("Control Page");
	gui.addTitle("Controls");
	gui.addSlider("X", _xDisplace, -2000.0, 2000.0);
	gui.addSlider("Y", _yDisplace, -2000.0, 2000.0);
	gui.addSlider("Scale", _scale, 0.8, 4.0);
	gui.addSlider("Point Scale", _pointScale, 0.1, 4);
	
	//gui.loadFromXML();
	
	gui.show();
}

/* Update
 ___________________________________________________________ */

void Sensing::update()
{
	_camera.grabFrame();
}

/* Draw
 ___________________________________________________________ */

void Sensing::draw()
{	
	gui.draw();
	
	if(_enabled && gui.currentPage == 1)
	{
		ofSetColor(255, 255, 255);
		
		_camera.draw(VIDEO_X, VIDEO_Y, _camera.getWidth() * VIDEO_SCALE, _camera.getHeight() * VIDEO_SCALE);
		
		for (int i = 0; i < _points.size(); i++) 
		{
			drawPoint(_points[i]->x, _points[i]->y, 0x00FF00);
		}
	}
	else if(!disableAnimation() && _mapFromScreen)
	{
		vector <ofPoint *> points = getPointsSorted();
		
		ofSetColor(0, 255, 0);
		
		for(int i = 0; i < points.size(); i++)
		{
			drawPoint(points[i]->x, points[i]->y, 0xFF0000);
		}	
	}
}

/* Mouse
___________________________________________________________ */

void Sensing::mousePressed(int xPos, int yPos, int button)
{
	if(_enabled && gui.currentPage == 1)
	{
		if(isClickWithinVideo(xPos, yPos))
	    {
			checkClick(xPos, yPos);
	    }
	}
	else if(!disableAnimation() && _mapFromScreen)
	{
		// map points from screen coordinates to video coordinates
		float scaleToVideoX = (VIDEO_WIDTH * VIDEO_SCALE) / ofGetWidth();
		float scaleToVideoY = (VIDEO_HEIGHT * VIDEO_SCALE) / ofGetHeight();
		
		float xMapped = (xPos * scaleToVideoX) + VIDEO_X;
		float yMapped = (yPos * scaleToVideoY) + VIDEO_Y;
		
		checkClick(xMapped, yMapped);
	}
}

void Sensing::checkClick(int xPos, int yPos)
{
	int index = isClickWithinPoint(xPos, yPos);
	
	if(index == DISABLED)
	{
		ofPoint * newPoint = new ofPoint();
		newPoint->set(xPos, yPos);
		
		_points.push_back(newPoint);
	}
	else 
	{
		_points.erase(_points.begin() + index);
	}
}

/* Utilities
___________________________________________________________ */

bool Sensing::isClickWithinVideo(int xPos, int yPos)
{
	if(xPos > VIDEO_X && xPos < VIDEO_X + (_camera.getWidth() * VIDEO_SCALE) && yPos > VIDEO_Y && yPos < VIDEO_Y + (_camera.getHeight() * VIDEO_SCALE))
	{
		return true;
	}
	
	return false;
}
		   
int Sensing::isClickWithinPoint(int xPos, int yPos)
{	
	for(int i = 0; i < _points.size(); i++)
	{
		if(fabs(xPos - _points[i]->x) < POINT_MARGIN && fabs(yPos - _points[i]->y) < POINT_MARGIN)
		{
			return i;
		}
	}
	
	return DISABLED;
}

void Sensing::drawPoint(int xPos, int yPos, int color)
{
	ofSetColor(color);
	
	ofFill();
	ofCircle(xPos, yPos, 3);
	
	ofNoFill();
	ofCircle(xPos, yPos, 3);
	ofCircle(xPos, yPos, 8);
}

/* Loading
 ___________________________________________________________ */

void Sensing::loadPoints()
{
	if(_xml.loadFile(XML_FILE))
	{
		if(_xml.pushTag("points", 0))
		{
			for(int i = 0; i < _xml.getNumTags("point"); i++) 
			{
				ofPoint * point = new ofPoint();
				point->x = (float) _xml.getAttribute("point", "x", 0, i);
				point->y = (float) _xml.getAttribute("point", "y", 0, i);
				_points.push_back(point);
			}
			
			_xml.popTag();
		}
	}
}

void Sensing::savePoints()
{	
	//_xml.loadFromBuffer("<root></root>");
	
	_xml.clear();
	
	_xml.addTag("points");
	_xml.pushTag("points", 0);
	
	for(int i = 0; i < _points.size(); i++)
	{
		_xml.addTag("point");
		_xml.addAttribute("point", "x", ofToString(_points[i]->x, 1), i);
		_xml.addAttribute("point", "y", ofToString(_points[i]->y, 1), i);
	}
	
	_xml.popTag();
	
	_xml.saveFile(XML_FILE);

}

/* Getters / Setters
___________________________________________________________ */

void Sensing::displace(string method, string value)
{
	printf("subtract");
	
	if(value == DISPLACE_X)
	{
		if(method == ADD)		_xDisplace++;
		else if(method == SUB)	_xDisplace--;
	}
	else if(value == DISPLACE_Y)
	{
		if(method == ADD)		_yDisplace++;
		else if(method == SUB)	_yDisplace--;
	}
	else if(value == DISPLACE_SCALE)
	{
		if(method == ADD)		_scale += 0.005;
		else if(method == SUB)	_scale -= 0.005;
	}
	else if(value == DISPLACE_RADIUS)
	{
		if(method == ADD)		_pointScale += 0.005;
		else if(method == SUB)	_pointScale += 0.005;
	}
	else 
	{
		printf("ERROR: Wrong displace command \n");
	}
}

vector <ofPoint *> Sensing::getPoints()
{
	vector <ofPoint *> norm;
	norm.clear();
	
	float scaleToScreenX = ofGetWidth() / (VIDEO_WIDTH * VIDEO_SCALE);
	float scaleToScreenY = ofGetHeight() / (VIDEO_HEIGHT * VIDEO_SCALE);
	
	for(int i = 0; i < _points.size(); i++)
	{
		ofPoint * newPoint = new ofPoint();
		newPoint->x = (_points[i]->x - VIDEO_X + _xDisplace) * (scaleToScreenX * _scale);
		newPoint->y = (_points[i]->y - VIDEO_Y + _yDisplace) * (scaleToScreenY * _scale);
		
		norm.push_back(newPoint);
	}
	
	return norm;
}

vector <ofPoint *> Sensing::getPointsSorted()
{
	vector <ofPoint *> norm = getPoints();
	
	//std::sort(norm.begin(), norm.end(), Sensing::xsorter());
	std::sort(norm.begin(), norm.end(), Sensing::ysorter());
	
	return norm;
}

void Sensing::toggleEnabled()
{
	_enabled = !_enabled;
	
	gui.toggleDraw();
}

bool Sensing::getEnabled()
{
	return _enabled;
}

void Sensing::nextPage()
{
	gui.nextPage(); 
}

void Sensing::prevPage()
{
	gui.prevPage(); 
}

int Sensing::getPage()
{
	return gui.currentPage;
}

float Sensing::getPointScale()
{
	return _pointScale;
}

void Sensing::toggleMapFromScreen()
{
	_mapFromScreen = !_mapFromScreen;
}

bool Sensing::disableAnimation()
{
	if(getPage() == 1 && getEnabled())
	{
		return true;
	}
	
	return false;
}