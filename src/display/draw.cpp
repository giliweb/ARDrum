#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "GLMetaseq.h"

struct Model{
	MQO_MODEL mqo;
	int state;
};


void renderModel(Model &model, Model &actModel, float x, float y, float z, float a, int actFlg){
	// �A�N�V�����������3�t���[���A�N�V�����p�̉摜��\������
	if(actFlg == 1) model.state = 3;

	glPushMatrix();
	
	if( model.state == 0 ){
		// �ʏ펞
		glTranslatef(x, y, z);						// ���s�ړ��i���A�c�A���s���j
		glRotatef( 45/180.0 * 3.14, 0, 1, 0 );		// Y����]
		glRotatef( a, 1, 0, 0 );					// X����]
		glScalef( 0.5f, 0.5f, 0.5f );				// �X�P�[���ϊ�

		mqoCallModel(model.mqo);					// MQO���f���̃R�[��		
	}
	else{
		// �A�N�V�����p
		glTranslatef(x, y-15, z);					// ���s�ړ��i���A�c�A���s���j
		glRotatef( 45/180.0 * 3.14, 0, 1, 0 );		// Y����]
		glRotatef( a, 1, 0, 0 );					// X����]
		glScalef( 0.5f, 0.5f, 0.5f );				// �X�P�[���ϊ�

		mqoCallModel(actModel.mqo);					 // MQO���f���̃R�[��	
	
		if(model.state > 0) model.state--;
	}
	
	glPopMatrix();	
}

