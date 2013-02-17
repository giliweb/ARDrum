#include "opencv2\opencv.hpp"
 
#ifdef _DEBUG
    //Debug���[�h�̏ꍇ
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_core240d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_imgproc240d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_highgui240d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_objdetect240d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_contrib240d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_features2d240d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_flann240d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_gpu240d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_haartraining_engined.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_legacy240d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_ts240d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_video240d.lib")
#else
    //Release���[�h�̏ꍇ
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_core240.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_imgproc240.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_highgui240.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_objdetect240.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_contrib240.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_features2d240.lib")

#pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_flann240.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_gpu240.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_haartraining_engined.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_legacy240.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_ts240.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x86\\vc10\\lib\\opencv_video240.lib")
#endif
 

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "GLMetaseq.h"	// ���f�����[�_


// �O���[�o���ϐ�
int g_mouseX = 0;	// �}�E�XX���W
int g_mouseY = 0;	// �}�E�XY���W
int g_rotX = 10.0f; // X������̉�]
int	g_rotY = 10.0f;		// Y������̉�]

MQO_MODEL g_mqoModel, g_mqoModel2;	// MQO���f��

//CV
CvCapture *capture=NULL;
IplImage *frameImage=NULL;

// �v���g�^�C�v�錾
void mySetLight(void);
void Draw(void);
void Reshape (int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);


// �����̐ݒ���s���֐�
void mySetLight(void)
{
	GLfloat light_diffuse[]  = { 0.9, 0.9, 0.9, 1.0 };	// �g�U���ˌ�
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };	// ���ʔ��ˌ�
	GLfloat light_ambient[]  = { 0.3, 0.3, 0.3, 0.1 };	// ����
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };	// �ʒu�Ǝ��

	// �����̐ݒ�
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  light_diffuse );	 // �g�U���ˌ��̐ݒ�
	glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular ); // ���ʔ��ˌ��̐ݒ�
	glLightfv( GL_LIGHT0, GL_AMBIENT,  light_ambient );	 // �����̐ݒ�
	glLightfv( GL_LIGHT0, GL_POSITION, light_position ); // �ʒu�Ǝ�ނ̐ݒ�

	glShadeModel( GL_SMOOTH );	// �V�F�[�f�B���O�̎�ނ̐ݒ�
	glEnable( GL_LIGHT0 );		// �����̗L����
}


// �`��֐�
void Draw(void)
{
	// �摜�o�b�t�@�쐬
	IplImage *copyImage = cvCreateImage( cvSize(frameImage->width, frameImage->height), 8, 4 ); // RGBA ��4�o�C�g

	frameImage = cvQueryFrame( capture );
    cvCvtColor(frameImage, copyImage, CV_BGR2RGBA ); // OpenGL�p�ɉ�f�̕��т�ϊ�
    cvFlip( copyImage, copyImage, 0 ); // OpenGL�̌��_�ɍ��킹�ď㉺���]

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// ������
	//glClearColor(0.f, 0.f, 0.2f, 1.0);					// �w�i�F
	glMatrixMode(GL_MODELVIEW);

	glEnable( GL_DEPTH_TEST );		// �B�ʏ����̓K�p
	mySetLight();					// �����̐ݒ�
	glEnable( GL_LIGHTING );		// ����ON

	// OpenCV �̉摜�f�[�^��`��
	glDrawPixels( copyImage->width, copyImage->height, GL_RGBA, GL_UNSIGNED_BYTE, copyImage->imageData ); //�L���v�`�������摜��w�i�Ƃ��ĕ`��
	glClear( GL_DEPTH_BUFFER_BIT ); // �f�v�X�o�b�t�@�݂̂��N���A
	cvReleaseImage( &copyImage );

	glPushMatrix();
		glTranslatef(120.0, -100.0, -650.0); // ���s�ړ��i���A�c�A���s���j
		glRotatef( g_rotX, 1, 0, 0 );		 // X����]
		glRotatef( g_rotY, 0, 1, 0 );		 // Y����]
		//glRotatef( 20.0f, 0, 0, 1 );		 // Z����]
		mqoCallModel(g_mqoModel);			 // MQO���f���̃R�[��
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-120.0, -100.0, -650.0); // ���s�ړ��i���A�c�A���s���j
		glRotatef( g_rotX, 1, 0, 0 );		 // X����]
		glRotatef( g_rotY, 0, 1, 0 );		 // Y����]
		//glRotatef( -20.0f, 0, 0, 1 );		 // Z����]
		mqoCallModel(g_mqoModel);			 // MQO���f���̃R�[��
	glPopMatrix();

	glDisable( GL_LIGHTING );
	glDisable( GL_DEPTH_TEST );

	glutSwapBuffers();
}


