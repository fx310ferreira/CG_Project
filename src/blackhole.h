#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "ofMain.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"

class Blackhole {
    public:
        ofVec3f pos;
        GLdouble radius;
        int count = 0;
        int mesh;
        long unsigned mass;

        Blackhole(){
            pos = ofVec3f(0, 0, 0);
            radius = 0;
            mesh = 50;
            mass = 60000;
        }

        Blackhole(GLfloat x_, GLfloat y_, GLfloat z_, GLfloat radius_, int mesh_, long unsigned mass_) {
            pos = ofVec3f(x_, y_, z_);
            radius = radius_;
            mesh = mesh_;
            mass = mass_;
        }

        void draw() { //TODO posicionamento especial????
            if(radius < 300 and radius > 0.1){
                radius += 1/60.0;
            }
            count += 1;
            glColor3f(1, 1, 1);
            glTranslatef(pos.x, pos.y, pos.z);
            glScalef(radius,radius,radius);
            glRotated(count,0,0,1);
            unit_sphere();
        }
    
    private:
        void unit_sphere() {
            GLfloat theta_s, theta_e;
            GLfloat theta_step = 2.0 * M_PI / GLfloat(mesh);
            GLfloat phi_s, phi_e;
            GLfloat phi_step = M_PI / GLfloat(mesh);
            GLfloat x1, y1, z1;
            GLfloat x2, y2, z2;
            GLfloat x3, y3, z3;
            GLfloat x4, y4, z4;

            for (int i = 0; i < mesh; i++) {
                theta_s = i * theta_step;
                theta_e = theta_s + theta_step;
                glBegin(GL_TRIANGLES);
                phi_s = M_PI /2;
                phi_e = M_PI /2 - phi_step;
                x1 = sin(theta_s) * cos(phi_s);
                y1 = cos(theta_s) * cos(phi_s);
                z1 = sin(phi_s);
                x2 = sin(theta_e) * cos(phi_e);
                y2 = cos(theta_e) * cos(phi_e);
                z2 = sin(phi_e);
                x3 = sin(theta_s) * cos(phi_e);
                y3 = cos(theta_s) * cos(phi_e);
                z3 = sin(phi_e);
                glVertex3d(x3, y3, z3);
                glVertex3d(x2, y2, z2);
                glVertex3d(x1, y1, z1);
                glEnd();
                glBegin(GL_QUADS);
                for (int j = 1; j < mesh-1; j++) {
                    if(i == j){
                        glColor3f(1, 0, 0);
                    }else{
                        glColor3f(1, 1, 1);
                    }
                    phi_s = M_PI /2 - j * phi_step;
                    phi_e = M_PI /2 - (j+1) * phi_step;
                    x1 = sin(theta_s) * cos(phi_s);
                    y1 = cos(theta_s) * cos(phi_s);
                    z1 = sin(phi_s);
                    x2 = sin(theta_e) * cos(phi_s);
                    y2 = cos(theta_e) * cos(phi_s);
                    z2 = sin(phi_s);
                    x3 = sin(theta_e) * cos(phi_e);
                    y3 = cos(theta_e) * cos(phi_e);
                    z3 = sin(phi_e);
                    x4 = sin(theta_s) * cos(phi_e);
                    y4 = cos(theta_s) * cos(phi_e);
                    z4 = sin(phi_e);
                    glVertex3f(x4, y4, z4);
                    glVertex3f(x3, y3, z3);
                    glVertex3f(x2, y2, z2);
                    glVertex3f(x1, y1, z1);
                    // glNormal3f(x1, y1, z1);
                    // glNormal3f(x2, y2, z2);
                    // glNormal3f(x3, y3, z3);
                    // glNormal3f(x4, y4, z4);
                }
                glEnd();
                glBegin(GL_TRIANGLES);
                phi_s = M_PI /2 - (mesh-1) * phi_step;
                phi_e = - M_PI /2;
                x1 = sin(theta_s) * cos(phi_s);
                y1 = cos(theta_s) * cos(phi_s);
                z1 = sin(phi_s);
                x2 = sin(theta_e) * cos(phi_s);
                y2 = cos(theta_e) * cos(phi_s);
                z2 = sin(phi_s);
                x3 = sin(theta_e) * cos(phi_e);
                y3 = cos(theta_e) * cos(phi_e);
                z3 = sin(phi_e);
                glVertex3d(x3, y3, z3);
                glVertex3d(x2, y2, z2);
                glVertex3d(x1, y1, z1);
                glEnd();
            }
        }
};

#endif