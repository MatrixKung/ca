#include "pch.h"
#include "send_packet.h"
#include "function.h"
//__asm {
//	push cdov
//	mov ecx, __������ַ
//	mov ecx, dword ptr ss : [ecx]
//	mov eax, __����CALL
//	call eax
//}
void SendPacket::����Call(int cdov) {
	byte bytes[] = {
		0x68,0x00,0x00,0x00,0x00,
		0xB9,0x00,0x00,0x00,0x00,
		0x8B,0x09,
		0xB8,0x00,0x00,0x00,0x00,
		0xFF,0xD0
	};
	*(int*)(bytes + 1) = cdov;
	*(int*)(bytes + 6) = __������ַ;
	*(int*)(bytes + 13) = __����CALL;
	std::vector<byte> v_bytes = utils::bytesToVectorBytes(bytes, sizeof(bytes));
	v_shell_code.insert(v_shell_code.end(), v_bytes.begin(), v_bytes.end());

}
//__asm {
//	push wtud
//	mov ecx, __������ַ
//	mov ecx, dword ptr ss : [ecx]
//	mov eax, cdov
//	call eax
//}
void SendPacket::�ܰ�Call(int wtud, int taya) {
	int cdov = 0;
	if (taya == 1)cdov = __�ܰ�CALL;
	if (taya == 2)cdov = __�ܰ�CALL + 0x30;
	if (taya == 3)cdov = __�ܰ�CALL + 0x60;
	if (taya == 4)cdov = __�ܰ�CALL + 0x90;
	byte bytes[] = {
		0x68,0x00,0x00,0x00,0x00,
		0xB9,0x00,0x00,0x00,0x00,
		0x8B,0x09,
		0xB8,0x00,0x00,0x00,0x00,
		0xFF,0xD0
	};
	*(int*)(bytes + 1) = wtud;
	*(int*)(bytes + 6) = __������ַ;
	*(int*)(bytes + 13) = cdov;
	std::vector<byte> v_bytes = utils::bytesToVectorBytes(bytes, sizeof(bytes));
	v_shell_code.insert(v_shell_code.end(), v_bytes.begin(), v_bytes.end());
}
//__asm {
//	push wtud
//	mov ecx, __������ַ
//	mov ecx, dword ptr ss : [ecx]
//	mov eax, cdov
//	call eax
//}
void SendPacket::����Call(bool is_send) {
	byte bytes[] = {
			0xB8,0x00,0x00,0x00,0x00,
			0xFF,0xD0,
			0x00
	};
	*(int*)(bytes + 1) = __����CALL;
	if (is_send == true)*(byte*)(bytes + 7) = 0xC3;

	std::vector<byte> v_bytes = utils::bytesToVectorBytes(bytes, sizeof(bytes));
	v_shell_code.insert(v_shell_code.end(), v_bytes.begin(), v_bytes.end());
	if (is_send == true)
	{
		byte * shell_code = new byte[v_shell_code.size()];
		utils::vectorBytesToBytes(v_shell_code, shell_code);
		fun::remoteMainThreadCall(shell_code, v_shell_code.size());
		delete[]shell_code;
	}
}


void SendPacket::���ؽ�ɫ()
{
	����Call(0x7);
	����Call();
}

void SendPacket::ѡ���ɫ(int role_index)
{
	����Call(4);
	�ܰ�Call(role_index, 3);
	����Call();
}

void SendPacket::����˲��(CITY_INFO cityInfo, int goods_index)
{
	if (goods_index > 0)
	{
		����Call(237);
		�ܰ�Call(goods_index, 2);
		�ܰ�Call(2600014, 3);
		�ܰ�Call(0, 1);
		�ܰ�Call(cityInfo.room.x, 1);
		�ܰ�Call(cityInfo.room.y, 1);
		�ܰ�Call(cityInfo.x, 2);
		�ܰ�Call(cityInfo.y, 2);
		����Call();
	}
	else {
		����Call(36);
		�ܰ�Call(cityInfo.room.x, 1);
		�ܰ�Call(cityInfo.room.y, 1);
		�ܰ�Call(cityInfo.x, 2);
		�ܰ�Call(cityInfo.y, 2);
		�ܰ�Call(5, 1);
		�ܰ�Call(38, 2);
		�ܰ�Call(1, 2);
		�ܰ�Call(0, 3);
		�ܰ�Call(0, 1);
		����Call();
	}
}

void SendPacket::����ѡͼ()
{
	����Call(15);
	�ܰ�Call(0, 3);
	����Call();
}

void SendPacket::ѡ�񸱱�(int �������, int �����Ѷ�, int ����ģʽ,int ����ID)
{

	����Call(16);
	�ܰ�Call(�������, 3);
	if (������� > 7100 && ������� < 7200)
	{
		�ܰ�Call(0, 1);
		�ܰ�Call(0, 2);
	}
	else
	{
		�ܰ�Call(�����Ѷ�, 1);
		�ܰ�Call(0, 2);
	}
	if (����ģʽ == ��Ԩ) { // ��Ԩ
		�ܰ�Call(1, 1);
		�ܰ�Call(0, 1);
	}
	else if (����ģʽ == ��ϰ) {
		�ܰ�Call(0, 1);//��ϰ
		�ܰ�Call(1, 1);
	}
	else {//��ͨ
		�ܰ�Call(0, 1);
		�ܰ�Call(0, 1);
	}
	�ܰ�Call(65535, 2);
	�ܰ�Call(0, 3);
	�ܰ�Call(0, 1);
	if (������� > 7100 && ������� < 7200)
	{
		�ܰ�Call(0, 3);
	}
	else {
		�ܰ�Call(����ID, 3);
	}
	����Call();
}

void SendPacket::���ʰȡ(int loot_address, int x, int y)
{
	����Call(43);
	�ܰ�Call(loot_address, 3);
	�ܰ�Call(0, 1);
	�ܰ�Call(1, 1);
	�ܰ�Call(x, 2);
	�ܰ�Call(y, 2);
	�ܰ�Call(0, 2);
	�ܰ�Call(x + ((x % 4) + 1), 2);
	�ܰ�Call(y + ((y % 4) + 1), 2);
	�ܰ�Call(0, 2);
	�ܰ�Call(0, 2);
	����Call();
}

void SendPacket::�������()
{
	����Call(69);
	����Call();

	����Call(70);
	����Call();

	����Call(71);
	�ܰ�Call(0, 1);
	����Call();

	����Call(1431);
	����Call();
}

void SendPacket::�������(int ��Ʒ�±�)
{
	����Call(593);
	�ܰ�Call(2, 3);
	�ܰ�Call(0, 3);
	����Call();

	����Call(22);
	�ܰ�Call(0, 1);
	�ܰ�Call(��Ʒ�±�, 2);
	�ܰ�Call(1, 3);
	�ܰ�Call(1000, 3);
	�ܰ�Call(��Ʒ�±� * 2 + 3, 3);
	����Call();
}


//void SendPacket::����س�()
//{
//	using namespace utils;
//	����Call(123);
//	�ܰ�Call(createRandom(1, 1500), 3);
//	�ܰ�Call(createRandom(1, 1500), 3);
//	�ܰ�Call(createRandom(1, 1500), 3);
//	�ܰ�Call(createRandom(1, 1500), 3);
//	�ܰ�Call(createRandom(1, 1500), 3);
//	�ܰ�Call(createRandom(1, 1500), 3);
//	����Call();
//	����Call(42);
//	����Call();
//}