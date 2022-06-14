#pragma once
#include <map>
#include <string>
#include "Enums.h"

// ������
// ���� : ���ӿɼ��� �����ϴ� Ŭ����. �׻� static���� ����Ұ�
class GameOptions
{

public:
	static GameOptions PlayingOptions;

	GameOptions();
	~GameOptions();

public:
	inline void SetPlayerTeamSetting(TeamColor _TeamColor,int _Num)
	{
		PlayerTeamSetting_[_TeamColor] = _Num;
	}

	inline std::map<TeamColor, int> GetPlayerTeamSetting()
	{
		return PlayerTeamSetting_;
	}

	inline void SetTurnTime(int _Time)
	{
		TurnTime_ = _Time;
	}

	inline int GetTurnTime()
	{
		return TurnTime_;
	}

	inline void SetMapType(MapType _MapType)
	{
		MapType_ = _MapType;
	}

	inline MapType GetMapType()
	{
		return MapType_;
	}

	inline void SetWormzHp(int _WormzHp)
	{
		WormzHp_ = _WormzHp;
	}

	inline int GetWormzHp()
	{
		return WormzHp_;
	}

private:
	// Ű = �� ����, �� = (Ű : �� ��ȣ, �� : �÷��̾� ����)
	std::map<TeamColor, int> PlayerTeamSetting_;

	// �� ���� �ð� ��
	int TurnTime_;

	// �� ����
	MapType MapType_;

	// ������ Hp
	int WormzHp_;
};

