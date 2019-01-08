#pragma once
#define ���� 0
#define ��� 1
#define ���� 2
#define ��ͼ 3
namespace role {
	int getRoleLevel();
	std::wstring getRoleJobName();
	int getCurrentRoleFatigueValue();
	ROLE_POS getRolePos();
	int getRoleStatus();
	int getRoleFacing();
	void releaseSkillByKey(int keyCode, int s = 100);
	void moveRoleToPos_����(ROLE_POS targetPos);
	void moveRoleToPos_��ͼ(ROLE_POS targetPos);
	void moveRoleToPos_����(ROLE_POS targetPos);
	void moveRoleToPos_���(ROLE_POS targetPos);
	std::vector<int> moveRoleToPos_���㷽��(ROLE_POS currentPos, ROLE_POS targetPos);
	void moveRoleToPos_���㴦��(ROLE_POS targetPos, std::map<const char*, bool>& cardPointList);
	void moveRoleToPos(ROLE_POS targetPos,int type = ����);
	int getRoleMoveSpeed();
	void moveRoleToPos2(ROLE_POS targetPos, int type);
	void ignoreBuild(bool enbale);
	void ignoreTerrain(bool enbale);
}

