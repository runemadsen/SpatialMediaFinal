#include "BalloonControllerStars.h"
#include "Expo.h"

/* Constructor
 ___________________________________________________________ */

BalloonControllerStars::BalloonControllerStars(Balloon * model) : BalloonController(model)
{
	balloonShine.loadImage("balloon.png");
	
	timer.setDuration(150);
	
	PSetting setting1;
	
	//if(ofRandomuf() > 0.3)
	//{
		setting1.percent = 1;
		setting1.sizeMin = 8;
		setting1.sizeMax = 15;
		setting1.dirMin = 0.1;
		setting1.dirMax = 0.3;
		setting1.lifeMin = 0.5;
		setting1.lifeMax = 0.5;
	/*
	}
	else 
	{
		setting1.percent = 1;
		setting1.sizeMin = 5;
		setting1.sizeMax = 10;
		setting1.dirMin = 0.2;
		setting1.dirMax = 0.8;
		setting1.lifeMin = 0.5;
		setting1.lifeMax = 0.5;
	}*/
	
	_settings.push_back(setting1);
	_direction.set(ofRandomf(), ofRandomf());
	_direction.normalize();
	
	numParticles = 0;
	
	
	// Setup the VBO
	glGenBuffersARB(3, &particleVBO[0]);	
	
	// color
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[0]);	
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, (MAX_PARTICLES*4)*4*sizeof(float), color, GL_STREAM_DRAW_ARB);	

	// vertices
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[1]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, (MAX_PARTICLES*4)*3*sizeof(float), pos, GL_STREAM_DRAW_ARB);
	
	// texture coords
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[2]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, (MAX_PARTICLES*4)*2*sizeof(float), texcords, GL_STREAM_DRAW_ARB);
}

/* Set texture
 _______________________________________________________________________ */

void BalloonControllerStars::setTexture(ofImage newTexture, int cellsInRow, int cellsInCol) 
{
	ofDisableArbTex();
	texture = newTexture;
	ofEnableArbTex();
	
	texW = texture.getWidth();
	texH = texture.getHeight();
	
	cellRows  = cellsInRow;
	cellColls = cellsInCol; 
}

/* Update
 ___________________________________________________________ */

void BalloonControllerStars::update()
{
	timer.tick();
	
	//if(model->visible)	
	//{
		if(numParticles < MAX_PARTICLES)
		{
			for(int i = 0; i < 1; i++)
			{
				spawn(numParticles);
				
				numParticles++;
				
				if(numParticles >= MAX_PARTICLES)
					break;
			}
		}
	//}
	
	for(int i=0; i<numParticles; i++) 
	{
		vel[i][0] += acc[i][0];
		vel[i][1] += acc[i][1];
		
		vel[i][0] *= damping[i];
		vel[i][1] *= damping[i];
		vel[i][2] *= damping[i];
		
		addPosition(i, vel[i][0], vel[i][1], vel[i][2]);
		
		// fade by the life rate
		if(fadeDown[i])
		{
			life[i][0] -= life[i][1];
		}
		else 
		{
			life[i][0] += life[i][1];
		}
		
		if(isParticleInsideEllipse(i))
		{
			setParticleColor(i, 1.0, 1.0, 1.0, life[i][0]);
		}
		else 
		{
			setParticleColor(i, 1.0, 1.0, 1.0, 0);
		}
		
		checkParticle(i);
	}
	
}

/* Create Particle
 _______________________________________________________________________ */

void BalloonControllerStars::spawn(int i) 
{
	float percent = 0.0;
	float random = ofRandomuf();
	
	for (int j = 0; j < _settings.size(); j++) 
	{
		percent += _settings[j].percent;
		
		if (random < percent) 
		{
			// set org life			
			life[i][2] = ofRandom(_settings[j].lifeMin, _settings[j].lifeMax);
			
			setParticleSize(i, ofRandom(_settings[j].sizeMin, _settings[j].sizeMax));
			setParticleColor(i, 1, 1, 1, 1);
			
			ofPoint pos;
			pos.set(ofRandom(_model->getTopLeftX(), _model->getTopLeftX() + _model->getWidth()), ofRandom(_model->getTopLeftY(), _model->getTopLeftY() + _model->getHeight()));
			
			// choose direction of particle
			setParticlePos(i, pos.x, pos.y);
			setParticleTexCoords(i, (int)ofRandom(0, 2), (int)ofRandom(0, 2));
			
			life[i][0] = 0;
			life[i][1] = ofRandom(_settings[j].lifeSubMin, _settings[j].lifeSubMax);
			
			ofxVec2f direction = _direction * ofRandom(_settings[j].dirMin, _settings[j].dirMax);
			
			acc[i][0] = direction.x;
			acc[i][1] = direction.y;
			acc[i][2] = 0;
			
			fadeDown[i] = false;
			
			damping[i] = _settings[j].damping;
			
			break;
		}
	}	
}

