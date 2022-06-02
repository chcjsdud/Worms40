#pragma once
#include "UIMaster.h"
#include <vector>
// ���� :
class GameEngineRenderer;
class GameEngineCollision;
class Inventory : public UIMaster
{
public:
	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
	void MoveInOut();
	void ClickWeapon();

private:
	GameEngineRenderer* GridRenderer_;

	// UI In<->Out ����
	float4 OutPos_;
	float4 InPos_;
	bool IsOut_;

	//  5 x 11 ������ ��� ����
	std::vector<std::vector<GameEngineCollision*>> WeaponButtons_;

};

