#include "pch.h"
#include "function.h"
#include "status_3.h"
#include "role.h"
#include "astar.hpp"
#include "knapsac.h"
#include "call.h"
#include "task.h"

int moveToNextRoomFaulureNumber = 0;//��ͼʧ�ܼƴ�
int getTheSpoilsFaulureNumber = 0;//����ʧ�ܼƴ�
void status_3::manage()
{
	int gameStatus = fun::getGameStatus();
	if (status_3::getCurrentCopyId() == -1)
	{
		return;
	}
	if (fun::isOpenDoor())
	{
		//utils::myprintf(VMProtectDecryptStringA("���ѿ�"));
		if (g_�Զ�ģʽ == ��ש && knapsac::getGoodsCount() < 15)
		{
			if (getTheSpoils() == true && getTheSpoilsFaulureNumber < 10)
			{
				getTheSpoilsFaulureNumber++;
				return;
			}
			getTheSpoilsFaulureNumber = 0;
			//utils::myprintf(VMProtectDecryptStringA("��Ʒʰȡ���"));
		}
		if (fun::isBossRoom() == true && getMonsterCount() == 0)
		{
			switch (g_�Զ�ģʽ)
			{
			case ��ϰ:
				while (g_�Զ�����)
				{
					if (gameStatus != fun::getGameStatus() || fun::isBossRoom() == false)
					{
						g_ˢͼ����++;
						g_��ͼʱ�� = utils::getTime() - g_��ͼʱ��;
						g_��ͼ��� = true;
						utils::mywprintf(VMProtectDecryptStringW(L"��ϰ�� %d �� ��ʱ %d s "), CYAN, g_ˢͼ����, (int)(g_��ͼʱ�� / 1000));
						Sleep(1000);
						break;
					}
					key.doKeyPress(VK_F10);
					Sleep(1000);
				}
				break;
			case ��ש:
				while (g_�Զ�����)
				{
					if (getObjectPointerByCode(Code_ͨ��Ӫ��) == NULL)
					{
						Sleep(2000);
						key.doKeyPress(VK_ESCAPE);
						continue;
					}
					//��������();
					knapsac::keyPadSellThings();
					key.doKeyPress(VK_ESCAPE);
					while (g_�Զ�����)
					{
						if (gameStatus != fun::getGameStatus() || fun::isBossRoom() == false)
						{
							g_ˢͼ����++;
							g_��ͼʱ�� = utils::getTime() - g_��ͼʱ��;
							g_��ͼ��� = true;
							utils::mywprintf(VMProtectDecryptStringW(L"��ש�� %d �� ��ʱ %d �� "), CYAN, g_ˢͼ����, (int)(g_��ͼʱ�� / 1000));
							Sleep(500);
							break;
						}
						if (memory.read<int>(__�Ի���ַ2) == 1) {
							key.doKeyPress(VK_ESCAPE);
							key.doKeyPress(VK_SPACE);
							continue;
						}
						if (role::getCurrentRoleFatigueValue() <= 0) {
							key.doKeyPress(VK_F12);
						}
						else {
							key.doKeyPress(VK_F10);
						}
						Sleep(1000);
					}
					break;
				}
				break;
			case ����:
				while (g_�Զ�����)
				{
					if (getObjectPointerByCode(Code_ͨ��Ӫ��) == NULL)
					{
						Sleep(2000);
						key.doKeyPress(VK_ESCAPE);
						continue;
					}
					
					if (task::isThearMainTask())
					{
						Sleep(1000);
					}
					
					key.doKeyPress(VK_V);
					while (g_�Զ�����)
					{
						if (gameStatus != fun::getGameStatus() || fun::isBossRoom() == false)
						{
							g_ˢͼ����++;
							g_��ͼʱ�� = utils::getTime() - g_��ͼʱ��;
							g_��ͼ��� = true;
							utils::mywprintf(VMProtectDecryptStringW(L"����� %d �� ��ʱ %d �� "), CYAN, g_ˢͼ����, (int)(g_��ͼʱ�� / 1000));
							Sleep(1000);
							break;
						}
						
						if (task::isThearMainTask())
						{
							key.doKeyPress(VK_ESCAPE);
							key.doKeyPress(VK_SPACE);
							key.doKeyPress(VK_ESCAPE);
							key.doKeyPress(VK_SPACE);
						}
						
						Sleep(1000);
						/*if (fun::passStoryFrame() == false)
						{
							continue;
						}*/
						if (getTheSpoilsCount() > 0)
						{
							//printf("getTheSpoilsCount->:%d\n", getTheSpoilsCount());
							key.doKeyPress(VK_X, (150 * getTheSpoilsCount()));
						}
						if (knapsac::getGoodsCount() > 13)
						{
							knapsac::keyPadSellThings();
							key.doKeyPress(VK_ESCAPE);
						}
						if (role::getCurrentRoleFatigueValue() <= 0 || task::currentMainTaskIsCanIgnore() == true || task::isThearMainTask() == true) {
							key.doKeyPress(VK_F12);
						}
						else {
							key.doKeyPress(VK_F10);
							Sleep(1000);
							key.doKeyPress(VK_F10);
							key.doKeyPress(VK_F12);
						}
						Sleep(1000);
					}
					break;
				}
				break;
			default:
				break;
			}
		}
		else {
			moveToNextRoom();
		}
	}
	else {
		//utils::myprintf(VMProtectDecryptStringA("��ʼ���"));
		if (g_��ͼ��� == true)
		{
			g_��ͼʱ�� = utils::getTime();
			g_��ͼ��� = false;
		}
		if (fun::passStoryFrame() == false)
		{
			/*key.doKeyPress(VK_ESCAPE);
			Sleep(100);
			if (fun::passStoryFrame() == false)
			{
				key.doKeyPress(VK_RETURN);
			}*/
			return;
		}
		if (g_�Զ�ģʽ == ����)
		{
			if (g_���鹦�� == 0)
			{
				if (g_������� == 110525) {
					����_������();
				}
				else if (g_������� == 107000902) {
					����_����ħ();
				}
			}
			else if (g_���鹦�� == 1) {
				follow();
				fullScreenSkills();
			}
			
		}
		else if (g_�Զ�ģʽ == ��ש || g_�Զ�ģʽ == ��ϰ) {
			std::wstring role_job_name = role::getRoleJobName();
			if (wcscmp(role_job_name.c_str(), VMProtectDecryptStringW(L"����Ů��")) == 0)
			{
				����_����Ů��();
			}
			/*else if (wcscmp(role_job_name.c_str(), L"��Ѫ߱��") == 0) {
				����_��Ѫ߱��();
			}
			else if (wcscmp(role_job_name.c_str(), L"���") == 0) {
				����_���();
			}
			else if (wcscmp(role_job_name.c_str(), L"����") == 0) {
				����_����();
			}
			else if (wcscmp(role_job_name.c_str(), L"����") == 0) {
				����_����();
			}*/
		}
		
	}
}