/* Create Particle numbers
 _______________________________________________________________________ */

void BalloonControllerStars::checkParticle(int i)
{
	// check alpha
	if(life[i][0] <= 0.0) 
	{
		//if(model->visible)	
		//{
			fadeDown[i] = false;
		//}
	}
	else if(life[i][0] >= life[i][2]) 
	{
		//if(model->visible)	
		//{
			fadeDown[i] = true;
		//}
	}
	
	
	switch (isParticleInsideBox(i)) 
	{
		case DISABLED: // is inside
			break;
		case 0: // is left
			setParticlePos(i, _model->getTopLeftX() + _model->getWidth(), getY(i));
			break;
		case 1: // is right
			setParticlePos(i, _model->getTopLeftX(), getY(i));
			break;
		case 2: // is top
			setParticlePos(i, getX(i), _model->getTopLeftY() + _model->getHeight());
			break;
		case 3: // is bottom
			setParticlePos(i, getX(i), _model->getTopLeftY());
			break;
		default:
			break;
	}
}

/* Draw
 ___________________________________________________________ */

void BalloonControllerStars::draw()
{
	ofRectangle bounds = _model->getBoundsFromSize(balloonShine.getWidth(), balloonShine.getHeight(), false);
	
	float alpha = Expo::easeOut(timer.getTime(), 40, 140, timer.getDuration());
	
	ofSetColor(255, 255, 255, alpha);
	ofEnableAlphaBlending();
	balloonShine.draw(bounds.x, bounds.y, bounds.width, bounds.height);
	ofDisableAlphaBlending();
	
	glEnable(GL_TEXTURE_2D);	// Tells OpenGL that we want to draw a 2d teture
	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); // Enables the Texture coordinate array for drawing with glDrawArrays or glDrawElements calls 
	glEnableClientState(GL_VERTEX_ARRAY); // Enables the Vertex array for drawing with glDrawArrays or glDrawElements calls 
	glEnableClientState(GL_COLOR_ARRAY); // Enables the Color array for drawing with glDrawArrays or glDrawElements calls 
	
	// bind tex coors
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[2]); // init VBO (see above)
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, (MAX_PARTICLES*4)*2*sizeof(float), texcords); // put data in VBO
	glTexCoordPointer(2, GL_FLOAT, 0, 0); // Tell OpenGL that we have 2 coordinates and the coordinates in the array are floats
	
	
	// bind color
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[0]);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, (MAX_PARTICLES*4)*4*sizeof(float), color);
	glColorPointer(4, GL_FLOAT, 0, 0);
	
	
	// bind vertices [these are quads]
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[1]);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, (MAX_PARTICLES*4)*3*sizeof(float), pos);
	glVertexPointer(3, GL_FLOAT, 0, 0); // Tell OpenGL that we have 3 coordinates (x, y, z) and the coordinates are stored as floats in the array
	
	// draw the vbo
	//glDisable(GL_DEPTH_TEST); // disable depth test (whatever it is)
	
	ofEnableArbTex();	
	
	ofEnableAlphaBlending();
	
	texture.getTextureReference().bind();
	
	glDrawArrays(GL_QUADS, 0, MAX_PARTICLES*4);  // render all array data we putted in VBO's as quads, at index 0, and to the end of the arrays
	
	texture.getTextureReference().unbind();
	
	ofDisableAlphaBlending();
	
	ofDisableArbTex();
	
	//glEnable(GL_DEPTH_TEST);
	
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
	glDisable(GL_TEXTURE_2D);
	
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}

/* Set Particle Texture Coordinates
 _______________________________________________________________________ */

void BalloonControllerStars::setParticleTexCoords(int i, float columnID, float rowID) 
{	
	if(i < 0)				i = 0;
	if(i > MAX_PARTICLES)	i = MAX_PARTICLES;
	
	if(columnID > cellColls) columnID = cellColls;
	if(rowID    > cellRows)	 rowID	  = cellRows;
	
	if(columnID < 0) columnID = 0;
	if(rowID < 0)	 rowID	  = 0;
	
	// get the cell image width
	float cellWidth  = texW / cellRows;
	float cellHeight = texH / cellColls;
	
	float row = rowID;
	float col = columnID;
	
	// P1
	texcords[(i*4)+0].u = (cellWidth * row)		/ texW;
	texcords[(i*4)+0].v = (cellHeight * col)	/ texH;
	
	// P2
	texcords[(i*4)+1].u = ((cellWidth * row)	+ cellWidth)	/ texW;
	texcords[(i*4)+1].v = (cellHeight * col)	/ texH;
	
	// P2
	texcords[(i*4)+2].u = ((cellWidth * row) + cellWidth)		/ texW;
	texcords[(i*4)+2].v = ((cellHeight * col) + cellHeight)	/ texH;	
	
	// P2
	texcords[(i*4)+3].u = (cellWidth * row)		/ texW;
	texcords[(i*4)+3].v = ((cellHeight * col)+cellHeight)	/ texH;	
}

