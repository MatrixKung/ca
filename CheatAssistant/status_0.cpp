#include "pch.h"
#include "status_0.h"
#include "function.h"

void status_0::manage()
{
	if ((getRoleCount() - 1) == getRoleIndex()) {
		utils::mywprintf(VMProtectDecryptStringW(L"���н�ɫˢͼ��ϣ��Զ��ر�"));
		g_�Զ����� = false;
	}
	else {
		selectRole(-1);
	}

}

int status_0::getRoleIndex()
{
	int role_index = memory.readOffset<int>(__����ȡֵ, { __��ɫ�±�ƫ�� });
	return role_index;

}

int status_0::getRoleCount()
{
	int role_count = memory.readOffset<int>(__����ȡֵ, { __��ǰ��ɫ����,__��ɫ����ƫ��2 });
	return role_count;
}

int status_0::getRoleMaxCount()
{
	int role_max_count = memory.readOffset<int>(__����ȡֵ, { __����ɫ����,__��ɫ����ƫ��2 });
	return role_max_count;
}

void status_0::selectRole(int roleIndex) 
{
	if (roleIndex == -1)
	{
		roleIndex = getRoleIndex() + 1;
	}
	while (fun::getGameStatus() == 0 && g_�Զ�����)
	{
		if (roleIndex != getRoleIndex())
		{
			key.doKeyPress(VK_RIGHT);
		}
		//doKeyPress(VK_RETURN);
		key.setMousePos(gameWindowInfo.left + 534, gameWindowInfo.top + 550);
		key.mouseClick();
		Sleep(3000);
	}
}