// �E�B���h�E�ό`���ɌĂ΂��֐�
void Reshape (int w, int h)
{
	double	znear = 10;
	double	fovy = 50;
	double	zfar = 10000;

	// �r���[�|�[�g�ݒ�
	glViewport(0, 0, w, h);

	// �ˉe�ݒ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (double)w/h, znear, zfar);
}


// �L�[�C�x���g�֐�
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 'q':
		case 'Q':
		case 0x1b:
			exit(0);	// �i���̂��ƏI�������֐����Ă΂��j
		default:
			break;
	}
}


// �}�E�X�C�x���g�֐�
void Mouse(int button, int state, int x, int y)
{
	if ( state == GLUT_DOWN ) {
		g_mouseX = x;
		g_mouseY = y;				
	}
}


// �}�E�X�h���b�O�̏����֐�
void Motion(int x, int y)
{
	int xd, yd;

	// �}�E�X�ړ��ʂ̎Z�o
	xd = x - g_mouseX;
	yd = y - g_mouseY;

	// ��]�ʂ̐ݒ�
	g_rotX += yd;
	g_rotY += xd;

	// �}�E�X���W�̍X�V
	g_mouseX = x;
	g_mouseY = y;
}


// �I�������֐�
void Quit(void)
{
	mqoDeleteModel( g_mqoModel );	// ���f���̍폜
	mqoCleanup();					// GLMetaseq�̏I������
}


// main�֐�
int main(int argc, char *argv[])
{
	capture = cvCreateCameraCapture( -1 );
	frameImage = cvQueryFrame( capture ); // �J�����摜�̎擾

	// ������
	glutInit(&argc,argv);										// OpenGL������
	glutInitWindowPosition(100, 50);							// �E�B���h�E�̕\���ʒu
	glutInitWindowSize(640, 480);								// �E�B���h�E�̃T�C�Y
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// �f�B�X�v���C�ݒ�
	glutCreateWindow("MQO Loader for OpenGL");					// �E�B���h�E�̐���

	// ���f����\�������鏀��
	mqoInit();											// GLMetaseq�̏�����
	g_mqoModel = mqoCreateModel("drum.mqo",1.0);		// ���f���̃��[�h
	g_mqoModel2 = mqoCreateModel("drum.mqo",1.0);		// ���f���̃��[�h

	// �I�������֐��̐ݒ�
	atexit(Quit);

	// �R�[���o�b�N�֐��̐ݒ�
	glutDisplayFunc(Draw);			// �`�揈���֐��̐ݒ�
	glutIdleFunc(Draw);				// �A�C�h�����̏����֐��̐ݒ�
	glutReshapeFunc(Reshape);		// �E�B���h�E�ό`���̏������s���֐��̐ݒ�
	glutKeyboardFunc(Keyboard);		// �L�[���͎��̏����֐��̐ݒ�
	glutMouseFunc(Mouse);			// �}�E�X���͎��̏����֐��̐ݒ�
	glutMotionFunc(Motion);			// �}�E�X�h���b�O���̏����֐��̐ݒ�

	// �C�x���g�҂��̖������[�v�ɓ���
	glutMainLoop();

    // OpenCV��Еt��
    cvReleaseCapture( &capture );

	return 0;
}
