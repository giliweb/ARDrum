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


struct Model{
	MQO_MODEL mqo;
	int state;
	Model(){
		state = 0;
	}
};

Model drumModel, cymbalModel;	// MQO���f��

//CV
CvCapture *capture=NULL;
IplImage *frameImage=NULL;

// �v���g�^�C�v�錾
void mySetLight(void);
void Draw(void);
void Reshape (int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Quit(void);
void renderModel(Model &model, float x, float y, float z, float a);

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
	
	glMatrixMode(GL_MODELVIEW);

	glEnable( GL_DEPTH_TEST );		// �B�ʏ����̓K�p
	mySetLight();					// �����̐ݒ�
	glEnable( GL_LIGHTING );		// ����ON

	// OpenCV �̉摜�f�[�^��`��i�L���v�`�������摜��w�i�Ƃ��ĕ`��j
	glDrawPixels( copyImage->width, copyImage->height, GL_RGBA, GL_UNSIGNED_BYTE, copyImage->imageData );
	glClear( GL_DEPTH_BUFFER_BIT ); // �f�v�X�o�b�t�@�݂̂��N���A


	{
		// detect marker

		// detect action





		// out sound




	}


	{// renderModel
		//if(aciont)
		{
			//g_mqoModel.state = 20;

		}
		renderModel( drumModel,   -160, -100, -400, 10 );
		renderModel( drumModel,    -80, -100, -400, 10 );
		renderModel( drumModel,     80, -100, -400, 10 );
		renderModel( drumModel,    160, -100, -400, 10 );
		renderModel( cymbalModel, -200,    0, -400, 10 );
		renderModel( cymbalModel,  200,    0, -400, 10 );
	}

	glutSwapBuffers();
	cvReleaseImage( &copyImage );
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
	drumModel.mqo = mqoCreateModel("drum.mqo",1.0);		// ���f���̃��[�h
	cymbalModel.mqo = mqoCreateModel("cymbal.mqo",1.0);		// ���f���̃��[�h

	// �I�������֐��̐ݒ�
	atexit(Quit);

	// �R�[���o�b�N�֐��̐ݒ�
	glutDisplayFunc(Draw);			// �`�揈���֐��̐ݒ�
	glutIdleFunc(Draw);				// �A�C�h�����̏����֐��̐ݒ�
	glutReshapeFunc(Reshape);		// �E�B���h�E�ό`���̏������s���֐��̐ݒ�
	glutKeyboardFunc(Keyboard);		// �L�[���͎��̏����֐��̐ݒ�

	// �C�x���g�҂��̖������[�v�ɓ���
	glutMainLoop();

    // OpenCV��Еt��
    cvReleaseCapture( &capture );

	return 0;
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


// �I�������֐�
void Quit(void)
{
	mqoDeleteModel( drumModel.mqo );	// ���f���̍폜
	mqoDeleteModel( cymbalModel.mqo );	// ���f���̍폜
	mqoCleanup();					// GLMetaseq�̏I������
}
