#pragma once
class SendPacket
{
public:
	void ���ؽ�ɫ();
	void ѡ���ɫ(int role_index);
	void ����˲��(CITY_INFO cityInfo, int goods_index = 0);
	void ����ѡͼ();
	void ѡ�񸱱�(int �������, int �����Ѷ�, int ����ģʽ = ��ש, int ����ID = 0);
	void ���ʰȡ(int loot_address, int x, int y);
	void �������();
	void �������(int ��Ʒ�±�);
	//void ����س�();
private:
	std::vector<byte> v_shell_code;
	void ����Call(int cdov);
	void �ܰ�Call(int wtud, int taya);
	void ����Call(bool is_send = true);
};

