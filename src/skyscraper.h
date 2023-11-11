#ifndef SKYSCRAPPER_H
#define SKYSCRAPPER_H

#include "ofMain.h"
#include "cg_extras.h"
#include "blackhole.h"
#include "cg_drawing_extras.h"

class Skyscraper {
    public:
        
        GLfloat width, height, depth, maxDepth;
        GLfloat R, G, B;
        ofVec3f pos, vel;
        ofVec3f angle;
        GLdouble acc;
        GLint mesh;
        GLint delay;
        Blackhole blackhole;
        GLint decrement = 0;
        bool deleted = false;
        bool cap = false;
        bool cap2 = false;

        Skyscraper() {
            ;
        }

        Skyscraper(GLfloat _width, GLfloat _height, GLfloat _depth, GLfloat _R, GLfloat _G, GLfloat _B, GLfloat _posGridX, GLfloat _posGridY, GLfloat _posGridZ, GLint _mesh, Blackhole _blackhole) {
            width = _width;
            height = _height;
            maxDepth = _depth;
            R = _R;
            G = _G;
            B = _B;
            pos = ofVec3f(_posGridX, _posGridY, _posGridZ);
            mesh = _mesh;
            delay = ofRandom(0, 1200);
            vel = ofVec3f(0,0,0);
            blackhole = _blackhole;
            if(ofRandom(0,1) > 0.5){
                cap = true ;
                ofRandom(0,1) > 0.5 ? cap2 = true : cap2 = false;
            }
            depth = 0;
        }

        void draw() {
            if(deleted){
                return;
            }
            if(depth < maxDepth){
                depth += 1;
            }
            glPushMatrix(); //master push
            update();
            glTranslatef(pos.x, pos.y, pos.z+0.5*depth);
            angle.y = angle.y * 180 / M_PI;
            angle.x = angle.x * 180 / M_PI;
            glRotated(angle.y, 1, 0, 0);
            glRotated(angle.x, 0, 1, 0);
            glPushMatrix();//base push
            glColor3f(R, G, B);
            glScalef(width, height, depth);
            cube_mesh_unit(mesh,mesh);
            glPopMatrix();//base pop
            if(cap){
                glTranslatef(0, 0, depth*0.5+depth*0.05/4);
                glPushMatrix();//base push
                glColor3f(R, G, B);
                glScalef(width*0.8, height*0.8, depth*0.05/2);
                cube_mesh_unit(mesh/2,mesh/2);
                glPopMatrix();//base pop
            }if(cap2){
                glTranslatef(0, 0,  depth*0.05/4+depth*0.20/2);
                glPushMatrix();//base push
                glColor3f(R, G, B);
                glScalef(width*0.1, height*0.1, depth*0.20);
                cube_unit();
                glPopMatrix();//base pop
            }
            glPopMatrix();//master pop
        }
    private:
        void update() {
            if(delay > 0){
                delay -= decrement;
            }else{
                ofVec3f direction;
                direction.x = blackhole.pos.x - pos.x;
                direction.y = blackhole.pos.y - pos.y;
                direction.z = blackhole.pos.z - (pos.z + 0.5*depth);
                GLdouble distance = direction.length();
                direction = direction.getNormalized();
                if(distance < blackhole.radius+depth*0.5){
                    depth *=0.98;
                }
                if(distance < blackhole.radius){
                    deleted = true;
                    return;
                }
                if(depth < 10){
                    deleted = true;
                    return;
                }
                acc = (blackhole.mass *  6.674 * pow(10, -11)) / (distance * distance);
                vel += direction * acc/60;
                // cout << "ACC: " << acc << " MASS: " << blackhole.mass << " VEL: " << vel << endl; 
                pos += vel;
                angle = ofVec3f(asin(direction.x), -asin(direction.y), asin(direction.z));
            }
        }
};

#endif