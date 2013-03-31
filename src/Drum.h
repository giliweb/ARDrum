
#ifndef _INC_DRUM    //�܂��ǂݍ��܂�Ă��Ȃ���Έȉ��̏���������
#define _INC_DRUM    //���łɓǂݍ��܂�Ă���Ƃ����ڈ������

#include <MIDIIO.h>
#include "tone.h"


class Drum
{
public:
	Drum(void);
	Drum(MIDIOut*);
	~Drum(void);
	void tataku(tone);
	void tataku(tone, int);
	void send(char, char, char);
private:
	MIDIOut* pMIDIOut;

};

#endif