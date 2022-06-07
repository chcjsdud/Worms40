#pragma once
#include "UIMaster.h"
#include "Enums.h"
#include <vector>

// 설명 : 플레이어 인벤토리 
class GameEngineRenderer;
class GameEngineCollision;
class Inventory : public UIMaster
{
public:
	// 인벤토리에서 클릭한 무기
	inline WeaponState GetClickedWeapon()
	{
		return ClickedWeapon_;
	}

	// 인벤토리가 활성화 되있으면 True
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
	void InventoryWeaponInit(); // 인벤토리 안의 무기 위치 초기화
	void MoveInOut();
	void ClickWeapon();
	void OnOffSelector();

private:
	// 격자배경
	GameEngineRenderer* GridRenderer_;

	// UI In<->Out 관련
	float4 OutPos_;
	float4 InPos_;
	bool IsOut_;

	//  5 x 11 아이템 목록 관련
	std::vector<std::vector<InventoryButton>> WeaponButtons_;
	WeaponState ClickedWeapon_;

};



