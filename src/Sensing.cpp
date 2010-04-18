#include "Sensing.h"

/* Constructor
 ___________________________________________________________ */

Sensing::Sensing()
{
	_enabled = false;
	_mapFromScreen = false;
	_scalePosAll = 1;
	_xDisplaceAll = 0;
	_yDisplaceAll = 0;
	_scaleSizeAll = 1;
	_constrainRatio = true;
	_scaleWidthSelected = 1;
	_scaleHeightSelected = 1;
	_oldScaleWidthSelected = 1;
	_oldScaleHeightSelected = 1;
	_selectedBalloon = DISABLED;
	
	_camera.initGrabber(VIDEO_WIDTH, VIDEO_HEIGHT);
	
	gui.addTitle("Video");
	gui.addFPSCounter();
	
	gui.addPage("Control Page");
	gui.addTitle("All Balloons");
	gui.addSlider("X", _xDisplaceAll, -1000, 1000);
	gui.addSlider("Y", _yDisplaceAll, -1000, 1000);
	gui.addSlider("Scale Positions", _scalePosAll, 0.8, 4.0);
	gui.addSlider("Scale Sizes", _scaleSizeAll, 0.1, 4);
	
	gui.addTitle("Selected Balloons");
	
	gui.addSlider("Scale Width", _scaleWidthSelected, 0.1, 4);
	gui.addSlider("Scale Height", _scaleHeightSelected, 0.1, 4);
	gui.addToggle("Constrain Ratio", _constrainRatio);
	
	//gui.loadFromXML();
	
	//gui.show();
}

/* Update
 ___________________________________________________________ */

void Sensing::update()
{
	if(_constrainRatio)
	{
		// if both are edited on the same frame, this fucks up, shouldn't be possible
		float diffWidth = _oldScaleWidthSelected - _scaleWidthSelected;
		float diffHeight = _oldScaleHeightSelected - _scaleHeightSelected;
		_scaleHeightSelected -= diffWidth;
		_scaleWidthSelected -= diffHeight;
	}
	
	_camera.grabFrame();
	
	_oldScaleWidthSelected = _scaleWidthSelected;
	_oldScaleHeightSelected = _scaleHeightSelected;
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
				drawBalloon(mapScreenXToVideoX(_balloons[i]->getX()), mapScreenYToVideoY(_balloons[i]->getY()), 0x000FF00);
			}
			else
			{
				drawBalloon(mapScreenXToVideoX(_balloons[i]->getX()), mapScreenYToVideoY(_balloons[i]->getY()), 0xFF0000);
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
			xPos = mapVideoXToScreenX(xPos);
			yPos = mapVideoYToScreenY(yPos);
			
			checkClick(xPos, yPos);
	    }
	}
	else if(!_enabled && _mapFromScreen)
	{
		checkClick((xPos / _scalePosAll) - _xDisplaceAll, (yPos / _scalePosAll) - _yDisplaceAll);
	}
}

void Sensing::checkClick(float xPos, float yPos)
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

void Sensing::setBalloonDataToGUI()
{
	_scaleWidthSelected = _balloons[_selectedBalloon]->getScaleWidth();
	_scaleHeightSelected = _balloons[_selectedBalloon]->getScaleHeight();
	
	_oldScaleWidthSelected = _scaleWidthSelected;
	_oldScaleHeightSelected = _scaleHeightSelected;
}

/* Utilities
___________________________________________________________ */

bool Sensing::isClickWithinVideo(float xPos, float yPos)
{
	if(xPos > VIDEO_X && xPos < VIDEO_X + (_camera.getWidth() * VIDEO_SCALE) && yPos > VIDEO_Y && yPos < VIDEO_Y + (_camera.getHeight() * VIDEO_SCALE))
	{
		return true;
	}
	
	return false;
}
		   
int Sensing::isClickWithinBalloon(float xPos, float yPos)
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

