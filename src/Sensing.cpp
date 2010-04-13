#include "Sensing.h"

/* Constructor
 ___________________________________________________________ */

Sensing::Sensing()
{
	_enabled = true;
	_mapFromScreen = false;
	_scalePosAll = 1;
	_xDisplaceAll = 0;
	_yDisplaceAll = 0;
	_scaleSizeAll = 1;
	_scaleSizeSelected = 1;
	_selectedBalloon = DISABLED;
	
	_camera.initGrabber(VIDEO_WIDTH, VIDEO_HEIGHT);
	
	gui.addTitle("Video");
	gui.addFPSCounter();
	
	gui.addPage("Control Page");
	gui.addTitle("All Balloons");
	gui.addSlider("X", _xDisplaceAll, 0, ofGetWidth());
	gui.addSlider("Y", _yDisplaceAll, 0, ofGetHeight());
	gui.addSlider("Scale Positions", _scalePosAll, 0.8, 4.0);
	gui.addSlider("Scale Sizes", _scaleSizeAll, 0.1, 4);
	
	gui.addTitle("Selected Balloons");
	
	gui.addSlider("Scale Size", _scaleSizeSelected, 0.1, 4);
	
	//gui.loadFromXML();
	
	gui.show();
}

/* Update
 ___________________________________________________________ */

