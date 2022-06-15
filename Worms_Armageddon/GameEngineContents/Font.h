#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>

enum class FONT_COLOR
{
	Orange,
	Blue,
	Green,
	Yellow,
	Pink,
	SkyBlue,
	White,
	Gray,
};


// 설명 :
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
	void GameContentCreateFont(std::string _Text, float4 _Pivot);
	void GameContentChangeFont(std::string _Text, float4 _Pivot);

	void GameContentCreateNumberFont(int _Num, float4 _Pivot, FONT_COLOR _FontColor);
	void GameContentChangeNumberFont(int _Num, float4 _Pivot, FONT_COLOR _FontColor);


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




enum class NUMBER_FONT
{
	//화이트
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

};
