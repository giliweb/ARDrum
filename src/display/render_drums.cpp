
//�v���W�F�N�g�̃v���p�e�B��C/C++�ˑS�ʁ@�̒ǉ��̃C���N���[�h�f�B���N�g����
// opencv2�̂���t�H���_�wC:\OpenCV\include�x�Ȃǂ�ǉ��̂���
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

#include <GL/gl.h>

#include <GL/glut.h> // for glutSolidCube()

#include <iostream>
#include "XLoader.h"
#include "Mouse.h"
using namespace std;

//
// Global Variable
//
int WindowPositionX = 100;
int WindowPositionY = 100;
int WindowWidth = 512;
int WindowHeight = 512;
char WindowTitle[] = "���@X�t�@�C���̓ǂݍ��݁@��";
char Version[50];
char Vender[50];
char Renderer[50];
char FpsString[50] = {0};
double CurrentTime = 0.0;
double LastTime = 0.0;
double CurrentCount = 0.0;
double LastCount = 0.0;
int FrameCount = 0;
float Fps = 0.0f;
XModel model;
ViewCamera camera;

//
// Forward declarations
//
void Render3D();



// OpenGL�̂��߂̃t�H�[�}�b�g�w��

static PIXELFORMATDESCRIPTOR pfd = {

  sizeof (PIXELFORMATDESCRIPTOR),

  1,

  PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,

  PFD_TYPE_RGBA,

  24,

  0, 0, 0,

  0, 0, 0,

  0, 0,

  0, 0, 0, 0, 0,

  32,

  0,

  0,

  PFD_MAIN_PLANE,

  0,

  0,

  0,

  0

};

  

int main( int argc, char *argv[] )

{

  CvCapture *capture=NULL;

  IplImage *frameImage=NULL, *copyImage=NULL, *outputImage=NULL;

  // ���f���t�@�C���̓ǂݍ���
  model.Load("Models/dosei.x");

  int key;

  int count=0;

  HWND hwnd;

  HDC hdc;

  HGLRC hglrc;

  int pfdID;

  GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};

  GLfloat light_position[] = {3.0, 3.0, 3.0, 0.0};

  

  capture = cvCreateCameraCapture( -1 );

  

  frameImage = cvQueryFrame( capture ); // �J�����摜�̎擾

  cvNamedWindow( "OpenCV", CV_WINDOW_AUTOSIZE ); // �E�C���h�E�쐬

  cvResizeWindow( "OpenCV", frameImage->width, frameImage->height );

  // �摜�o�b�t�@�쐬

  copyImage = cvCreateImage( cvSize(frameImage->width, frameImage->height), 8, 4 ); // RGBA ��4�o�C�g

  outputImage = cvCreateImage( cvSize(frameImage->width, frameImage->height), 8, 3 ); // BGR ��3�o�C�g

  

  hwnd = (HWND)cvGetWindowHandle( "OpenCV" ); // �E�C���h�E�n���h�����擾

  hdc = GetDC(hwnd); // �f�o�C�X�R���e�L�X�g���擾

  pfdID = ChoosePixelFormat(hdc, &pfd);

  SetPixelFormat(hdc, pfdID, &pfd); // �f�o�C�X�R���e�L�X�g�Ƀs�N�Z���t�H�[�}�b�g��ݒ�

  hglrc = wglCreateContext(hdc); // OpenGL�p�̃R���e�L�X�g���쐬

  wglMakeCurrent(hdc, hglrc); // ��������OpwnGL�R�}���h���L���ɂȂ�

 
  

  // �����ݒ�

  //glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

  //glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  //glEnable(GL_LIGHTING);

  //glEnable(GL_LIGHT0);

  // �A�ʏ�����L����

  glEnable(GL_DEPTH_TEST);

  

  while( 1 ) {

    frameImage = cvQueryFrame( capture );

    cvCvtColor(frameImage, copyImage, CV_BGR2RGBA ); // OpenGL�p�ɉ�f�̕��т�ϊ�

    cvFlip( copyImage, copyImage, 0 ); // OpenGL�̌��_�ɍ��킹�ď㉺���]

	//�@�o�b�N�o�b�t�@���N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//�@���f���r���[�s��̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


    // OpenCV �̉摜�f�[�^��`��

    glDrawPixels( copyImage->width, copyImage->height, GL_RGBA, GL_UNSIGNED_BYTE, copyImage->imageData ); //�L���v�`�������摜��w�i�Ƃ��ĕ`��

  

    glClear( GL_DEPTH_BUFFER_BIT ); // �f�v�X�o�b�t�@�݂̂��N���A

  
	glOrtho( -4.0, 4.0, -3.0, 3.0, -5.0, 5.0 ); // �Ƃ肠���� ��:�c=4:3 �Ő��ˉe

  

	//�@���_�̐ݒ�
	camera.SetParams();

	camera.Set();
  

	//
	glPushMatrix();
	
	//�@3D�V�[���̕`��
	Render3D();	

	//�@2D�V�[���̕`��
	//Render2D();

	//
	glPopMatrix();

	//�@�_�u���o�b�t�@
	//glutSwapBuffers();



    // OpenGL�o�b�t�@�̓��e���摜�Ƃ��Ď擾

    glReadPixels( 0, 0, outputImage->width, outputImage->height, GL_RGB, GL_UNSIGNED_BYTE, outputImage->imageData ); // RGB�Ŏ擾

    cvCvtColor( outputImage, outputImage, CV_RGB2BGR ); // OpenCV��BGR���тɕϊ�

    cvFlip( outputImage, outputImage, 0 ); // OpenCV �ɍ��킹�ď㉺���]

  

    cvShowImage( "OpenCV", outputImage ); // �摜�\��

  

    key = cvWaitKey(10);

    if( key == 27 ){

      break;

    }

  }

  

  wglMakeCurrent(hdc, 0);

  wglDeleteContext(hglrc);

  ReleaseDC(hwnd, hdc);

  cvReleaseImage( &copyImage );
  cvReleaseImage( &outputImage );

  cvDestroyWindow( "OpenCV" );

  cvReleaseCapture( &capture );

  

  return 0;

}





//--------------------------------------------------------------------------------------------------
// Name : Render3D()
// Desc : 3�����V�[���̕`��
//--------------------------------------------------------------------------------------------------
void Render3D()
{
	//�@���f���̕`��
	float scale = 1.0f/model.sphere.radius;	//�@�g��W��
	model.Render(scale);	//�@�`��
}