void Sensing::update()
{
	_camera.grabFrame();
	
	if(_selectedBalloon != DISABLED)
	{
		_balloons[_selectedBalloon]->setScale( _scaleSizeSelected );
	}
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
		
		for (int i = 0; i < _balloons.size(); i++) 
		{
			if(i == _selectedBalloon)	
			{
				drawBalloon(_balloons[i]->getX(), _balloons[i]->getY(), 0x000FF00);
			}
			else
			{
				drawBalloon(_balloons[i]->getX(), _balloons[i]->getY(), 0xFF0000);
			}
		}
	}
	else if(!disableAnimation() && _mapFromScreen)
	{
		vector <Balloon *> balloons = getBalloons();
		
		ofSetColor(0, 255, 0);
		
		for(int i = 0; i < balloons.size(); i++)
		{
			if(i == _selectedBalloon)	
			{
				drawBalloon(balloons[i]->getX(), balloons[i]->getY(), 0x000FF00);
			}
			else
			{
				drawBalloon(balloons[i]->getX(), balloons[i]->getY(), 0xFF0000);
			}
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
	else if(!_enabled && _mapFromScreen)
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
	int index = isClickWithinBalloon(xPos, yPos);
	
	if(index == DISABLED)
	{
		if (_selectedBalloon == DISABLED) 
		{
			Balloon * newBalloon = new Balloon();
			newBalloon->setX(xPos);
			newBalloon->setY(yPos);
			
			_balloons.push_back(newBalloon);
		}
		else 
		{
			_selectedBalloon = DISABLED;
		}
	}
	else 
	{
		_selectedBalloon = index;
		
		setBalloonDataToGUI();
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
		   
int Sensing::isClickWithinBalloon(int xPos, int yPos)
{	
	for(int i = 0; i < _balloons.size(); i++)
	{
		if(fabs(xPos - _balloons[i]->getX()) < POINT_MARGIN && fabs(yPos - _balloons[i]->getY()) < POINT_MARGIN)
		{
			return i;
		}
	}
	
	return DISABLED;
}

void Sensing::drawBalloon(int xPos, int yPos, int color)
{
	ofSetColor(color);
	
	ofFill();
	ofCircle(xPos, yPos, 3);
	
	ofNoFill();
	ofCircle(xPos, yPos, 3);
	ofCircle(xPos, yPos, 8);
}

void Sensing::setBalloonDataToGUI()
{
	_scaleSizeSelected = _balloons[_selectedBalloon]->getScale();
}

void Sensing::deleteSelectedBalloon()
{
	if(_selectedBalloon != DISABLED)
	{
		_balloons.erase(_balloons.begin() + _selectedBalloon);
		_selectedBalloon = DISABLED;
	}
}

/* Key press
 ___________________________________________________________ */

void Sensing::keyPressed(int key)
{	
	// delete
	if(key == 127)
	{
		deleteSelectedBalloon();
	}
	// right arrow
	else if (key == 358) 
	{
		nextPage();
	}
	// left arrow
	else if (key == 356) 
	{
		prevPage();
	}
	else if (key == 'S') 
	{
		_scalePosAll += 0.005;
	}
	else if (key == 's') 
	{
		_scalePosAll -= 0.005;
	}
	else if (key == 'X') 
	{
		_xDisplaceAll++;
	}
	else if (key == 'x') 
	{
		_xDisplaceAll--;
	}
	else if (key == 'Y') 
	{
		_yDisplaceAll++;
	}
	else if (key == 'y') 
	{
		_yDisplaceAll--;
	}
	else if (key == 'P') 
	{
		_scaleSizeAll += 0.005;
	}
	else if (key == 'p') 
	{
		_scaleSizeAll -= 0.005;
	}
	else if (key == 'l') 
	{
		loadBalloons();
	}
	else if (key == 'L') 
	{
		saveBalloons();
	}
	else if (key ==' ') 
	{
		toggleEnabled();
	}
	else if (key == 'm') 
	{
		toggleMapFromScreen();
	}
}

/* Loading / Saving
 ___________________________________________________________ */

void Sensing::loadBalloons()
{
	if(_xml.loadFile(XML_FILE))
	{
		if(_xml.pushTag("points", 0))
		{
			for(int i = 0; i < _xml.getNumTags("point"); i++) 
			{
				Balloon * point = new Balloon();
				point->setX( (float) _xml.getAttribute("point", "x", 0, i) );
				point->setY( (float) _xml.getAttribute("point", "y", 0, i) );
				point->setScale( (float) _xml.getAttribute("point", "scale", 0, i) );
				_balloons.push_back(point);
			}
			
			_xml.popTag();
		}
	}
}

void Sensing::saveBalloons()
{	
	//_xml.loadFromBuffer("<root></root>");
	
	_xml.clear();
	
	_xml.addTag("points");
	_xml.pushTag("points", 0);
	
	for(int i = 0; i < _balloons.size(); i++)
	{
		_xml.addTag("point");
		_xml.addAttribute("point", "x", ofToString(_balloons[i]->getX(), 1), i);
		_xml.addAttribute("point", "y", ofToString(_balloons[i]->getY(), 1), i);
		_xml.addAttribute("point", "scale", ofToString(_balloons[i]->getScale(), 2), i);
	}
	
	_xml.popTag();
	
	_xml.saveFile(XML_FILE);
	
}

/* Getters / Setters
___________________________________________________________ */

vector <Balloon *> Sensing::getBalloons()
{
	vector <Balloon *> norm;
	norm.clear();
	
	float scaleToScreenX = ofGetWidth() / (VIDEO_WIDTH * VIDEO_SCALE);
	float scaleToScreenY = ofGetHeight() / (VIDEO_HEIGHT * VIDEO_SCALE);
	
	for(int i = 0; i < _balloons.size(); i++)
	{
		Balloon * newPoint = new Balloon();
		newPoint->setX( (_balloons[i]->getX() - VIDEO_X + _xDisplaceAll) * (scaleToScreenX * _scalePosAll) );
		newPoint->setY( (_balloons[i]->getY() - VIDEO_Y + _yDisplaceAll) * (scaleToScreenY * _scalePosAll) );
		newPoint->setScale( _balloons[i]->getScale() * _scaleSizeAll );
		
		norm.push_back(newPoint);
	}
	
	return norm;
}

vector <Balloon *> Sensing::getBalloonsSorted()
{
	vector <Balloon *> norm = getBalloons();
	
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