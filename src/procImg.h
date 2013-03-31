#ifndef PROCIMG_H
#define PROCIMG_H
#include "Labeling.h"

using namespace cv;

struct iVec2{
	int x, y;
};
struct fVec3{
	float x, y, z;
};


struct Vec2{
	int x,y;
	void set(int _x, int _y){ x = _x; y = _y; };
	Vec2(){ x = 0; y = 0;};
	~Vec2(){}
};

struct Vec3{
	float x, y, z;
	Vec3(){ x=0; y = 0; };
	~Vec3(){}
};

struct Marker{
	iVec2 center;
	Vec3 pos;
	double angle;
	int size_x, size_y;
	void calcZ(float f, int w, int h){
		pos.z = 100.0 * f / size_x; 
		pos.x = (center.x - w/2) * pos.z / f;
		pos.y = (h/2 - center.y) * pos.z / f;
	};
	void setCenter(iVec2 center3){
		center = center3;
	};
	void setCenter(Vec2 center2){
		center.x = center2.x;
		center.y = center2.y;
	};
	void calcAngle(int _size_x, int _size_y){
		size_x = _size_x;
		size_y = _size_y;
		if(size_x < size_y)
			size_y = size_x;
		double cos = (double)size_y/(double)size_x;
		angle = acos(cos);
	};
};
struct MarkerCand : public Marker{
	Vec2 minNode, maxNode;
};


class Detector{
	int w, h;	// �摜�T�C�Y
	float f;	// �œ_

	Mat *srcRGB;	//���͉摜�̃|�C���^
	Mat srcGray;	//���͉摜�̃O���[
	Mat preGray;	//��O�̃O���[
    Mat srcBW;      //���͉摜�̔���

	//�����}�b�v�̍��W���q�X�g�O���� 2�F
	int *histH[2], *histW[2];	
	int detectStart[2];

	int kernelSize; // ���x����p�̃J�[�l���T�C�Y
	int *kernel;	// ���x����p�̃J�[�l��(�w���֐�)
	int kernelSum;

	// ���o�����X�e�B�b�N�̏��
	struct PosBuff{
		iVec2 pos;
		bool detect;
	};

	PosBuff posBuff[2][3];
	int lastPos[2];
	int valMax[2];


public:
	// �f�o�b�O�p�Ɉꎞ public
	Mat diffMask;	//�P�x�����}�b�v
	Mat dstCol[2];	//�@�F�����}�b�v
	vector<Marker> m_marker;
	vector<MarkerCand> markerCands;

	Mat debug1, debug2;

	Detector( int w, int h, float f );

	~Detector();

	void init( Mat &frame );

	// �X�e�B�b�N�̃A�N�V�������o
	void detectAction( vector<iVec2> &act );

	    // �}�[�J���o
	void getMarkerPos(/*vector<Vec3> &posList*/);
    void selectMarkerCand( vector<MarkerCand> &markerCands, vector<Marker> &markers, LabelingBS &labelingBs);
    void getMarker( vector<Marker> &markers );
};

#endif



