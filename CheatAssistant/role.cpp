#include "pch.h"
#include "role.h"
#include "function.h"
#include "status_3.h"


int role::getRoleLevel()
{
	return memory.read<int>(__��ɫ�ȼ�);
}
std::wstring role::getRoleJobName()
{
	return memory.readWString(memory.read<DWORD>(__ְҵ����) + 0x0, 100);
}
int role::getCurrentRoleFatigueValue()
{
	return fun::decrypt(__���ƣ��) - fun::decrypt(__��ǰƣ��);
}
ROLE_POS role::getRolePos()
{
	ROLE_POS RolePos;
	RolePos.room = fun::getCurrentRoomPos();
	RolePos.x = (int)memory.read<float>(__��ɫ����);
	RolePos.y = (int)memory.read<float>(__��ɫ���� + 4);
	RolePos.z = (int)memory.read<float>(__��ɫ���� + 8);
	return RolePos;
}
int role::getRoleStatus()
{
	return memory.read<int>(memory.read<int>(__��ɫ״̬) + __��ɫ״̬ƫ��);
}
// ȥ��ɫ���� 0-�� 1-��
int role::getRoleFacing() {
	if (memory.read<int>(memory.read<int>(__��ɫ״̬) + __��ɫ����ƫ��1) == 1 || memory.read<int>(memory.read<int>(__��ɫ״̬) + __��ɫ����ƫ��2) == 1) {
		return 1;
	}
	return 0;
}
void role::releaseSkillByKey(int keyCode, int s)
{
	if (fun::isOpenDoor() == false && status_3::getMonsterCount() > 0)
	{
		key.doKeyPress(keyCode, s);
		Sleep(100);
		// �ͷż��ܵ���ʱ
		while (getRoleStatus() != 0)
		{
			Sleep(100);
		}
		Sleep(300);
	}
}

void role::moveRoleToPos_����(ROLE_POS targetPos)
{
	
}

void role::moveRoleToPos_��ͼ(ROLE_POS targetPos)
{

}

void role::moveRoleToPos_����(ROLE_POS targetPos)
{
	ROLE_POS currentPos = getRolePos();
	std::vector<int> directionArray = moveRoleToPos_���㷽��(currentPos, targetPos);
	if (directionArray[0] == 1)
	{
		key.keyDown(VK_NUMPAD1);
	}
	if (directionArray[1] == 1)
	{
		key.keyDown(VK_NUMPAD3);
	}
	if (directionArray[2] == 1)
	{
		key.keyDown(VK_NUMPAD5);
	}
	if (directionArray[3] == 1)
	{
		key.keyDown(VK_NUMPAD2);
	}
}

void role::moveRoleToPos_���(ROLE_POS targetPos)
{

}
// 0-�� 1-�� 2-�� 3-�� 
std::vector<int> role::moveRoleToPos_���㷽��(ROLE_POS currentPos,ROLE_POS targetPos)
{
	std::vector<int> directionArray = {0,0,0,0};
	if (abs(currentPos.x - targetPos.x) > 50)
	{
		if (currentPos.x > targetPos.x)
		{
			directionArray[0] = 1;
		}
		else
		{
			directionArray[1] = 1;
		}
	}
	if (abs(currentPos.y - targetPos.y) > 20)
	{
		if (currentPos.y > targetPos.y)
		{
			directionArray[2] = 1;
		}
		else
		{
			directionArray[3] = 1;
		}
	}
	return directionArray;
}

void role::moveRoleToPos_���㴦��(ROLE_POS targetPos, std::map<const char*, bool> &cardPointList)
{
	ROLE_POS currentPos = getRolePos();
}


