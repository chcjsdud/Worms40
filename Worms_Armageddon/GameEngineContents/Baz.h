#pragma once
#include "WeaponMaster.h"

// Ό³Έν :
class Baz : public WeaponMaster
{
public:
	// constrcuter destructer
	Baz();
	~Baz();

	// delete Function
	Baz(const Baz& _Other) = delete;
	Baz(Baz&& _Other) noexcept = delete;
	Baz& operator=(const Baz& _Other) = delete;
	Baz& operator=(Baz&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	bool WeaponUpdate() override;
};

