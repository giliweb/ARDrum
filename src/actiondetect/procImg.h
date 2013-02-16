#ifndef PROCIMG_H
#define PROCIMG_H

using namespace cv;

struct iVec2{
	int x, y;
};

class Detector{
	int w, h;	// �摜�T�C�Y
	float f;	// �œ_

	Mat *srcRGB;	//���͉摜�̃|�C���^
	Mat srcGray;	//���͉摜�̃O���[
	Mat preGray;	//��O�̃O���[

	//�����}�b�v�̍��W���q�X�g�O���� 2�F
	int *histH[2], *histW[2];	
	int detectStart[2];

	int kernelSize; // ���x����p�̃J�[�l���T�C�Y
	int *kernel;	// ���x����p�̃J�[�l��(�w���֐�)

	// ���o�����X�e�B�b�N�̏��
	struct PosBuff{
		iVec2 pos;
		bool detect;
	};

	PosBuff posBuff[2][3];
	int lastPos[2];

public:
	// �f�o�b�O�p�Ɉꎞ public
	Mat diffMask;	//�P�x�����}�b�v
	Mat dstCol[2];	//�@�F�����}�b�v

	Detector( int w, int h, float f ){
		this->w = w, this->h = h;

		// �z��m��
		srcGray  = Mat(Size(w, h),CV_8UC1); 
		preGray  = Mat(Size(w, h),CV_8UC1);
		diffMask = Mat(Size(w, h),CV_8UC1);


		
		{
			for( int i = 0; i < 2; i++ ){
				detectStart[i] = true;
				dstCol[i] = Mat(Size(w, h), CV_8UC1);
				lastPos[i] = 0;
				memset( &posBuff[i], 0, 3 * sizeof(PosBuff) );
			}
		}
		{// ���x����p
			for( int i = 0; i < 2; i++ ){
				histH[i] = new int[h];
				histW[i] = new int[w];
			}

			kernelSize = 20;
			kernel = new int[kernelSize+1];
			for(int i = 0 ; i < kernelSize + 1; i++ ){
				kernel[i] = (int)(20 * exp((double)(-i*0.2)) + 0.5);
			}
		}
	}

	~Detector(){
		for( int i = 0; i < 2; i++ ){
			delete []histH[i];
			delete []histW[i];
		}
		delete []kernel;
	}

	void init( Mat &frame ){
		srcRGB = &frame;

		// ������
		GaussianBlur( *srcRGB, *srcRGB, Size(5,5), 3 );

		// RGB��GRAY
		cvtColor( *srcRGB, srcGray, CV_BGR2GRAY );
	}

	// �X�e�B�b�N�̃A�N�V�������o
	void detectAction( vector<iVec2> &act );
};

#endif