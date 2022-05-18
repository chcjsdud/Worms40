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
	// Ű = �÷��̾� ��ȣ, �� = �̸�
	std::map<int, std::string> PlayerNames_;
	// Ű = �÷��̾� ��ȣ, �� = ����
	std::map<int, int> PlayerColors_;

	// �� ���� �ð� ��
	int TurnTime_;
	// �÷��̾� �ο���
	int PlayerNum_;
	// �� ����
	MapType MapType_;


private:
	GameOptions();
	~GameOptions();
};

