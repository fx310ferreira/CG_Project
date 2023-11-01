#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	glEnable(GL_DEPTH_TEST);
	ofBackground(0.05, 0.05, 0.05);
	glLineWidth(2);

	//view
	view = 0;
    //variable for the lens
    lens = true;

	//floor parameters
	resX = 20;
	resY = 15;
    // resX = 3;
	// resY = 3;
	floorWidth = gw() * 0.6;
	floorHeight = gw() * 0.45;
	floorHeightPos = 0.;//gh() * 0.75;

    //building parameters
    baseWidth = floorWidth / GLfloat(resX);
    baseHeight = floorHeight / GLfloat(resY);
    baseWidthMin = floorWidth / GLfloat(resX) * 0.3;
	baseWidthMax = floorWidth / GLfloat(resX) * 0.9;
    baseHeightMin = floorHeight / GLfloat(resY) * 0.3;
	baseHeightMax = floorHeight / GLfloat(resY) * 0.9;
	baseDepthMax = 200;
    baseDepthMin = 10;
	basePos.x = 0;
	basePos.y = 0;
	basePos.z = 0;

    //mesh
    mesh = 10;

    baseGrid.clear();
    for(int i = 0; i < resX; i++){
        baseGrid.push_back({});
        for(int j = 0; j < resY; j++){
            baseGrid[i].push_back({ofRandom(baseWidthMin, baseWidthMax), 
            ofRandom(baseHeightMin, baseHeightMax), ofRandom(baseDepthMin, baseDepthMax),
            ofRandom(0,1), ofRandom(0,1), ofRandom(0,1), 
            i* baseWidth + baseWidth * 0.5 - floorWidth * 0.5,
            j * baseHeight + baseHeight * 0.5 - floorHeight * 0.5, 0, mesh});
        }
    }
    blackhole = {0, 0, baseDepthMax, 0, 4};

    angle = 0;
    lookDistance = 700;
}
  
//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    //View port for all the screen
	glColor3f(0.5, 0.5, 0.5);

    int lensAngle = 60;
    GLfloat alpha = 10;
    GLfloat beta = 1000;

	//lens and perspective
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    if(lens){
	    perspective(lensAngle, alpha, beta);
    }
    else{
        glOrtho(-gw() * 0.5, gw() * 0.5, -gh() * 0.5, gh() * 0.5, -1000, 10000);
    }

	//Camera positions
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glPushMatrix();//master push
    switch (view) {
    case 0:
        lookat(0,0,lookDistance, 0,0,0, 0,1,0);
        break;
    case 1:
        lookat(lookDistance*sin(angle),-lookDistance*cos(angle), 500+inc_z, 0,0,0, 0,0,1);
        break;
    case 2:
        angle += (2*PI/360)/2;
        lookat(lookDistance*sin(angle),-lookDistance*cos(angle), 500, 0,0,0, 0,0,1); //TODO change this do moduelar
        break;
    }


	//floor
	glPushMatrix();//floor push
        glScalef(floorWidth, floorHeight, 1.);
        malha_unit(resX, resY);
	glPopMatrix();//floor pop

	//skyscrapers
	glPushMatrix();//skyscrapers master push
        for(int i = 0; i < resX; i++){
            for(int j = 0; j < resY; j++){
                baseGrid[i][j].draw1();
            }
        }
	glPopMatrix();//skyscrapers master poop

	glPushMatrix();//TODO sphere???
        blackhole.draw();
    glPopMatrix();
glPopMatrix();//master pop
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case '1':
		glDisable(GL_CULL_FACE);
		break;
	case '2':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		break;
	case '3':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		break;
	case '4':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT_AND_BACK);
		break;
	case 'f':
        if(grid){
		    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            grid = false;
        }else{
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            grid = true;
        }

		break;
	case 'g':
		view ++;
        if (view > 2) {
            view = 0;
        }
		break;
    case 'v':
		lens = !lens; 
		break;
	case OF_KEY_LEFT:
		angle -= (2*PI/360)/2;
		break;
	case OF_KEY_RIGHT:
		angle += (2*PI/360)/2;
		break;
	case OF_KEY_UP:
		inc_z+=1;
		break;
	case OF_KEY_DOWN:
		inc_z-=1;
		break;
    case '+':
        lookDistance-=5;
        break;
    case '-':
        lookDistance+=5;
        break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	setup();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
