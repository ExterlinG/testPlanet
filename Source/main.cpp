#include <DxLib.h>
#include "App.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(1920, 1080, 32);
	SetOutApplicationLogValidFlag(FALSE); // ���O���o���Ȃ�
#if _DEBUG // �f�o�b�O�r���h�̂Ƃ�����
	SetMainWindowText("�f�o�b�O�E�B���h�E");
	SetWindowSizeExtendRate(1.0);
	ChangeWindowMode(TRUE); // Window���[�h�̏ꍇ
#endif
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);
	AppInit();	//������
	int mStartTime = GetNowCount();
	while (ProcessMessage() >= 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 ) {
		int cur = GetNowCount();
		if (cur < mStartTime + 16) //120fps�΍�
			continue;
		mStartTime = cur;
		AppUpdate();	//����
		ClearDrawScreen();
		AppDraw();	//�`��
		ScreenFlip();
	}
	AppRelease();
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
} 