void status_3::moveToNextRoom()
{
	DWORD temp_data;
	DWORD coordinate_struct;
	ROLE_POS rolePos;
	AStarMapInfo map_info;
	int direction = getDirection(1);//GetDirection(1);//�¸����䷴��
	int currentCopyId = getCurrentCopyId();
	POS currentRoomPos = fun::getCurrentRoomPos();
	if (currentCopyId == 9)
	{
		if (currentRoomPos.x == 0 && currentRoomPos.y == 1)
		{
			direction = 2;
		}
		else if (currentRoomPos.x == 0 && currentRoomPos.y == 0) {
			direction = 1;
		}
	}
	/*else if (currentCopyId == 104) {
		if (currentRoomPos.x == 2 && currentRoomPos.y == 1)
		{
			direction = 0;
		}
		else if (currentRoomPos.x == 1 && currentRoomPos.y == 1) {
			direction = 3;
		}
	}*/
	//utils::myprintf("direction->:%x", RED, direction);
	int x, y, xf, yf, cx, cy = 0;
	temp_data = memory.read<DWORD>(__�̵��ַ - 8);
	temp_data = memory.read<DWORD>(temp_data + __ʱ���ַ);
	temp_data = memory.read<DWORD>(temp_data + __����ṹƫ��1);
	coordinate_struct = temp_data + (direction + direction * 8) * 4 + __����ṹƫ��2 + (direction * 4);
	//utils::myprintf(VMProtectDecryptStringA("coordinate_struct->:%x"),RED, coordinate_struct);
	x = memory.read<int>(coordinate_struct + 0x0);
	y = memory.read<int>(coordinate_struct + 0x4);
	xf = memory.read<int>(coordinate_struct + 0x8);
	yf = memory.read<int>(coordinate_struct + 0xc);
	if (direction == 0)
	{
		cx = x + xf + 20;
		cy = y + (yf / 2);
	}
	else if (direction == 1)
	{
		cx = x - 20;
		cy = y + (yf / 2);
	}
	else if (direction == 2)
	{
		cx = x + xf / 2;
		cy = y + yf + 20;
	}
	else if (direction == 3)
	{
		cx = x + xf / 2;
		cy = y - 20;
	}
	Sleep(200);
	rolePos = role::getRolePos();
	rolePos.x = cx;
	rolePos.y = cy;
	//utils::myprintf(VMProtectDecryptStringA("������ x->:%d,y->:%d | xf->:%d,yf->:%d | cx->:%d,cy->:%d"), YELLOW, x, y, xf, yf, cx, cy);
	//utils::myprintf("������ rolePos.x->:%d,rolePos.y->:%d", YELLOW, rolePos.x, rolePos.y);
	//Sleep(1000);
	moveRoleToPos((x + xf / 2), cy);
	if (direction == 0) {
		key.doKeyPress(VK_NUMPAD1, 300);
	}
	else if (direction == 1) {
		key.doKeyPress(VK_NUMPAD3, 300);
	}
	else if (direction == 2)
	{
		key.doKeyPress(VK_NUMPAD5, 300);
	}
	else if (direction == 3) {
		key.doKeyPress(VK_NUMPAD2, 300);
	}
	Sleep(200);
	if (rolePos.room.x == role::getRolePos().room.x && rolePos.room.y == role::getRolePos().room.y)
	{
		if (moveToNextRoomFaulureNumber>=2)
		{
			call::��ͼCall(direction);
		}
		moveToNextRoomFaulureNumber++;
	}
	else {
		moveToNextRoomFaulureNumber = 0;
	}
	
}

