#include "Sensing.h"

/* Constructor
 ___________________________________________________________ */

Sensing::Sensing()
{
	_blobMode = false;
	_enabled = false;
	_mapFromScreen = false;
	_scalePosAll = 1;
	//_xDisplaceAll = 0;
	//_yDisplaceAll = 0;
	_xDisplaceAll = -1055;
	_yDisplaceAll = -723;
	_blobCalibrate = 3.09;
	_scaleSizeAll = 1;
	_constrainRatio = true;
	_scaleWidthSelected = 1;
	_scaleHeightSelected = 1;
	_oldScaleWidthSelected = 1;
	_oldScaleHeightSelected = 1;
	_selectedBalloon = DISABLED;
	_idcount = 0;
	
	_threshold = 242;
	_blurAmount = 10;
	_area = 1010;
	_showMask = true;
	
	_colorImg.allocate( VIDEO_WIDTH, VIDEO_HEIGHT );
	_grayImg.allocate( VIDEO_WIDTH, VIDEO_HEIGHT );
	_outputTexture.allocate(VIDEO_WIDTH, VIDEO_HEIGHT, GL_RGB);
	_mask.loadImage("mask.png");
	_mask.setImageType(OF_IMAGE_GRAYSCALE);
	_maskPixels = _mask.getPixels();
	
	//_camera.setDeviceID(1);
	_camera.initGrabber(VIDEO_WIDTH, VIDEO_HEIGHT);
	
	gui.addTitle("Video");
	gui.addContent("Input", _outputTexture);
	gui.addSlider("Threshold", _threshold , 0.0, 255);
	gui.addSlider("Bluring", _blurAmount , 0, 40);
	gui.addContent("Difference", _grayImg);
	gui.addSlider("Area", _area,4,6000);	
	gui.addToggle("Mask", _showMask);
	gui.addFPSCounter();
	
	gui.addPage("Control Page");
	gui.addTitle("All Balloons");
	gui.addSlider("X", _xDisplaceAll, -1500, 1000);
	gui.addSlider("Y", _yDisplaceAll, -1500, 1000);
	gui.addSlider("Scale Positions", _scalePosAll, 0.8, 4.0);
	gui.addSlider("Scale Sizes", _scaleSizeAll, 0.1, 4);
	gui.addSlider("Calibrate", _blobCalibrate, 0.6, 4);
	
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
	
	if(_blobMode)
	{
		if(_camera.isFrameNew()) 
		{
			_colorImg = _camera.getPixels();
			//_colorImg.mirror( false, true );
			_grayImg = _colorImg;
			
			_grayImg.blur( _blurAmount );
			_grayImg.threshold( _threshold );
			_grayPixels = _grayImg.getPixels();
			
			if (_showMask) 
			{
				for (int i=0; i<VIDEO_WIDTH*VIDEO_HEIGHT; i++) 
				{
					if(_maskPixels[i] == 0)
					{
						_grayPixels[i]= _maskPixels[i]; 
					}
				}
				
				_grayImg.setFromPixels(_grayPixels, VIDEO_WIDTH, VIDEO_HEIGHT);
			}
			//findContures( img, minSize, maxSize, nMax, inner contours yes/no )
			_contourFinder.findContours( _grayImg, _area, 300000, 20, false);
			_blobTracker.trackBlobs( _contourFinder.blobs );
		}
		
	}
}

/* Draw
 ___________________________________________________________ */

