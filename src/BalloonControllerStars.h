#pragma once

#include "ofMain.h"
#include "BalloonController.h"
#include "Balloon.h"
#include "Tools.h"
#include "ofxVec2f.h"
#include "Constants.h"

class BalloonControllerStars : public BalloonController
{
	
public:
	
	BalloonControllerStars(Balloon * model);
	
	void update();
	void draw();
	
	void setTexture(ofImage newTexture, int cellsInRow, int cellsInCol);
	
	int getX(int i);
	int getY(int i);
	int getTotal();
	
	ofImage	texture;
	
private:
	
	vector <PSetting> _settings;
	ofxVec2f _direction;
	
	int numParticles;
	int			cellRows;
	int			cellColls;
	
	GLuint		particleVBO[3];
	
	PVector		pos[MAX_PARTICLES*4];		// vertex (quad) of particle
	PTexture	texcords[MAX_PARTICLES*4];	// texture coords
	PColor		color[MAX_PARTICLES*4];		// particle color rgba
	bool		fadeDown[MAX_PARTICLES];
	
	float		texW, texH;
	float		dim[MAX_PARTICLES];			// particle size (w/h)
	float		vel[MAX_PARTICLES][3];		
	float		acc[MAX_PARTICLES][3];
	float		damping[MAX_PARTICLES];
	float		life[MAX_PARTICLES][3];		//	[life] [life rate] [org life]
	
	void spawn(int i);
	void checkParticle(int i);
	
	void setParticleColor(int i, float r, float g, float b, float a=0.0);
	void setParticlePos(int i, float px, float py, float pz=0.0);
	void setParticleSize(int i, float particleDim);
	void addPosition(int i, float x, float y, float z);
	void setParticleTexCoords(int i, float columnID, float rowID);
	
	bool isParticleInsideEllipse(int pi);
	int isParticleInsideBox(int pi);
};