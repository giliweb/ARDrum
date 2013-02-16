#include "common.h"
#include "procImg.h"

int main(){

	Drum * drum = new Drum();
	
	VideoCapture cap(2);
	if(!cap.isOpened()) return -1;

	char *wName = "test";
	namedWindow( wName );

	//�L�[���͗p
	int toggle = 1;
	int key = 0;

	Mat frame;
	cap >> frame;


	// �����ݒ� 
	Detector detector(frame.cols, frame.rows, 1000.0);


	int saveFlag = -1;
	int loadFlag = -1;

	//loadFlag = 0;
	while( key != 'q' ){
		// �L���v�`��
		if( loadFlag < 0 ){
			cap >> frame;
		}
		else{
			char str[256];
			sprintf( str, "view%03d.bmp", loadFlag );
			frame = imread( str );
			loadFlag++;
			if( loadFlag > 160 ){
				loadFlag = 0;
			}
			waitKey(20);
		}
		if( saveFlag >= 0 ){
			char str[256];
			sprintf( str, "view%03d.bmp", saveFlag );
			cv::imwrite( str, frame );
			saveFlag++;
		}


		// �摜�ݒ�
		detector.init( frame );

		// �X�e�B�b�N���o
		vector<iVec2> act;
		detector.detectAction( act );

		if(act.size() > 0) {
			drum->tataku(SCRATCH_PUSH);
		}

		Mat *show = toggle ? &frame : &detector.dstCol[0];
		{// ���o���ʕ`��
			for( int i = 0; i < act.size(); i++ ){
				int x = act[i].x, y = act[i].y;
				line( frame, Point(x-15, y) , Point(x+15, y), Scalar(255, 255, 0), 4, CV_AA );
				line( frame, Point(x, y-15) , Point(x, y+15), Scalar(255, 255, 0), 4, CV_AA );
				circle( *show, Point(x, y), 20, Scalar(255, 255, 255), 2 );
			}
		}

		// �摜�\��
		imshow( wName, *show );

		// �L�[����
		key = waitKey(1);
		switch( key ){
			case 't' :{ toggle ^= 1; break;} 
			case 's' :{ if( saveFlag < 0) saveFlag = 0; else saveFlag = -1; break;} 
			case 'l' :{ if( loadFlag < 0) loadFlag = 0; else loadFlag = -1; break;} 
			default  :{ break;}
		}
	}
	return 0;
}