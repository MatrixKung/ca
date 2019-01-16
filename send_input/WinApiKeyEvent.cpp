#include "WinApiKeyEvent.h"

// IsKeyPressed(nVirtKey)��������ֵΪTRUE�����ʾ�������£���֮��ʾ��������
#define  IsKeyPressed(nVirtKey)((GetKeyState(nVirtKey) & (1<<(sizeof(SHORT)*8-1))) != 0);

// IsKeyToggled(nVirtKey)��������ֵΪTRUE��ʾ���������л�״̬�����ƣ�����ֵΪFALSE����ʾ�������ڷ��л�״̬����ơ�
#define IsKeyToggled(nVirtKey)  ((GetKeyState(nVirtKey) & 1) != 0);


WinApiKeyEvent::WinApiKeyEvent()
{
}


WinApiKeyEvent::~WinApiKeyEvent()
{
}

WORD WinApiKeyEvent::getSCan(int keyCode)
{
	WORD sCan = MapVirtualKey(keyCode, 0);
	if (
		keyCode == VK_LEFT ||
		keyCode == VK_RIGHT ||
		keyCode == VK_DOWN ||
		keyCode == VK_UP
		)
	{
		sCan += 0x80;
	}
	return sCan;
}

bool WinApiKeyEvent::getKeyState(int keyCode) 
{
	return IsKeyPressed(keyCode);
}

void WinApiKeyEvent::keyDown(int keyCode,int s)
{
	if (getKeyState(keyCode) == false) {
		INPUT input[1];
		memset(input, 0, sizeof(input));
		input[0].type = INPUT_KEYBOARD;
		input[0].ki.wVk = keyCode;
		input[0].ki.wScan = MapVirtualKey(keyCode, 0);
		input[0].ki.dwFlags = 0;
		SendInput(sizeof(input) / sizeof(INPUT), input, sizeof(INPUT));
	}
	
}

void WinApiKeyEvent::keyUp(int keyCode)
{
	if (getKeyState(keyCode) == true) {
		INPUT input[1];
		memset(input, 0, sizeof(input));
		input[0].type = INPUT_KEYBOARD;
		input[0].ki.wVk = keyCode;
		input[0].ki.wScan = MapVirtualKey(keyCode, 0);
		input[0].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(sizeof(input) / sizeof(INPUT), input, sizeof(INPUT));
	}
}

void WinApiKeyEvent::doKeyPress(int keyCode,int s)
{
	keyDown(keyCode);
	keyUp(keyCode);
}