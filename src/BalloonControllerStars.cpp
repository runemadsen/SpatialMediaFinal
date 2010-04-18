#include "BalloonControllerStars.h"

/* Constructor
 ___________________________________________________________ */

BalloonControllerStars::BalloonControllerStars(Balloon * model) : BalloonController(model)
{
	PSetting setting1;
	
	if(ofRandomuf() > 0.3)
	{
		setting1.percent = 1;
		setting1.sizeMin = 3;
		setting1.sizeMax = 6;
		setting1.dirMin = 3;
		setting1.dirMax = 5;
		setting1.lifeMin = 0.5;
		setting1.lifeMax = 0.5;
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
	}
	
	_settings.push_back(setting1);
	_direction.set(ofRandomf(), ofRandomf());
	_direction.normalize();
	
	numParticles = 0;
	
	// Setup the VBO
	
	glGenBuffersARB(3, &particleVBO[0]);	// Create 3 vertex buffer object. Give address to GLUint array where ID's are stored
	
	// color
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[0]);	// Init VBO 0 as a vertex array VBO
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, (MAX_PARTICLES*4)*4*sizeof(float), color, GL_STREAM_DRAW_ARB);	// Copy data into VBO 0: 
	// Second parameter is the number of bytes to allocate
	// Third parameter is pointer to the actual data
	// Fourth parameter is for performance and says how the VBO is going to be used: Stream means that it will be changed every frame. Draw means data is sent to GPU
	
	// vertices
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[1]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, (MAX_PARTICLES*4)*3*sizeof(float), pos, GL_STREAM_DRAW_ARB);
	
	// texture coords
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[2]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, (MAX_PARTICLES*4)*2*sizeof(float), texcords, GL_STREAM_DRAW_ARB);
}

/* Update
 ___________________________________________________________ */

void BalloonControllerStars::update()
{
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
		
		if(isParticleInsidePoly(i))
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
		percent += model->settings[j].percent;
		
		if (random < percent) 
		{
			// set org life			
			life[i][2] = ofRandom(model->settings[j].lifeMin, model->settings[j].lifeMax);
			
			setParticleSize(i, ofRandom(model->settings[j].sizeMin, model->settings[j].sizeMax));
			setParticleColor(i, 1, 1, 1, 1);
			
			ofPoint pos;
			pos.set(ofRandom(model->boundingBox.x, model->boundingBox.x + model->boundingBox.width), ofRandom(model->boundingBox.y, model->boundingBox.y + model->boundingBox.height));
			
			// choose direction of particle
			setParticlePos(i, pos.x, pos.y);
			setParticleTexCoords(i, (int)ofRandom(0, 2), (int)ofRandom(0, 2));
			
			life[i][0] = 0;
			life[i][1] = ofRandom(model->settings[j].lifeSubMin, model->settings[j].lifeSubMax);
			
			ofxVec2f direction = model->direction * ofRandom(model->settings[j].dirMin, model->settings[j].dirMax);
			
			acc[i][0] = direction.x;
			acc[i][1] = direction.y;
			acc[i][2] = 0;
			
			fadeDown[i] = false;
			
			damping[i] = model->settings[j].damping;
			
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
			setParticlePos(i, model->boundingBox.x + model->boundingBox.width, getY(i));
			break;
		case 1: // is right
			setParticlePos(i, model->boundingBox.x, getY(i));
			break;
		case 2: // is top
			setParticlePos(i, getX(i), model->boundingBox.y + model->boundingBox.height);
			break;
		case 3: // is bottom
			setParticlePos(i, getX(i), model->boundingBox.y);
			break;
		default:
			break;
	}
}



/* Draw
 ___________________________________________________________ */

void BalloonControllerStars::draw()
{
	glEnable(GL_TEXTURE_2D);	// Tells OpenGL that we want ot draw a 2d teture
	
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
	glDisable(GL_DEPTH_TEST); // disable depth test (whatever it is)
	ofEnableArbTex();	
	
	ofEnableAlphaBlending();
	
	texture.getTextureReference().bind();
	
	glDrawArrays(GL_QUADS, 0, MAX_PARTICLES*4);  // render all array data we putted in VBO's as quads, at index 0, and to the end of the arrays
	
	texture.getTextureReference().unbind();
	
	ofDisableAlphaBlending();
	
	ofDisableArbTex();
	
	glEnable(GL_DEPTH_TEST);
	
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
	glDisable(GL_TEXTURE_2D);
	
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}

/* Getter / Setter
 ___________________________________________________________ */

void BalloonControllerStars::setTexture(ofImage newTexture, int cellsInRow, int cellsInCol) 
{
	//view.setTexture(newTexture, cellsInRow, cellsInCol);
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

bool BalloonControllerStars::isParticleInsidePoly(int pi)
{
	float px = getX(pi);
	float py = getY(pi);
	float x1,x2;
	int crossings = 0;
	
	for(int i = 0; i < model->outline.size(); i++)
	{
		if (model->outline[i].x < model->outline[ (i+1) % model->outline.size()].x)
		{
			x1 = model->outline[i].x;
			x2 = model->outline[(i+1) % model->outline.size()].x;
		} 
		else 
		{
			x1 = model->outline[(i+1) % model->outline.size()].x;
			x2 = model->outline[i].x;
		}
		
		if ( px > x1 && px <= x2 && ( py < model->outline[i].y || py <= model->outline[(i+1) % model->outline.size()].y)) 
		{
			static const float eps = 0.000001;
			
			float dx = model->outline[(i+1) % model->outline.size()].x - model->outline[i].x;
			float dy = model->outline[(i+1) % model->outline.size()].y - model->outline[i].y;
			float k;
			
			if(fabs(dx) < eps)
			{
				k = INFINITY;
			} 
			else 
			{
				k = dy/dx;
			}
			
			float m = model->outline[i].y - k * model->outline[i].x;
			
			float y2 = k * px + m;
			
			if ( py <= y2 )
			{
				crossings++;
			}
		}
	}
	
	if (crossings % 2 == 1)
	{		
		return true;
	}
	
	return false;
}

int BalloonControllerStars::isParticleInsideBox(int pi)
{
	float px = getX(pi);
	float py = getY(pi);
	
	if(px < model->boundingBox.x)
	{
		return 0;
	}
	else if(px > model->boundingBox.x + model->boundingBox.width)
	{
		return 1;
	}
	else if(py < model->boundingBox.y)
	{
		return 2;
	}
	else if(py > model->boundingBox.y + model->boundingBox.height)
	{
		return 3;
	}
	
	return DISABLED;
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

void BalloonControllerStars::setModel(TouchModel * newModel)
{
	model = newModel;
}


