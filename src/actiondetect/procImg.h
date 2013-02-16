#ifndef PROCIMG_H
#define PROCIMG_H

using namespace cv;

struct Vec2{
	int x, y;
};

class Detector{
	int w, h;	// �摜�T�C�Y
	float f;	// �œ_

	Mat *srcRGB;	//���͉摜�̃|�C���^
	Mat srcGray;	//���͉摜�̃O���[
	Mat preGray;	//��O�̃O���[

	//�����}�b�v�̍��W���q�X�g�O���� 2�F
	int *histRedH, *histRedW;	
	int *histBlueH, *histBlueW;

	int kernelSize; // ���x����p�̃J�[�l���T�C�Y
	int *kernel;	// ���x����p�̃J�[�l��(�w���֐�)

	// ���o�����X�e�B�b�N�̏��
	struct PosBuff{
		Vec2 pos;
		bool detect;
	};

	PosBuff posBuffRed[3], posBuffBlue[3];
	int lastPosRed, lastPosBlue;

public:
	// �f�o�b�O�p�Ɉꎞ public
	Mat diffMask;	//�����}�b�v
	Mat dstRed;		//�ԓ����}�b�v
	Mat dstBlue;	//�����}�b�v


	Detector( int w, int h, float f ){
		this->w = w, this->h = h;

		// �z��m��
		srcGray = Mat(Size(w, h),CV_8UC1);
		preGray = Mat(Size(w, h),CV_8UC1);
		diffMask = Mat(Size(w, h),CV_8UC1);
		
		dstRed = Mat(Size(w, h),CV_8UC1);
		dstBlue = Mat(Size(w, h),CV_8UC1);

		{// ���x����p
			histRedH  = new int[h];
			histRedW  = new int[w];
			histBlueH = new int[h];
			histBlueW = new int[w];

			kernelSize = 10;
			kernel = new int[kernelSize];
			for(int i = 0 ; i < 10; i++ ){
				kernel[i] = (int)(20 * exp((double)(-i)) + 0.5);
			}
		}

		lastPosRed = 0;
		memset( &posBuffRed, 0, 3 * sizeof(PosBuff) );
	}

	~Detector(){
		delete []histRedH;
		delete []histRedW;
		delete []kernel;
	}

	void init( Mat &frame ){
		srcRGB = &frame;

		// RGB��GRAY
		cvtColor( *srcRGB, srcGray, CV_BGR2GRAY );

		//������
		GaussianBlur( srcGray, srcGray, Size(5,5), 3 );
	}

	// �X�e�B�b�N�̃A�N�V�������o
	void detectAction( vector<Vec2> &act );
};

#endif