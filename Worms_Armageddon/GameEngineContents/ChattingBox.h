#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>
#include <vector>

#include "Font.h"


enum class CHAT_FONT
{
	A = 0,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	a,
	b,
	c,
	d,
	e,
	f,
	g,
	h,
	i,
	j,
	k,
	l,
	m,
	n,
	o,
	p,
	q,
	r,
	s,
	t,
	u,
	v,
	w,
	x,
	y,
	z,
	Zero,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Grave_Accent,					 //`
	Exclamaion_Mark,				//!
	Empty = 160,
};



// Ό³Έν :
class ChattingBox : public GameEngineActor
{
public:
	// constrcuter destructer
	ChattingBox();
	~ChattingBox();

	// delete Function
	ChattingBox(const ChattingBox& _Other) = delete;
	ChattingBox(ChattingBox&& _Other) noexcept = delete;
	ChattingBox& operator=(const ChattingBox& _Other) = delete;
	ChattingBox& operator=(ChattingBox&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;


private:
	GameEngineCollision* ChattingBox_;
	Font* Font_;

	std::string String_;
	std::list<std::string> AllString_;

};

