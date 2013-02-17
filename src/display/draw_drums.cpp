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

int actFlg[6];
Model drumL2Model, drumL1Model, drumR1Model, drumR2Model, cymbalLModel, cymbalRModel, drumActModel, cymbalActModel;	// MQO���f��

//CV
CvCapture *capture=NULL;
IplImage *frameImage=NULL;

// �v���g�^�C�v�錾
void mySetLight(void);
void Draw(void);
void Reshape (int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Quit(void);
void renderModel(Model &model, Model &actModel, float x, float y, float z, float a, int actFlg);

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
			// vector<int> act;
			// int num = act.size();
			// int id1 = act[0]; // �������ꂽ���f����ID


		// out sound

		
	}

	{// renderModel

		// ���f���̕\���ʒu{ x, y, z, a }
		// ���ߑł��ŏ����Ă邪���ۂ͂��̍��W�Ɗp�x���}�[�J�[�Ŏ擾�������̂ɂ���I
		float sym_l[]   = {-200,    0, -500, 10};
		float drum_l2[] = {-150, -100, -450, 10};
		float drum_l1[] = { -50, -100, -400, 10};
		float drum_r1[] = {  50, -100, -400, 10};
		float drum_r2[] = { 150, -100, -450, 10};
		float sym_r[]   = { 200,    0, -500, 10};

		// �@���ꂽ���f����actFlg��1�ɂ��ēn���i�����w��j
		renderModel( cymbalLModel, cymbalActModel, sym_l[0],   sym_l[1],   sym_l[2],   sym_l[3], actFlg[0] );
		renderModel( drumL2Model,  drumActModel, drum_l2[0], drum_l2[1], drum_l2[2], drum_l2[3], actFlg[1] );
		renderModel( drumL1Model,  drumActModel, drum_l1[0], drum_l1[1], drum_l1[2], drum_l1[3], actFlg[2] );
		renderModel( drumR1Model,  drumActModel, drum_r1[0], drum_r1[1], drum_r1[2], drum_r1[3], actFlg[3] );
		renderModel( drumR2Model,  drumActModel, drum_r2[0], drum_r2[1], drum_r2[2], drum_r2[3], actFlg[4] );
		renderModel( cymbalRModel, cymbalActModel, sym_r[0],   sym_r[1],   sym_r[2],   sym_r[3], actFlg[5] );
	
		for(int i=0;i<6; i++) actFlg[i] = 0;

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
	mqoInit();						// GLMetaseq�̏�����
	// ���f���̃��[�h
	drumL2Model.mqo = mqoCreateModel("drum.mqo",1.0);
	drumL1Model.mqo = mqoCreateModel("drum.mqo",1.0);
	drumR1Model.mqo = mqoCreateModel("drum.mqo",1.0);
	drumR2Model.mqo = mqoCreateModel("drum.mqo",1.0);
	drumActModel.mqo = mqoCreateModel("drumAct.mqo",1.0);
	cymbalLModel.mqo = mqoCreateModel("cymbal.mqo",1.0);
	cymbalRModel.mqo = mqoCreateModel("cymbal.mqo",1.0);	
	cymbalActModel.mqo = mqoCreateModel("cymbalAct.mqo",1.0);	

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
		case 'a': actFlg[0]=1; break;
		case 's': actFlg[1]=1; break;
		case 'd': actFlg[2]=1; break;
		case 'f': actFlg[3]=1; break;
		case 'g': actFlg[4]=1; break;
		case 'h': actFlg[5]=1; break;
		case 'q': actFlg[2]=1; actFlg[5]=1; break;
		case 'Q':
		case 0x1b:
			Quit();	// �i���̂��ƏI�������֐����Ă΂��j
		default:
			break;
	}
}


// �I�������֐�
void Quit(void)
{
	// ���f���̍폜
	mqoDeleteModel( drumL2Model.mqo );
	mqoDeleteModel( drumL1Model.mqo );	
	mqoDeleteModel( drumR1Model.mqo );	
	mqoDeleteModel( drumR2Model.mqo );	
	mqoDeleteModel( drumActModel.mqo );	
	mqoDeleteModel( cymbalLModel.mqo );
	mqoDeleteModel( cymbalRModel.mqo );
	mqoDeleteModel( cymbalActModel.mqo );

	// GLMetaseq�̏I������
	mqoCleanup();					
}
