#pragma once
#include <map>
#include <string>
#include "Enums.h"

// 이정민
// 설명 : 게임옵션을 관리하는 클래스. 항상 static으로 사용할것
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
	// 키 = 팀 색깔, 값 = (키 : 팀 번호, 값 : 플레이어 숫자)
	std::map<TeamColor, int> PlayerTeamSetting_;

	// 한 턴의 시간 값
	int TurnTime_;

	// 맵 종류
	MapType MapType_;

	// 웜즈의 Hp
	int WormzHp_;
};