DWORD status_3::getMapAddress()
{

	return memory.readOffset<int>(__�����ַ, { __��ͼƫ�� });
}

DWORD status_3::getMapStartAddress()
{
	return  memory.read<int>(getMapAddress() + __�׵�ַ);
}

int status_3::getMapObjectCount(DWORD map_start_address)
{
	return  (memory.read<int>(getMapAddress() + __β��ַ) - map_start_address) / 4;
}

void status_3::moveRoleToPos(int x,int y) 
{
	int pointer = 0;
	ROLE_POS currentPos;
	if (g_�Զ�ģʽ == ����)
	{
		if (g_���鹦�� == 0)
		{
			MAP_OBJECT_STRUCT object;
			if (getObjectInfoByObjectCode(&object, g_�������) == TRUE) {
				currentPos.x = object.x;
				currentPos.y = object.y;
				pointer = object.address;
			}
			else {
				/*g_�Զ����� = false;
				utils::myprintf(VMProtectDecryptStringA("����ģʽ�� ʹ�ñ����� ��δ��ȡ��������ָ��"));
				return;*/
				pointer = memory.read<int>(__�����ַ);
			}
			
		}
	}
	if(pointer == 0) {
		currentPos = role::getRolePos();
		pointer = memory.read<int>(__�����ַ);
	}
	if (g_�ƶ���ʽ == 0) //����call
	{
		call::����Call(pointer,x,y,0);
	}
	else if (g_�ƶ���ʽ == 1) { //�ű��ƶ�
		call::�ƶ�Call(pointer, x, y);
		Sleep((abs(currentPos.x - x) + abs(currentPos.y - y)) + 100);
	}
	Sleep(100);
}

