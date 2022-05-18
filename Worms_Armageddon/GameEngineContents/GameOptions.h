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

public:
	inline void SetPlayerName(int _Num, std::string _Names)
	{
		PlayerNames_.insert(std::pair<int, std::string>(_Num, _Names));
	}

	inline std::map<int, std::string> GetPlayerName()
	{
		return PlayerNames_;
	}

	inline void SetPlayerColor(int _Num, int _Color)
	{
		PlayerColors_.insert(std::pair<int, int>(_Num, _Color));
	}

	inline std::map<int, int> GetPlayerColor()
	{
		return PlayerColors_;
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

	inline int SetPlayerNum()
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

private:
	// 키 = 플레이어 번호, 값 = 이름
	std::map<int, std::string> PlayerNames_;
	// 키 = 플레이어 번호, 값 = 색깔
	std::map<int, int> PlayerColors_;

	// 한 턴의 시간 값
	int TurnTime_;
	// 플레이어 인원수
	int PlayerNum_;
	// 맵 종류
	MapType MapType_;


private:
	GameOptions();
	~GameOptions();
};

