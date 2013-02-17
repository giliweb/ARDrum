#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "GLMetaseq.h"

struct Model{
	MQO_MODEL mqo;
	int state;
};

void renderModel(Model &model, float x, float y, float z, float a){


	glPushMatrix();
	glLoadIdentity();
	
	if( model.state == 0 ){

		glTranslatef(x, y, z);						// ���s�ړ��i���A�c�A���s���j
		glRotatef( 45/180.0 * 3.14, 0, 1, 0 );		// Y����]
		glRotatef( a, 1, 0, 0 );					// X����]
		glScalef( 0.5f, 0.5f, 0.5f );

		mqoCallModel(model.mqo);						// MQO���f���̃R�[��
		glPopMatrix();	
	}
	else{




	}
	

}

