#include "pch.h"
#include "status_2.h"
#include "role.h"
#include "function.h"
#include "call.h"
#include "send_packet.h"

void status_2::manage() {
	if (role::getCurrentRoleFatigueValue() == 0)
	{
		key.doKeyPress(VK_ESCAPE);
		Sleep(1000);
	}
	else {
		if (g_�Զ�ģʽ == ��ש)
		{
			selectCopyByKey(g_�������, g_�����Ѷ�);
		}
		else if (g_�Զ�ģʽ == ��ϰ) {
			SendPacket().ѡ�񸱱�(g_�������, g_�����Ѷ�, g_�Զ�ģʽ, 0);
			while (fun::getGameStatus() != 3 && g_�Զ�����)
			{
				Sleep(1000);
			}
			Sleep(1000);
		}
		else {
			key.doKeyPress(VK_ESCAPE);
			Sleep(1000);
		}
	}
}

void status_2::selectCopyByKey(int ����ID, int �����Ѷ�)
{
	int ��ǰ����ID, ��ǰ�����Ѷ�;
	int flag = true;
	if (fun::passStoryFrame() == false)
	{
		return;
	}
	while (flag && fun::getGameStatus() == 2)
	{
		��ǰ����ID = memory.read<int>(__����ID);
		��ǰ�����Ѷ� = memory.read<int>(memory.read<int>(__�����Ѷ�) + __�����Ѷ�ƫ��);
		Sleep(500);
		if (����ID == ��ǰ����ID && ��ǰ�����Ѷ� == �����Ѷ�)
		{
			flag = false;
			while (g_�Զ�����)
			{
				if (fun::getGameStatus() == 3)
				{
					break;
				}
				key.doKeyPress(VK_SPACE);
				Sleep(3000);
			}
			fun::passStoryFrame();
			break;
		}
		if (����ID != ��ǰ����ID)
		{
			key.doKeyPress(VK_NUMPAD2);
			Sleep(500);
			continue;
		}
		if (�����Ѷ� != ��ǰ�����Ѷ� && �����Ѷ� > ��ǰ�����Ѷ�)
		{
			key.doKeyPress(VK_NUMPAD3);
			Sleep(500);
			continue;
		}
		else if (�����Ѷ� != ��ǰ�����Ѷ� && �����Ѷ� < ��ǰ�����Ѷ�)
		{
			key.doKeyPress(VK_NUMPAD1);
			Sleep(500);
			continue;
		}
	}
}