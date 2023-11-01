#ifndef SKYSCRAPPER_H
#define SKYSCRAPPER_H

#include "ofMain.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"

class Skyscraper {
    public:
        
        GLfloat width, height, depth;
        GLfloat R, G, B;
        GLfloat posGridX, posGridY, posGridZ;
        int mesh;

        Skyscraper(GLfloat width, GLfloat height, GLfloat depth, GLfloat R, GLfloat G, GLfloat B, GLfloat posGridX, GLfloat posGridY, GLfloat posGridZ, int mesh) {
            this->width = width;
            this->height = height;
            this->depth = depth;
            this->R = R;
            this->G = G;
            this->B = B;
            this->posGridX = posGridX;
            this->posGridY = posGridY;
            this->posGridZ = posGridZ;
            this->mesh = mesh;
        }

        void draw(int special) { //TODO posicionamento especial????
            glPushMatrix();//base push
            glTranslatef(posGridX, posGridY, depth*0.5);
            glColor3f(R, G, B);
            if(special)
                glScalef(width++, height++, depth++);
            else 
                glScalef(width, height, depth);
            cube_unit();
            glPopMatrix();//base pop
        }

        void draw1() { //TODO should i be drawing bottom ??
            glPushMatrix();//base push
            glTranslatef(posGridX, posGridY, depth*0.5);
            glColor3f(R, G, B);
            glScalef(width, height, depth);
            cube_mesh_unit(mesh,mesh);
            glPopMatrix();//base pop
            if(depth > gh()*0.10){
                glPushMatrix();//base push
                glTranslatef(posGridX, posGridY, depth+depth*0.05/4);
                glColor3f(R, G, B);
                glScalef(width*0.8, height*0.8, depth*0.05/2);
                cube_mesh_unit(mesh,mesh);
                glPopMatrix();//base pop
            }
        }
};

#endif