void Sensing::draw()
{	
	gui.draw();
	
	if(_enabled && gui.currentPage == 1)
	{
		_outputTexture.begin();
		ofSetColor( 0xffffff );
		_colorImg.draw(0, 0);
		_blobTracker.draw(0, 0);
		_outputTexture.end();
		
		/*ofSetColor(255, 255, 255);
		
		_camera.draw(VIDEO_X, VIDEO_Y, _camera.getWidth() * VIDEO_SCALE, _camera.getHeight() * VIDEO_SCALE);
		
		for (int i = 0; i < _balloons.size(); i++) 
		{
			if(i == _selectedBalloon)	
			{
				drawBalloon(mapScreenXToVideoX(_balloons[i]->getCenterX()), mapScreenYToVideoY(_balloons[i]->getCenterY()), 0x000FF00);
			}
			else
			{
				drawBalloon(mapScreenXToVideoX(_balloons[i]->getCenterX()), mapScreenYToVideoY(_balloons[i]->getCenterY()), 0xFF0000);
			}
		}*/
	}
	else if(!disableAnimation() && _mapFromScreen)
	{
		vector <Balloon *> balloons = getBalloons();
		
		ofSetColor(0, 255, 0);
		
		for(int i = 0; i < balloons.size(); i++)
		{
			if(i == _selectedBalloon)	
			{
				drawBalloon(balloons[i]->getCenterX(), balloons[i]->getCenterY(), 0x000FF00);
			}
			else
			{
				drawBalloon(balloons[i]->getCenterX(), balloons[i]->getCenterY(), 0xFF0000);
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

void Sensing::mouseDragged(int xPos, int yPos, int button)
{
	if(!_enabled && _mapFromScreen && _selectedBalloon != DISABLED)
	{
		_balloons[_selectedBalloon]->setCenterX((xPos / _scalePosAll) - _xDisplaceAll);
		_balloons[_selectedBalloon]->setCenterY((yPos / _scalePosAll) - _yDisplaceAll);
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
			newBalloon->setCenterX(xPos);
			newBalloon->setCenterY(yPos);
			newBalloon->setID(_idcount);
			
			_balloons.push_back(newBalloon);
			
			_idcount++;
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
		if(fabs(xPos - _balloons[i]->getCenterX()) < POINT_MARGIN && fabs(yPos - _balloons[i]->getCenterY()) < POINT_MARGIN)
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

float Sensing::cleanMapVideoXToScreenX(float xPos)
{
	return xPos * (ofGetWidth() / VIDEO_WIDTH);
}

float Sensing::cleanMapVideoYToScreenY(float yPos)
{
	return yPos * (ofGetHeight() / VIDEO_HEIGHT);
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
				point->setID(_idcount);
				point->setCenterX( (float) _xml.getAttribute("point", "x", 0, i) );
				point->setCenterY( (float) _xml.getAttribute("point", "y", 0, i) );
				point->setScale( (float) _xml.getAttribute("point", "scalewidth", 1.00, i), (float) _xml.getAttribute("point", "scaleheight", 1.00, i));
				_balloons.push_back(point);
				
				_idcount++;
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
		_xml.addAttribute("point", "x", ofToString(_balloons[i]->getCenterX(), 1), i);
		_xml.addAttribute("point", "y", ofToString(_balloons[i]->getCenterY(), 1), i);
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
	
	// get blobs
	if(_blobMode)
	{
		// loop through the blobs and make baloon objects
		for(int i = 0; i < _blobTracker.blobs.size(); i++)
		{
			ofxCvTrackedBlob& blob = _blobTracker.blobs[i];
			
			Balloon * newPoint = new Balloon();
			newPoint->setID(blob.id);
			newPoint->setCenterX( ((cleanMapVideoXToScreenX(blob.centroid.x) * _blobCalibrate) + _xDisplaceAll) * _scalePosAll );
			newPoint->setCenterY( ((cleanMapVideoYToScreenY(blob.centroid.y) * _blobCalibrate)  + _yDisplaceAll) * _scalePosAll);
			newPoint->setScale(1 * _scaleSizeAll, 1 * _scaleSizeAll);
			
			norm.push_back(newPoint);
		}
	}
	// get clicked points
	else 
	{
		for(int i = 0; i < _balloons.size(); i++)
		{
			Balloon * newPoint = new Balloon();
			newPoint->setID(_balloons[i]->getID());
			newPoint->setCenterX( (_balloons[i]->getCenterX() + _xDisplaceAll) * _scalePosAll );
			newPoint->setCenterY( (_balloons[i]->getCenterY() + _yDisplaceAll) * _scalePosAll );
			
			if(i == _selectedBalloon)
			{
				_balloons[_selectedBalloon]->setScale( _scaleWidthSelected, _scaleHeightSelected);
			}
			
			newPoint->setScale(_balloons[i]->getScaleWidth() * _scaleSizeAll, _balloons[i]->getScaleHeight() * _scaleSizeAll);
			
			norm.push_back(newPoint);
		}
	}
	
	return norm;
}

vector <Balloon *> Sensing::getBalloonsSorted()
{
	vector <Balloon *> norm = getBalloons();
	
	//std::sort(norm.begin(), norm.end(), Sensing::xsorter());
	std::sort(norm.begin(), norm.end(), Sensing::ysorter());
	
	// instead just run through the vector and do:
		// find the topmost balloon
		// Find all balloons 100 pixels below this
		// Pick from those balloons the balloon that is furthest to the left
			// put it to a new vector
			// remove it from original
		// keep picking the balloon furthest to the left until no one is left.
		
		// start over...
		
	
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
			_balloons[_selectedBalloon]->setCenterX( _balloons[_selectedBalloon]->getCenterX() + 1 );
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
			_balloons[_selectedBalloon]->setCenterX( _balloons[_selectedBalloon]->getCenterX() - 1 );
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
			_balloons[_selectedBalloon]->setCenterY( _balloons[_selectedBalloon]->getCenterY() - 1 );
		}
	}
	// down arrow
	else if (key == 359) 
	{
		if(_selectedBalloon != DISABLED)
		{
			_balloons[_selectedBalloon]->setCenterY( _balloons[_selectedBalloon]->getCenterY() + 1 );
		}
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
	else if (key == 'S') 
	{
		saveBalloons();
	}	
	else if (key == 'L') 
	{
		loadBalloons();
	}
	else if (key ==' ') 
	{
		toggleEnabled();
	}
	else if (key == 'r') 
	{
		toggleMapFromScreen();
	}
	else if (key == 'f') 
	{
		// bring selected to front
	}
	else if (key == 'b') 
	{
		// bring selected to back
	}
	else if(key == '0')
	{
		_blobMode = !_blobMode;
	}
	
	//_scalePosAll += 0.005;
	//_scalePosAll -= 0.005;
}