/* Set Particle Color
 _______________________________________________________________________ */

void BalloonControllerStars::setParticleColor(int i, float r, float g, float b, float a) 
{
	if(i < 0) i = 0;
	if(i > MAX_PARTICLES) i = MAX_PARTICLES;
	
	
	// Color 1
	color[(i*4)+0].r = r;
	color[(i*4)+0].g = g;
	color[(i*4)+0].b = b;
	color[(i*4)+0].a = a;
	
	// Color 2
	color[(i*4)+1].r = r;
	color[(i*4)+1].g = g;
	color[(i*4)+1].b = b;
	color[(i*4)+1].a = a;
	
	// Color 3
	color[(i*4)+2].r = r;
	color[(i*4)+2].g = g;
	color[(i*4)+2].b = b;
	color[(i*4)+2].a = a;
	
	// Color 4
	color[(i*4)+3].r = r;
	color[(i*4)+3].g = g;
	color[(i*4)+3].b = b;
	color[(i*4)+3].a = a;
	
}

/* Set Particle Position
 _______________________________________________________________________ */

void BalloonControllerStars::setParticlePos(int i, float px, float py, float pz) 
{	
	if(i < 0)				i = 0;
	if(i > MAX_PARTICLES)	i = MAX_PARTICLES;
	
	// P1
	pos[(i*4)+0].x = px;
	pos[(i*4)+0].y = py;
	pos[(i*4)+0].z = pz;
	
	// P2
	pos[(i*4)+1].x = px + dim[i];
	pos[(i*4)+1].y = py;
	pos[(i*4)+1].z = pz;
	
	// P3
	pos[(i*4)+2].x = px + dim[i];
	pos[(i*4)+2].y = py + dim[i];
	pos[(i*4)+2].z = pz;
	
	// P4
	pos[(i*4)+3].x = px;
	pos[(i*4)+3].y = py + dim[i];
	pos[(i*4)+3].z = pz;
}

/* Set Particle Size
 _______________________________________________________________________ */

void BalloonControllerStars::setParticleSize(int i, float particleDim) 
{	
	if(i < 0)				i = 0;
	if(i > MAX_PARTICLES)	i = MAX_PARTICLES;
	
	dim[i] = particleDim;
}

/* Add Position
 _______________________________________________________________________ */

void BalloonControllerStars::addPosition(int i, float x, float y, float z) 
{	
	if(i < 0)				i = 0;
	if(i > MAX_PARTICLES)	i = MAX_PARTICLES;
	
	// P1
	pos[(i*4)+0].x += x;
	pos[(i*4)+0].y += y;
	pos[(i*4)+0].z += z;
	
	// P2
	pos[(i*4)+1].x += x;
	pos[(i*4)+1].y += y;
	pos[(i*4)+1].z += z;
	
	// P2
	pos[(i*4)+2].x += x;
	pos[(i*4)+2].y += y;
	pos[(i*4)+2].z += z;
	
	// P2
	pos[(i*4)+3].x += x;
	pos[(i*4)+3].y += y;
	pos[(i*4)+3].z += z;
}

/* Is particle inside
 _______________________________________________________________________ */

bool BalloonControllerStars::isParticleInsideEllipse(int pi)
{
	float x = getX(pi) - _model->getCenterX();
	float y = getY(pi) - _model->getCenterY();
	
	float xRadius = _model->getWidth() / 2;
	float yRadius = _model->getHeight() / 2;
	
	return ((x*x/xRadius/xRadius + y*y/yRadius/yRadius) < 1);
}

int BalloonControllerStars::isParticleInsideBox(int pi)
{
	float px = getX(pi);
	float py = getY(pi);
	
	if(px < _model->getTopLeftX())
	{
		return 0;
	}
	else if(px > _model->getTopLeftX() + _model->getWidth())
	{
		return 1;
	}
	else if(py < _model->getTopLeftY())
	{
		return 2;
	}
	else if(py > _model->getTopLeftY() + _model->getHeight())
	{
		return 3;
	}
	
	return DISABLED;
}

/* Midi note on / off
 ___________________________________________________________ */

void BalloonControllerStars::noteOn()
{
	timer.setState(1);
}

void BalloonControllerStars::noteOff()
{
	timer.setState(-1);
}

/* Getter / Setter
 _______________________________________________________________________ */

int BalloonControllerStars::getTotal()
{
	return numParticles;
}

int BalloonControllerStars::getX(int i)
{
	return pos[(i*4)+0].x;
}

int BalloonControllerStars::getY(int i)
{
	return pos[(i*4)+0].y;
}


