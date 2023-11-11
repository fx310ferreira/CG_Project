#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	glEnable(GL_DEPTH_TEST);
	ofBackground(0.05, 0.05, 0.05);
	glLineWidth(2);

    maxFPS = 60;
    maxPeriod = 1 / maxFPS;
    lastTime = ofGetElapsedTimef();

	//view
	view = 0;
    //variable for the lens
    lens = true;

	//floor parameters
	resX = 30;
	resY = 20;
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
    long unsigned mass =  6 * pow(10, 13);
    blackhole = {0, 0, baseDepthMax+200, 0, 50, mass};

    baseGrid.clear();
    for(int i = 0; i < resX; i++){
        baseGrid.push_back({});
        for(int j = 0; j < resY; j++){
            baseGrid[i].push_back({ofRandom(baseWidthMin, baseWidthMax), 
            ofRandom(baseHeightMin, baseHeightMax), ofRandom(baseDepthMin, baseDepthMax),
            ofRandom(0,1), ofRandom(0,1), ofRandom(0,1), 
            i* baseWidth + baseWidth * 0.5 - floorWidth * 0.5,
            j * baseHeight + baseHeight * 0.5 - floorHeight * 0.5, 0, mesh, blackhole});
        }
    }

    angle = 0;
    inc_angle = 0;
    lookDistance = 700;
    dis_z = 500;
}
 
//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    //FPS
    GLdouble time = ofGetElapsedTimef();
    GLdouble deltaTime = time - lastTime;

    if(deltaTime >= maxPeriod){
        deltaTime = maxPeriod - deltaTime;
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
            dis_z += inc_z;
            angle += inc_angle;
            lookat(lookDistance*sin(angle),-lookDistance*cos(angle), dis_z, 0,0,0, 0,0,1);
            break;
        case 2:
            dis_z += inc_z;
            angle += (2*PI/360)/2;
            lookat(lookDistance*sin(angle),-lookDistance*cos(angle), 500, 0,0,0, 0,0,1); //TODO change this do moduelar
            break;
        }


        //floor
        glPushMatrix();//floor push
            glScalef(floorWidth, floorHeight, 1.);
            glColor3f(0.5, 0.5, 0.5);
            malha_unit(resX, resY);
        glPopMatrix();//floor pop

        //skyscrapers
        glPushMatrix();//skyscrapers master push
            for(int i = 0; i < resX; i++){
                for(int j = 0; j < resY; j++){
                    baseGrid[i][j].draw();
                    baseGrid[i][j].blackhole = blackhole;
                }
            }
        glPopMatrix();//skyscrapers master poop

        glPushMatrix();
            blackhole.draw();
        glPopMatrix();
    glPopMatrix();//master pop
    }
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
		inc_angle = - (2*PI/360)/2;
		break;
	case OF_KEY_RIGHT:
		inc_angle = (2*PI/360)/2;
		break;
	case OF_KEY_UP:
		inc_z = 2;
		break;
	case OF_KEY_DOWN:
		inc_z = -2;
		break;
    case '+':
        lookDistance-=5;
        break;
    case '-':
        lookDistance+=5;
        break;
    case ' ':
        blackhole.radius = 1;
        for(int i = 0; i < resX; i++){
            for(int j = 0; j < resY; j++){
                baseGrid[i][j].decrement = 1;
                if(baseGrid[i][j].deleted){
                    baseGrid[i][j] = {ofRandom(baseWidthMin, baseWidthMax), 
                    ofRandom(baseHeightMin, baseHeightMax), ofRandom(baseDepthMin, baseDepthMax),
                    ofRandom(0,1), ofRandom(0,1), ofRandom(0,1), 
                    i* baseWidth + baseWidth * 0.5 - floorWidth * 0.5,
                    j * baseHeight + baseHeight * 0.5 - floorHeight * 0.5, 0, mesh, blackhole};
                }
            }
        }
        break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
    case OF_KEY_UP:
		inc_z = 0;
		break;
	case OF_KEY_DOWN:
		inc_z = 0;
		break;
    case OF_KEY_LEFT:
		inc_angle = 0;
		break;
	case OF_KEY_RIGHT:
		inc_angle = 0;
		break;
    }
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