void role::moveRoleToPos(ROLE_POS targetPos,int type)
{
	// ʱ�����
	int t1, t2 = (int)utils::getTime();
	// ��Ϸ״̬
	int gameStatus = fun::getGameStatus();
	//utils::myprintf("gameStatus->%d", GREEN, gameStatus);
	// �����б�
	//std::map<const char*,bool> cardPointList;
	// λ�ñ���
	ROLE_POS currentPos, cardPointPos = getRolePos();
	//utils::myprintf("Ŀ��λ�� ����x->:%d,����y->:%d | x->:%d,y->:%d", RED, targetPos.room.x, targetPos.room.y, targetPos.x, targetPos.y);
	while (true)
	{
		currentPos = getRolePos();
		t1 = utils::getTime();
		//utils::myprintf("��ǰλ�� ����x->:%d,����y->:%d | x->:%d,y->:%d", YELLOW, currentPos.room.x, currentPos.room.y, currentPos.x, currentPos.y);
		if (
			currentPos.room.x != targetPos.room.x ||
			currentPos.room.y != targetPos.room.y ||
			(abs(currentPos.x - targetPos.x) < 50 && abs(currentPos.y - targetPos.y) < 30)
			)
		{
			key.upAllKey();//��ԭ���а���
			//utils::myprintf("�ɹ�����ָ��λ��");
			break;
		}

		if ((currentPos.y - targetPos.y) >= 30 && key.getKeyState(VK_NUMPAD5) == 0)
		{
			key.keyDown(VK_NUMPAD5);
		}

		if ((targetPos.y - currentPos.y) >= 30 && key.getKeyState(VK_NUMPAD2) == 0)
		{
			key.keyDown(VK_NUMPAD2);
		}

		if ((currentPos.x - targetPos.x) >= 50 && key.getKeyState(VK_NUMPAD1) == 0)
		{
			//printf("��\n");
			if (gameStatus == 3)
			{
				key.keyDown(VK_NUMPAD1);
				Sleep(100);
				key.keyUp(VK_NUMPAD1);
				Sleep(100);
				key.keyDown(VK_NUMPAD1);
			}
			else {
				key.keyDown(VK_NUMPAD1);
			}
		}

		if ((targetPos.x - currentPos.x) >= 50 && key.getKeyState(VK_NUMPAD3) == 0)
		{
			//printf("��\n");
			if (gameStatus == 3)
			{
				key.keyDown(VK_NUMPAD3);
				Sleep(100);
				key.keyUp(VK_NUMPAD3);
				Sleep(100);
				key.keyDown(VK_NUMPAD3);
			}
			else {
				key.keyDown(VK_NUMPAD3);
			}
		}




		if (abs(currentPos.y - targetPos.y) < 30)
		{
			if (key.getKeyState(VK_NUMPAD5) == 1) {
				key.keyUp(VK_NUMPAD5);
				//utils::myprintf("keyUp ��");
			}
			if (key.getKeyState(VK_NUMPAD2) == 1)
			{
				key.keyUp(VK_NUMPAD2);
				//utils::myprintf("keyUp ��");
			}

		}

		if (abs(currentPos.x - targetPos.x) < 50)
		{
			if (key.getKeyState(VK_NUMPAD1) == 1) {
				key.keyUp(VK_NUMPAD1);
			}
			if (key.getKeyState(VK_NUMPAD3) == 1)
			{
				key.keyUp(VK_NUMPAD3);
			}
			//utils::myprintf("keyUp ����");
		}

		// ���㴦��
		/*if (abs((int)t1 - (int)t2) > 3)
		{
			t2 = utils::getTime();
			if (
				abs(currentPos.x - cardPointPos.x) < 3 &&
				abs(currentPos.y - cardPointPos.y) < 3
				)
			{

				if (key.getKeyState(VK_NUMPAD1) == 1)
				{
					key.keyUp(VK_NUMPAD1);
					key.doKeyPress(VK_NUMPAD3, 500);
				}

				if (key.getKeyState(VK_NUMPAD2) == 1)
				{
					key.keyUp(VK_NUMPAD2);
					key.doKeyPress(VK_NUMPAD5, 500);
				}

				if (key.getKeyState(VK_NUMPAD3) == 1)
				{
					key.keyUp(VK_NUMPAD3);
					key.doKeyPress(VK_NUMPAD1, 500);
				}

				if (key.getKeyState(VK_NUMPAD5) == 1)
				{
					key.keyUp(VK_NUMPAD5);
					key.doKeyPress(VK_NUMPAD2, 500);
				}
			}
			cardPointPos = getRolePos();
		}*/
	}
}

// ȡ��ɫ�ƶ��ٶȵ�λ�루��
int role::getRoleMoveSpeed()
{
	return 123;
}

void role::moveRoleToPos2(ROLE_POS targetPos, int type) 
{
	// ��ǰλ��
	ROLE_POS currentPos = getRolePos();
	// ����
	int xD = abs(targetPos.x - currentPos.x);
	int yD = abs(targetPos.y - currentPos.y);
	// �ƶ��ٶ�
	int xMS = 300;
	int yMS = 50;
	// �ƶ���Ŀ��λ������Ҫ��ʱ��(����)
	int xT = int(xD / xMS) * 1000;
	int yT = int(yD / yMS) * 1000;

	// ������
	if (targetPos.x > currentPos.x)
	{
		key.doKeyPress(VK_NUMPAD3, xT);
	}
	// ������
	if (targetPos.x < currentPos.x)
	{
		key.doKeyPress(VK_NUMPAD1, xT);
	}
	// ������
	if (targetPos.y > currentPos.y)
	{
		key.doKeyPress(VK_NUMPAD5, yT);
	}
	// ������
	if (targetPos.y < currentPos.y)
	{
		key.doKeyPress(VK_NUMPAD2, yT);
	}
}


void role::ignoreBuild(bool enbale) {
	if (enbale == true)
	{
		memory.writeOffset(__�����ַ, { __���ӽ���ƫ�� }, 0);
		utils::myprintf(VMProtectDecryptStringA("���ӽ����ѿ���"));
	}
	else {
		memory.writeOffset(__�����ַ, { __���ӽ���ƫ�� }, 40);
		utils::myprintf(VMProtectDecryptStringA("���ӽ����ѹر�"));
	}
}

void role::ignoreTerrain(bool enbale) {
	if (enbale == true)
	{
		memory.writeOffset(__�����ַ, { __���ӵ���ƫ�� }, 0);
		utils::myprintf(VMProtectDecryptStringA("���ӵ����ѿ���"));
	}
	else {
		memory.writeOffset(__�����ַ, { __���ӵ���ƫ�� }, 10);
		utils::myprintf(VMProtectDecryptStringA("���ӵ����ѿ���"));
	}
}