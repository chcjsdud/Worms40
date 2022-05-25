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

public:
	inline void SetPlayerTeamSetting(TeamColor _TeamColor, std::string _Name, int _Num)
	{
		PlayerTeamSetting_[_TeamColor].insert(std::pair<std::string, int>(_Name, _Num));
	}

	inline std::map<TeamColor, std::map<std::string, int>> GetPlayerTeamSetting()
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

	inline void SetPlayerNum(int _Num)
	{
		PlayerNum_ = _Num;
	}

	inline int GetPlayerNum()
	{
		return PlayerNum_;
	}

	inline void SetMapType(MapType _MapType)
	{
		MapType_ = _MapType;
	}

	inline MapType SetMapType()
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
	// Ű = �� ����, �� = (Ű : �� �̸�, �� : �÷��̾� ����)
	std::map<TeamColor, std::map<std::string, int>> PlayerTeamSetting_;

	// �� ���� �ð� ��
	int TurnTime_;
	// �÷��̾� �ο���
	int PlayerNum_;
	// �� ����
	MapType MapType_;

	// ������ Hp
	int WormzHp_;
};

