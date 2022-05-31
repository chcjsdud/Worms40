#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>

// Ό³Έν :
class Font : public GameEngineActor
{
public:
	// constrcuter destructer
	Font();
	~Font();

	// delete Function
	Font(const Font& _Other) = delete;
	Font(Font&& _Other) noexcept = delete;
	Font& operator=(const Font& _Other) = delete;
	Font& operator=(Font&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update() override;

private:
	std::vector<GameEngineRenderer*> FontRenderer;


public:
	void GameContentCreateFont(std::string _Text, float4 _Pos);
	void GameContentChangeFont(std::string _Text, float4 _Pos);
};

enum class FONT_INDEX
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
	At,								//@
	FoundSign,						//#
	Dollar,							//$
	Percent,						//%
	Smile,							//^
	Ampersand,						//&
	Astrerrisk,						//*
	Parentheses_Left,				//(
	Parentheses_Right,				//)
	Hyphen,							//-
	Under_Hyphen,					//_
	Equal,							//=
	Plus,							//+
	Square_Bracket_Left,			//[
	Curly_Bracket_Left,				//{
	Square_Bracket_Right,			//]
	Curly_Bracket_Right,			//}
	Semicolon,						//;
	Colon,							//:
	Apostrophe,						//'
	Quotation,						//"
	BackSlash,						// 
	Pipe,							// |
	Period,							//,
	DecimalPoint = 89,				//.
	Slash = 91,						// /
	Question = 92,					//
	Empty = 160,


};