int status_3::getCurrentCopyId()
{
	return memory.read<int>(__ͼ�ڸ���ID);
}
std::wstring status_3::getCurrentCopyName()
{
	return memory.readWString(__ͼ�ڸ�������,100);
}
// ��ȡ������Ϣ
MAP_OBJECT_STRUCT status_3::getObjectInfo(DWORD object_pointer)
{
	MAP_OBJECT_STRUCT object;
	DWORD pos_pointer;
	object.address = object_pointer;
	object.type = memory.read<DWORD>(object_pointer + __����ƫ��);
	object.camp = memory.read<DWORD>(object_pointer + __��Ӫƫ��);
	object.health_point = memory.read<DWORD>(object_pointer + __Ѫ��ƫ��);
	object.code = memory.read<DWORD>(object_pointer + __����ƫ��);
	if (object.type == 289 && object.camp == 200)
	{
		object.name = memory.readWString(memory.read<DWORD>(memory.read<DWORD>(object_pointer + __������Ʒ����ƫ��) + 0x24) + 0, 100);
	}
	else {
		object.name = memory.readWString(memory.read<DWORD>(object_pointer + __����ƫ��), 100);
	}
	if (object.type == 273)
	{
		if (object_pointer == memory.read<DWORD>(__�����ַ))
		{
			object.x = (int)memory.read<float>(__��ɫ���� + 0);
			object.y = (int)memory.read<float>(__��ɫ���� + 4);
			object.z = (int)memory.read<float>(__��ɫ���� + 8);
		}
		else {
			pos_pointer = memory.read<int>(object_pointer + __���������ƫ��);
			object.x = (int)memory.read<float>(pos_pointer + 0);
			object.y = (int)memory.read<float>(pos_pointer + 4);
			object.z = (int)memory.read<float>(pos_pointer + 8);
		}
	}
	else {
		pos_pointer = memory.read<int>(object_pointer + __����ƫ��);
		object.x = (int)memory.read<float>(pos_pointer + 0x10);
		object.y = (int)memory.read<float>(pos_pointer + 0x14);
		object.z = (int)memory.read<float>(pos_pointer + 0x18);
	}
	return object;
}
// ��ӡ����������Ϣ
void status_3::outputMapObjectInfo()
{
	DWORD mapStartAddress = getMapStartAddress();
	DWORD mapObjectCount = getMapObjectCount(mapStartAddress);
	utils::myprintf(VMProtectDecryptStringA("map_start_address %x\n"), PINK, mapStartAddress);
	utils::myprintf(VMProtectDecryptStringA("map_object_count %d\n"), PINK, mapObjectCount);
	MAP_OBJECT_STRUCT _ObjectInfo;
	
	DWORD objectAddress;
	for (size_t i = 0; i < mapObjectCount; i++)
	{
		objectAddress = memory.read<int>((ULONG)(mapStartAddress + i * 4));
		if (objectAddress <= 0)continue;
		_ObjectInfo = getObjectInfo(objectAddress);
		utils::myprintf(VMProtectDecryptStringA("address 0x%x"), RED, _ObjectInfo.address);
		utils::myprintf(VMProtectDecryptStringA("code %d"), RED, _ObjectInfo.code);
		utils::myprintf(VMProtectDecryptStringA("type %d"), RED, _ObjectInfo.type);
		utils::myprintf(VMProtectDecryptStringA("camp %d"), RED, _ObjectInfo.camp);
		utils::myprintf(VMProtectDecryptStringA("health_point %d"), RED, _ObjectInfo.health_point);
		utils::myprintf(VMProtectDecryptStringA("pos %d,%d,%d"), RED, _ObjectInfo.x, _ObjectInfo.y, _ObjectInfo.z);
		utils::mywprintf(VMProtectDecryptStringW(L"name %s"), RED, _ObjectInfo.name.c_str());
		utils::myprintf(VMProtectDecryptStringA("====================================="));
	}
	utils::myprintf(VMProtectDecryptStringA("��ǰ����ID %d\n"), PINK, getCurrentCopyId());
	utils::mywprintf(VMProtectDecryptStringW(L"��ǰ�������� %ws\n"), PINK, getCurrentCopyName().c_str());
	POS currentRoomPos = fun::getCurrentRoomPos();
	utils::mywprintf(VMProtectDecryptStringW(L"��ǰ�������� %d,%d\n"), PINK, currentRoomPos.x, currentRoomPos.y);
}
// ��ȡ�����ڹ�������
int status_3::getMonsterCount()
{
	DWORD mapStartAddress = getMapStartAddress();
	DWORD mapObjectCount = getMapObjectCount(mapStartAddress);
	std::vector<MAP_OBJECT_STRUCT> Objects;
	MAP_OBJECT_STRUCT object;
	DWORD objectAddress;
	int monsterCount = 0;
	for (size_t i = 0; i < mapObjectCount; i++) {
		objectAddress = memory.read<DWORD>(mapStartAddress + i * 4);
		if (objectAddress <= 0)continue;
		object = getObjectInfo(objectAddress);
		if (g_�Զ�ģʽ == ���� && object.name.find(L"��Boss") != -1)
		{
			continue;
		}
		if (object.code == 258 || object.code == 818 || object.code == 63821)
		{
			continue;
		}
		if (object.type == 529 || object.type == 273 || object.type == 545)
		{
			if (object.camp > 0)
			{
				if (object.health_point > 0 || object.code == 8104 || object.code == 817)
				{
					monsterCount++;
				}
			}
		}
	}
	return monsterCount;
}
// ȫ������
void status_3::fullScreenSkills()
{
	DWORD mapStartAddress = getMapStartAddress();
	DWORD mapObjectCount = getMapObjectCount(mapStartAddress);
	std::vector<MAP_OBJECT_STRUCT> Objects;
	MAP_OBJECT_STRUCT object;
	DWORD objectAddress;
	int rolePointer = memory.read<int>(__�����ַ);
	for (size_t i = 0; i < mapObjectCount; i++) {
		objectAddress = memory.read<DWORD>(mapStartAddress + i * 4);
		if (objectAddress <= 0)continue;
		object = getObjectInfo(objectAddress);
		if (g_�Զ�ģʽ == ���� && object.name.find(L"��Boss") != -1)
		{
			continue;
		}
		if (object.code == 258 || object.code == 818 || object.code == 63821)
		{
			continue;
		}
		if (object.type == 529 || object.type == 273 || object.type == 545)
		{
			if (object.camp > 0)
			{
				if (object.health_point > 0 || object.code == 8104 || object.code == 817)
				{
					call::����Call(rolePointer, 48611, 0x113, object.x, object.y, object.z);
					Sleep(50);
				}
			}
		}
	}
}
// �����Ƿ��й���Z�����35
bool status_3::findMonsterZ_AxisMoreThanThe35()
{
	DWORD mapStartAddress = getMapStartAddress();
	DWORD mapObjectCount = getMapObjectCount(mapStartAddress);
	std::vector<MAP_OBJECT_STRUCT> Objects;
	MAP_OBJECT_STRUCT object;
	DWORD objectAddress;
	int monsterCount = 0;
	for (size_t i = 0; i < mapObjectCount; i++) {
		objectAddress = memory.read<DWORD>(mapStartAddress + i * 4);
		if (objectAddress <= 0)continue;
		object = getObjectInfo(objectAddress);
		if (object.code == 258 || object.code == 818 || object.code == 63821)
		{
			continue;
		}
		/*if (getCurrentCopyId() == 148)
		{
			return true;
		}*/
		if (object.type == 529 || object.type == 273 || object.type == 545)
		{
			if (object.camp > 0)
			{
				if (object.health_point > 0 || object.code == 8104 || object.code == 817)
				{
					if (object.z >= 35)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
// ����������ģ������
bool status_3::blurryFindMonsterByString(std::wstring string) {
	DWORD mapStartAddress = getMapStartAddress();
	DWORD mapObjectCount = getMapObjectCount(mapStartAddress);
	std::vector<MAP_OBJECT_STRUCT> Objects;
	MAP_OBJECT_STRUCT object;
	DWORD objectAddress;
	int monsterCount = 0;
	for (size_t i = 0; i < mapObjectCount; i++) {
		objectAddress = memory.read<DWORD>(mapStartAddress + i * 4);
		if (objectAddress <= 0)continue;
		object = getObjectInfo(objectAddress);
		if (object.code == 258 || object.code == 818 || object.code == 63821)
		{
			continue;
		}
		if (object.type == 529 || object.type == 273 || object.type == 545)
		{
			if (object.camp > 0)
			{
				if (object.health_point > 0 || object.code == 8104 || object.code == 817)
				{
					if (!(object.name.find(string.c_str(), 0) == -1)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}
// ����ɫ�����������
void status_3::sortByDistance(std::vector<MAP_OBJECT_STRUCT> &Objects)
{
	MAP_OBJECT_STRUCT temp_var;
	ROLE_POS RolePos = role::getRolePos();
	for (size_t i = 0; i < Objects.size(); i++)
	{
		for (size_t j = 0; j < Objects.size() - i; j++)
		{
			if (abs(Objects[j].x - RolePos.x) + abs(Objects[j].y - RolePos.y) > abs(Objects[j + 1].x - RolePos.x) + abs(Objects[j + 1].y - RolePos.y))
			{
				temp_var = Objects[j];
				Objects[j + 1] = Objects[j];
				Objects[j] = temp_var;
			}
		}
	}
}
// ����
void status_3::follow(std::wstring name)
{
	DWORD mapStartAddress = getMapStartAddress();
	DWORD mapObjectCount = getMapObjectCount(mapStartAddress);
	MAP_OBJECT_STRUCT object;
	ROLE_POS rolePos = role::getRolePos();
	DWORD objectAddress;
	for (size_t i = 0; i < mapObjectCount; i++) {
		objectAddress = memory.read<int>(mapStartAddress + i * 4);
		if (objectAddress <= 0)continue;
		object = getObjectInfo(objectAddress);
		if (object.code == 258 || object.code == 818 || object.code == 63821)
			continue;
		if (!(object.health_point > 0 || object.code == 8104 || object.code == 817))
			continue;
		if (!name.empty() && object.name.find(name.c_str(), 0) == -1)
			continue;
		if (!(object.type == 529 || object.type == 273 || object.type == 545))
			continue;
		if (!(object.camp > 0))
			continue;
		if (g_�Զ�ģʽ == ���� && wcsstr(object.name.c_str(),L"���� - �����Ѳ���׷����"))
		{
			continue;
		}
		if (abs(rolePos.x - object.x) > 200 || abs(rolePos.y - object.y) > 50 || wcsstr(object.name.c_str(),L"���˲�ͼ��") == 0)
		{
			if (rolePos.x > object.x)
			{
				moveRoleToPos(object.x + utils::createRandom(-10, 10) + 200, object.y + utils::createRandom(-10, 10));
				/*if (role::getRoleFacing() == 1)
				{*/
					key.doKeyPress(VK_NUMPAD1);
				//}
				
			}
			else {
				moveRoleToPos(object.x + utils::createRandom(-10, 10) - 200, object.y + utils::createRandom(-10, 10));
				/*if (role::getRoleFacing() == 0)
				{*/
					key.doKeyPress(VK_NUMPAD3);
				//}
			}
			Sleep(200);
			break;
		}
		else {
			if (rolePos.x > object.x) {
				/*if (role::getRoleFacing() == 1)
				{*/
				key.doKeyPress(VK_NUMPAD1);
				//}
			}
			else if (rolePos.x < object.x) {
				/*if (role::getRoleFacing() == 0)
				{*/
				key.doKeyPress(VK_NUMPAD3);
				//}
			}
		}
	}
}
// ������ ����ħ
void status_3::����_����ħ()
{
	MAP_OBJECT_STRUCT object;
	if (getObjectInfoByObjectCode(&object, g_�������) == FALSE)
	{
		call::����Call(g_�������);
		while (g_�Զ�����) {
			if (getObjectInfoByObjectCode(&object, g_�������) == TRUE)
			{
				break;
			}
			Sleep(1000);
		}
	}
	if (findMonsterZ_AxisMoreThanThe35())
	{
		role::releaseSkillByKey(VK_F, 2500);
		if (fun::isOpenDoor() == true)
		{
			return;
		}
		follow();
		role::releaseSkillByKey(VK_A, 2000);
		if (fun::isOpenDoor() == true)
		{
			return;
		}
	}
	else {
		follow();
		role::releaseSkillByKey(VK_S, 1000);
		if (fun::isOpenDoor() == true)
		{
			return;
		}
		follow();
		role::releaseSkillByKey(VK_S, 1000);
		if (fun::isOpenDoor() == true)
		{
			return;
		}
	}
	if (blurryFindMonsterByString(VMProtectDecryptStringW(L"����")) == true)
	{
		follow(VMProtectDecryptStringW(L"����"));
		role::releaseSkillByKey(VK_D, 2000);
	}
	
}
// ������ ������
void status_3::����_������()
{
	MAP_OBJECT_STRUCT object;
	if (getObjectInfoByObjectCode(&object, g_�������) == FALSE)
	{
		call::����Call(g_�������);
		Sleep(3000);
	}
	role::releaseSkillByKey(VK_A,1000);
	if (fun::isOpenDoor() == true)
	{
		return;
	}
	follow();
	role::releaseSkillByKey(VK_S, 1000);
	if (fun::isOpenDoor() == true)
	{
		return;
	}
	follow();
	role::releaseSkillByKey(VK_A, 1000);
	if (fun::isOpenDoor() == true)
	{
		return;
	}
	follow();
	role::releaseSkillByKey(VK_S, 1000);
	if (fun::isOpenDoor() == true)
	{
		return;
	}
	follow();
	role::releaseSkillByKey(VK_D, 1000);
}
// ���ݶ�������ȡ������Ϣ
BOOL status_3::getObjectInfoByObjectCode(PMAP_OBJECT_STRUCT object,int objectCode)
{
	DWORD mapStartAddress = getMapStartAddress();
	DWORD mapObjectCount = getMapObjectCount(mapStartAddress);
	ROLE_POS rolePos = role::getRolePos();
	DWORD objectAddress;
	for (size_t i = 0; i < mapObjectCount; i++) {
		objectAddress = memory.read<int>(mapStartAddress + i * 4);
		if (objectAddress <= 0)continue;
		*object = getObjectInfo(objectAddress);
		if (object->code == objectCode)
		{
			return TRUE;
		}
	}
	return NULL;
}
// ��ȡս��Ʒ����
int status_3::getTheSpoilsCount() {
	DWORD mapStartAddress = getMapStartAddress();
	DWORD mapObjectCount = getMapObjectCount(mapStartAddress);
	MAP_OBJECT_STRUCT object;
	DWORD objectAddress;
	ROLE_POS rolePos = role::getRolePos();
	int spoilsCount = 0;
	for (size_t i = 0; i < mapObjectCount; i++) {
		objectAddress = memory.read<DWORD>((mapStartAddress + i * 4));
		if (objectAddress <= 0)continue;
		object = getObjectInfo(objectAddress);
		if (object.code == Code_���� || object.code == Code_��� || object.code == Code_�ɳ�֮Ȫˮ)
			continue;
		if (object.type == 289 && object.camp == 200)
		{
			if (
				wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"���")) != 0 &&
				wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"������ʳ")) != 0
				)
			{
				spoilsCount++;
			}
		}
	}
	return spoilsCount;
}
// ��ȡս��Ʒ
bool status_3::getTheSpoils() {
	DWORD mapStartAddress = getMapStartAddress();
	DWORD mapObjectCount = getMapObjectCount(mapStartAddress);
	MAP_OBJECT_STRUCT object;
	DWORD objectAddress;
	ROLE_POS rolePos = role::getRolePos();
	int spoilsCount = getTheSpoilsCount();
	if (g_�Զ�ģʽ == ��ש)
	{
		if ((rolePos.room.x == 2 && rolePos.room.y == 2 && getCurrentCopyId() == ������))
		{
			key.doKeyPress(VK_V);
			if (spoilsCount > 0) {
				Sleep(200);
				key.doKeyPress(VK_X, 150 * spoilsCount);
			}
			return false;
		}
	}
	/*else if (g_�Զ�ģʽ == ����) {
		if (fun::isBossRoom() == true)
		{
			key.doKeyPress(VK_V);
			if (spoilsCount > 0) {
				Sleep(200);
				key.doKeyPress(VK_X, 150 * spoilsCount);
			}
			return false;
		}
	}*/
	
	for (size_t i = 0; i < mapObjectCount; i++) {
		objectAddress = memory.read<DWORD>((mapStartAddress + i * 4));
		if (objectAddress <= 0)continue;
		object = getObjectInfo(objectAddress);
		if (object.code == Code_���� || object.code == Code_��� || object.code == Code_�ɳ�֮Ȫˮ)
			continue;
		if (
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"�鲼Ƭ")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"���¼�Ӳ����")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"���¼���ʯ")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"�绯�����")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"����Ƭ")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"�������Ƭ")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"�ƾɵ�Ƥ��")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"�޾�������")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"����HPҩ��")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"����MPҩ��")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"���ʯ")) == 0 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"���ػʵ۵�ӡ��")) == 0 ||
			object.name.find(VMProtectDecryptStringW(L"���ͼ"), 0) != -1 ||
			object.name.find(VMProtectDecryptStringW(L"���²�"), 0) != -1 ||
			wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"������ʳ")) == 0
			) 
		{

			continue;
		}
		if (object.type == 289 && object.camp == 200)
		{
			if (object.z > 0)
			{
				Sleep(1000);
				return true;
			}
			if (abs(rolePos.x - object.x) > 2 || abs(rolePos.y - object.y) > 2)
			{
				moveRoleToPos(object.x, object.y);
			}
			if (wcscmp(object.name.c_str(), VMProtectDecryptStringW(L"���")) != 0)
			{
				key.doKeyPress(VK_X);
				Sleep(100);
			}
			return true;
		}
	}
	return false;
}

