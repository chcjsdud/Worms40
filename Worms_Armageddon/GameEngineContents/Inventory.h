#pragma once
#include "UIMaster.h"
#include "Enums.h"
#include <vector>

// ���� : �÷��̾� �κ��丮 
class GameEngineRenderer;
class GameEngineCollision;
class Inventory : public UIMaster
{
public:
	// �κ��丮���� Ŭ���� ����
	inline WeaponState GetClickedWeapon()
	{
		return ClickedWeapon_;
	}

	// �κ��丮�� Ȱ��ȭ �������� True
	inline bool IsInventoryOut()
	{
		return IsOut_;
	}

private:
	class InventoryButton
	{
	public:
		InventoryButton() : Col_(nullptr), WeaponSelector_(nullptr), Weapon_(WeaponState::None) {};
		~InventoryButton() {};

		GameEngineCollision* Col_;
		GameEngineRenderer* WeaponSelector_;
		WeaponState Weapon_;
	};

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
	void InventoryWeaponInit(); // �κ��丮 ���� ���� ��ġ �ʱ�ȭ
	void MoveInOut();
	void ClickWeapon();
	void OnOffSelector();

private:
	// ���ڹ��
	GameEngineRenderer* GridRenderer_;

	// UI In<->Out ����
	float4 OutPos_;
	float4 InPos_;
	bool IsOut_;

	//  5 x 11 ������ ��� ����
	std::vector<std::vector<InventoryButton>> WeaponButtons_;
	WeaponState ClickedWeapon_;

};