void Sensing::drawBalloon(float xPos, float yPos, int color)
{
	ofSetColor(color);
	
	ofFill();
	ofCircle(xPos, yPos, 3);
	
	ofNoFill();
	ofCircle(xPos, yPos, 3);
	ofCircle(xPos, yPos, 8);
}

void Sensing::deleteSelectedBalloon()
{
	if(_selectedBalloon != DISABLED)
	{
		_balloons.erase(_balloons.begin() + _selectedBalloon);
		_selectedBalloon = DISABLED;
	}
}

float Sensing::mapScreenXToVideoX(float xPos)
{
	return xPos * ( (VIDEO_WIDTH * VIDEO_SCALE) / ofGetWidth()) + VIDEO_X;
}

float Sensing::mapScreenYToVideoY(float yPos)
{
	return yPos * ( (VIDEO_HEIGHT * VIDEO_SCALE) / ofGetHeight()) + VIDEO_Y;
}

float Sensing::mapVideoXToScreenX(float xPos)
{
	return (xPos - VIDEO_X) * (ofGetWidth() / (VIDEO_WIDTH * VIDEO_SCALE));
}

float Sensing::mapVideoYToScreenY(float yPos)
{
	return (yPos - VIDEO_Y) * (ofGetHeight() / (VIDEO_HEIGHT * VIDEO_SCALE));
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
				point->setScaleWidth( (float) _xml.getAttribute("point", "scalewidth", 1.00, i) );
				point->setScaleHeight( (float) _xml.getAttribute("point", "scaleheight", 1.00, i) );

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
		_xml.addAttribute("point", "scalewidth", ofToString(_balloons[i]->getScaleWidth(), 2), i);
		_xml.addAttribute("point", "scaleheight", ofToString(_balloons[i]->getScaleHeight(), 2), i);
	}
	
	_xml.popTag();
	
	_xml.saveFile(XML_FILE);
	
}

/* Getters / Setters
___________________________________________________________ */

vector <Balloon *> Sensing::getBalloons()
{
	vector <Balloon *> norm;
	
	for(int i = 0; i < _balloons.size(); i++)
	{
		Balloon * newPoint = new Balloon();
		newPoint->setX( (_balloons[i]->getX() + _xDisplaceAll) * _scalePosAll );
		newPoint->setY( (_balloons[i]->getY() + _yDisplaceAll) * _scalePosAll );
		
		if(i == _selectedBalloon)
		{
			_balloons[_selectedBalloon]->setScaleWidth( _scaleWidthSelected );
			_balloons[_selectedBalloon]->setScaleHeight( _scaleHeightSelected );
		}
		
		newPoint->setScaleWidth( _balloons[i]->getScaleWidth() * _scaleSizeAll );
		newPoint->setScaleHeight( _balloons[i]->getScaleHeight() * _scaleSizeAll );
		
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
	
	if(!_mapFromScreen)
	{
		_selectedBalloon = DISABLED;
	}
}

bool Sensing::disableAnimation()
{
	if(getPage() == 1 && getEnabled())
	{
		return true;
	}
	
	return false;
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
		if(_selectedBalloon != DISABLED)
		{
			_balloons[_selectedBalloon]->setX( _balloons[_selectedBalloon]->getX() + 1 );
		}
		else 
		{
			nextPage();
		}
	}
	// left arrow
	else if (key == 356) 
	{
		if(_selectedBalloon != DISABLED)
		{
			_balloons[_selectedBalloon]->setX( _balloons[_selectedBalloon]->getX() - 1 );
		}
		else 
		{
			prevPage();
		}
	}
	// up arrow
	else if (key == 357) 
	{
		if(_selectedBalloon != DISABLED)
		{
			_balloons[_selectedBalloon]->setY( _balloons[_selectedBalloon]->getY() - 1 );
		}
	}
	// down arrow
	else if (key == 359) 
	{
		if(_selectedBalloon != DISABLED)
		{
			_balloons[_selectedBalloon]->setY( _balloons[_selectedBalloon]->getY() + 1 );
		}
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
	else if (key == 'r') 
	{
		toggleMapFromScreen();
	}
}