// ��ȡͨ���̵� Ӫ��
DWORD status_3::getObjectPointerByCode(int code)
{
	DWORD mapStartAddress = getMapStartAddress();
	DWORD mapObjectCount = getMapObjectCount(mapStartAddress);
	MAP_OBJECT_STRUCT object;
	DWORD objectAddress;
	for (size_t i = 0; i < mapObjectCount; i++) {
		objectAddress = memory.read<int>((mapStartAddress + i * 4));
		if (objectAddress <= 0)continue;
		object = getObjectInfo(objectAddress);
		if (object.code == code)
		{
			return objectAddress;
		}
	}
	return NULL;
}

void status_3::����_����Ů��()
{
	POS currentRoom = fun::getCurrentRoomPos();
	ROLE_POS rolePos;
	if (getCurrentCopyId() == ������)
	{
		if (currentRoom.x == 0 && currentRoom.y == 0)
		{
			Sleep(1000);
			role::releaseSkillByKey(VK_F);
			moveRoleToPos(468, 239);
			role::releaseSkillByKey(VK_G);
		}
		else if (currentRoom.x == 1 && currentRoom.y == 0) {
			Sleep(500);
			key.doKeyPress(VK_Y);
			Sleep(3000);
		}
		else if (currentRoom.x == 2 && currentRoom.y == 0) {
			moveRoleToPos(582, 241);
			role::releaseSkillByKey(VK_A, 300);
		}
		else if (currentRoom.x == 2 && currentRoom.y == 1) {
			moveRoleToPos(550,200);
			key.doKeyPress(VK_NUMPAD1);
			role::releaseSkillByKey(VK_R);
		}
		/*else if (currentRoom.x == 1 && currentRoom.y == 1) {
			moveRoleToPos(653, 272);
			role::releaseSkillByKey(VK_A, 300);
		}
		else if (currentRoom.x == 1 && currentRoom.y == 2) {
			moveRoleToPos(290, 321);
			key.doKeyPress(VK_NUMPAD3);
			role::releaseSkillByKey(VK_A, 300);
		}*/
		else if (currentRoom.x == 2 && currentRoom.y == 2) {
			moveRoleToPos(331, 329);
			key.doKeyPress(VK_NUMPAD3);
			role::releaseSkillByKey(VK_A);
			moveRoleToPos(611, 201);
			role::releaseSkillByKey(VK_T);
			follow(VMProtectDecryptStringW(L"���˲�ͼ��"));
			role::releaseSkillByKey(VK_Q);
		}
		else if (currentRoom.x == 3 && currentRoom.y == 2) {
			moveRoleToPos(343, 290);
			role::releaseSkillByKey(VK_A, 300);
		}
		else if (currentRoom.x == 3 && currentRoom.y == 1) {
			if (role::getRoleFacing() == 0)
			{
				key.doKeyPress(VK_NUMPAD3);
			}
			key.doKeyPress(VK_W);
			Sleep(3500);
		}
		if (fun::isOpenDoor() == true)
		{

			return;
		}
		follow();
		role::releaseSkillByKey(VK_S);
		if (fun::isOpenDoor() == true)
		{
			return;
		}
		else {
			Sleep(1200);
		}
		follow();
		role::releaseSkillByKey(VK_E);
		if (fun::isOpenDoor() == true)
		{
			return;
		}
		
		follow();
		role::releaseSkillByKey(VK_G);
		if (fun::isOpenDoor() == true)
		{
			return;
		}
		follow();
		role::releaseSkillByKey(VK_H);
		if (fun::isOpenDoor() == true)
		{
			return;
		}
		follow();
		role::releaseSkillByKey(VK_D);
		if (fun::isOpenDoor() == true)
		{
			return;
		}
		follow();
		role::releaseSkillByKey(VK_S);
		if (fun::isOpenDoor() == true)
		{
			return;
		}
		else {
			Sleep(1200);
		}
		int i = 0;
		while (fun::isOpenDoor() == false && g_�Զ�����)
		{
			if (fun::passStoryFrame() == false)
			{
				continue;
			}
			follow();
			key.doKeyPress(VK_X, 1000);
			if (i%3 == 0)
			{
				follow();
				role::releaseSkillByKey(VK_S);
			}
			if (i%10 == 0)
			{
				follow();
				role::releaseSkillByKey(VK_E);
			}
			if (i%20 == 0)
			{
				follow();
				role::releaseSkillByKey(VK_G);
			}
			if (i > 50) {
				utils::myprintf(VMProtectDecryptStringA("��ʱ�����Զ�"));
				key.doKeyPress(VK_ESCAPE);
				key.doKeyPress(VK_ESCAPE);
				g_�Զ����� = false;
				return;
			}
			i++;
		}
	}
	else {
		utils::myprintf(VMProtectDecryptStringA("�˸����ݲ�֧��"));
	}
}