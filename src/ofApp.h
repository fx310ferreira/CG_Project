#pragma once

#include "ofMain.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"
#include "cg_cam_extras_solution.h"
#include "skyscraper.h"
#include "GL/glut.h"
#include "blackhole.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		//game variables
		//floor
		GLint resX, resY;
		GLfloat floorWidth, floorHeight, floorHeightPos;

		//tank
		//base
		GLfloat baseWidthMax, baseWidthMin, baseWidth;
		GLfloat baseHeightMin, baseHeightMax, baseHeight;
		GLfloat baseDepthMax, baseDepthMin;
		GLfloat R, G, B;
		GLint basePosGridX, basePosGridY;
		ofVec3f basePos;

		std::vector<std::vector<Skyscraper>> baseGrid;
		Blackhole blackhole = {0,0,0, 0,0};

		int reset;
		bool grid;

		//view
		int view;
		double angle, inc_z;
		bool lens = true;
		int mesh;
		int lookDistance;
		double count;
};
