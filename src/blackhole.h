#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "ofMain.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"

class Blackhole {
    public:
        GLfloat x, y, z;
        GLfloat radius;
        int count = 0;
        int mesh;

        Blackhole(GLfloat x_, GLfloat y_, GLfloat z_, GLfloat radius_, int mesh_) {
            x = x_;
            y = y_;
            z = z_;
            radius = radius_;
            mesh = mesh_;
        }

        void draw() { //TODO posicionamento especial????
            count += 1;
            radius += 0.1;
            glColor3f(1, 1, 1);
            glTranslatef(0,0,300);
            glScalef(100,100,100);
            // glRotated(count,0,0,1);
            unit_sphere();
        }
    
    private:
        void unit_sphere() {
            GLfloat teta, phi;
            GLfloat teta_step = M_PI / GLfloat(mesh);
            GLfloat phi_step = 2.0 * M_PI / GLfloat(mesh);
            GLfloat x, y, z;
            GLfloat x1, y1, z1;
            GLfloat x2, y2, z2;
            GLfloat x3, y3, z3;
            GLfloat x4, y4, z4;

            for (int i = 0; i < mesh; i++) {
                teta = i * teta_step;
                glBegin(GL_QUADS);
                for (int j = 0; j < 1; j++) {
                    // glColor3f(0.1*i, 0.1*j, 0);
                    phi = j * phi_step;
                    x = sin(teta) * cos(phi);
                    y = sin(teta) * sin(phi);
                    z = cos(teta);
                    x1 = sin(teta + teta_step) * cos(phi);
                    y1 = sin(teta + teta_step) * sin(phi);
                    z1 = cos(teta + teta_step);
                    x2 = sin(teta) * cos(phi + phi_step);
                    y2 = sin(teta) * sin(phi + phi_step);
                    z2 = cos(teta);
                    x3 = sin(teta + teta_step) * cos(phi + phi_step);
                    y3 = sin(teta + teta_step) * sin(phi + phi_step);
                    z3 = cos(teta + teta_step);
                    x4 = sin(teta + teta_step) * cos(phi);
                    y4 = sin(teta + teta_step) * sin(phi);
                    z4 = cos(teta + teta_step);
                    glVertex3f(x, y, z);
                    glVertex3f(x1, y1, z1);
                    glVertex3f(x2, y2, z2);
                    glVertex3f(x3, y3, z3);
                    glVertex3f(x4, y4, z4);
                    // glNormal3f(x, y, z);
                    // glNormal3f(x1, y1, z1);
                    // glNormal3f(x2, y2, z2);
                    // glNormal3f(x3, y3, z3);
                    // glNormal3f(x4, y4, z4);
                }
                glEnd();
            }
        }
};

#endif