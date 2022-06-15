#include "Font.h"
#include "Enums.h"
#include <string.h>
#include <sstream>

Font::Font()
{
}

Font::~Font()
{
}

void Font::Start()
{
}

void Font::Update()
{
}

void Font::GameContentCreateFont(std::string _Text, float4 _Pivot)
{
	FontRenderer.reserve(_Text.size());
	size_t FontSize = _Text.size();

	for (int i = 0; i < FontSize; ++i)
	{
		FontRenderer.push_back(CreateRenderer("FontEdit.bmp", static_cast<int>(RenderOrder::Font)));
		FontRenderer.at(i)->CameraEffectOff();
	}

	float MarginX = 0;
	for (int Count_ = 0; Count_ < FontSize; ++Count_)
	{

		switch (_Text.c_str()[Count_])
		{
		case 'A':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::A));
			break;
		case 'B':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::B));
			break;
		case 'C':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::C));
			break;
		case 'D':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::D));
			break;
		case 'E':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::E));
			break;
		case 'F':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::F));
			break;
		case 'G':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::G));
			break;
		case 'H':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::H));
			break;
		case 'I':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::I));
			break;
		case 'J':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::J));
			break;
		case 'K':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::K));
			break;
		case 'L':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::L));
			break;
		case 'M':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::M));
			break;
		case 'N':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::N));
			break;
		case 'O':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::O));
			break;
		case 'P':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::P));
			break;
		case 'Q':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Q));
			break;
		case 'R':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::R));
			break;
		case 'S':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::S));
			break;
		case 'T':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::T));
			break;
		case 'U':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::U));
			break;
		case 'V':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::V));
			break;
		case 'W':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::W));
			break;
		case 'X':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::X));
			break;
		case 'Y':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Y));
			break;
		case 'Z':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Z));
			break;
		case 'a':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::a));
			break;
		case 'b':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::b));
			break;
		case 'c':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::c));
			break;
		case 'd':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::d));
			break;
		case 'e':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::e));
			break;
		case 'f':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::f));
			break;
		case 'g':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::g));
			break;
		case 'h':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::h));
			break;
		case 'i':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::i));
			break;
		case 'j':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::j));
			break;
		case 'k':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::k));
			break;
		case 'l':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::l));
			break;
		case 'm':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::m));
			break;
		case 'n':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::n));
			break;
		case 'o':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::o));
			break;
		case 'p':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::p));
			break;
		case 'q':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::q));
			break;
		case 'r':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::r));
			break;
		case 's':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::s));
			break;
		case 't':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::t));
			break;
		case 'u':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::u));
			break;
		case 'v':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::v));
			break;
		case 'w':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::w));
			break;
		case 'x':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::x));
			break;
		case 'y':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::y));
			break;
		case 'z':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::z));
			break;
		case '0':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Zero));
			break;
		case '1':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::One));
			break;
		case '2':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Two));
			break;
		case '3':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Three));
			break;
		case '4':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Four));
			break;
		case '5':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Five));
			break;
		case '6':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Six));
			break;
		case '7':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Seven));
			break;
		case '8':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Eight));
			break;
		case '9':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Nine));
			break;
		case '?':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Question));
			break;
		case '*':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Astrerrisk));
			break;
		case ')':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Parentheses_Right));
			break;
		case '(':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Parentheses_Left));
			break;
		case '"':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Quotation));
			break;
		case '!':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Exclamaion_Mark));
			break;
		case '-':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Hyphen));
			break;
		case '.':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::DecimalPoint));
			break;
		case ',':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Period));
			break;
		case '`':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Grave_Accent));
			break;
		case '/':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Slash));
			break;

		default:
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Empty));
			break;
		}

		FontRenderer.at(Count_)->SetPivot({ MarginX + _Pivot.x , 0 + _Pivot.y });
		MarginX += 10.f;

	}

	//delete Font_;

}

void Font::GameContentChangeFont(std::string _Text, float4 _Pivot)
{
	std::vector<GameEngineRenderer*>::iterator Start = FontRenderer.begin();

	for (Start; Start != FontRenderer.end(); ++Start)
	{
		if ((*Start) != nullptr)
		{
			(*Start)->Death();
		}
	}

	FontRenderer.clear();


	FontRenderer.reserve(_Text.size());
	size_t FontSize = _Text.size();

	for (int i = 0; i < FontSize; ++i)
	{
		FontRenderer.push_back(CreateRenderer("FontEdit.bmp", static_cast<int>(RenderOrder::Font)));
		FontRenderer.at(i)->CameraEffectOff();
	}

	float MarginX = 0;
	for (int Count_ = 0; Count_ < FontSize; ++Count_)
	{

		switch (_Text.c_str()[Count_])
		{
		case 'A':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::A));
			break;
		case 'B':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::B));
			break;
		case 'C':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::C));
			break;
		case 'D':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::D));
			break;
		case 'E':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::E));
			break;
		case 'F':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::F));
			break;
		case 'G':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::G));
			break;
		case 'H':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::H));
			break;
		case 'I':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::I));
			break;
		case 'J':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::J));
			break;
		case 'K':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::K));
			break;
		case 'L':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::L));
			break;
		case 'M':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::M));
			break;
		case 'N':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::N));
			break;
		case 'O':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::O));
			break;
		case 'P':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::P));
			break;
		case 'Q':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Q));
			break;
		case 'R':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::R));
			break;
		case 'S':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::S));
			break;
		case 'T':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::T));
			break;
		case 'U':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::U));
			break;
		case 'V':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::V));
			break;
		case 'W':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::W));
			break;
		case 'X':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::X));
			break;
		case 'Y':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Y));
			break;
		case 'Z':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Z));
			break;
		case 'a':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::a));
			break;
		case 'b':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::b));
			break;
		case 'c':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::c));
			break;
		case 'd':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::d));
			break;
		case 'e':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::e));
			break;
		case 'f':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::f));
			break;
		case 'g':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::g));
			break;
		case 'h':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::h));
			break;
		case 'i':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::i));
			break;
		case 'j':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::j));
			break;
		case 'k':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::k));
			break;
		case 'l':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::l));
			break;
		case 'm':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::m));
			break;
		case 'n':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::n));
			break;
		case 'o':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::o));
			break;
		case 'p':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::p));
			break;
		case 'q':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::q));
			break;
		case 'r':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::r));
			break;
		case 's':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::s));
			break;
		case 't':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::t));
			break;
		case 'u':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::u));
			break;
		case 'v':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::v));
			break;
		case 'w':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::w));
			break;
		case 'x':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::x));
			break;
		case 'y':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::y));
			break;
		case 'z':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::z));
			break;
		case '0':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Zero));
			break;
		case '1':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::One));
			break;
		case '2':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Two));
			break;
		case '3':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Three));
			break;
		case '4':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Four));
			break;
		case '5':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Five));
			break;
		case '6':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Six));
			break;
		case '7':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Seven));
			break;
		case '8':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Eight));
			break;
		case '9':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Nine));
			break;
		case '?':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Question));
			break;
		case '*':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Astrerrisk));
			break;
		case ')':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Parentheses_Right));
			break;
		case '(':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Parentheses_Left));
			break;
		case '"':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Quotation));
			break;
		case '!':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Exclamaion_Mark));
			break;
		case '-':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Hyphen));
			break;
		case '.':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::DecimalPoint));
			break;
		case ',':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Period));
			break;
		case '`':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Grave_Accent));
			break;
		case '/':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Slash));
			break;

		default:
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_INDEX::Empty));
			break;
		}

		FontRenderer.at(Count_)->SetPivot({ MarginX + _Pivot.x , 0 + _Pivot.y });
		MarginX += 10.f;

	}
}

void Font::GameContentCreateNumberFont(int _Num, float4 _Pivot, FONT_COLOR _FontColor)
{
	std::stringstream ssInt;
	ssInt << _Num;

	FontRenderer.reserve(ssInt.str().size());
	size_t FontSize = ssInt.str().size();

	for (int i = 0; i < FontSize; ++i)
	{
		FontRenderer.push_back(CreateRenderer("HPnumber.bmp", static_cast<int>(RenderOrder::Font)));
		FontRenderer.at(i)->CameraEffectOn();
	}

	int ColorIndex = 0;

	switch (_FontColor)
	{
	case FONT_COLOR::White:
		ColorIndex = 0;
		break;
	case FONT_COLOR::Gray:
		ColorIndex = 10;
		break;
	case FONT_COLOR::Orange:
		ColorIndex = 20;
		break;
	case FONT_COLOR::Blue:
		ColorIndex = 30;
		break;
	case FONT_COLOR::Green:
		ColorIndex = 40;
		break;
	case FONT_COLOR::Yellow:
		ColorIndex = 50;
		break;
	case FONT_COLOR::SkyBlue:
		ColorIndex = 60;
		break;
	case FONT_COLOR::Pink:
		ColorIndex = 70;
		break;
	default:
		break;
	}


	float MarginX = 0;
	if (FontSize == 3)
	{
		MarginX = -10.f;
	}

	if (FontSize == 2)
	{
		MarginX = -5.f;
	}

	for (int Count_ = 0; Count_ < FontSize; ++Count_)
	{
		switch (ssInt.str().c_str()[Count_])
		{

		case '0':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Zero) + ColorIndex);
			break;
		case '1':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::One) + ColorIndex);
			break;
		case '2':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Two) + ColorIndex);
			break;
		case '3':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Three) + ColorIndex);
			break;
		case '4':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Four) + ColorIndex);
			break;
		case '5':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Five) + ColorIndex);
			break;
		case '6':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Six) + ColorIndex);
			break;
		case '7':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Seven) + ColorIndex);
			break;
		case '8':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Eight) + ColorIndex);
			break;
		case '9':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Nine) + ColorIndex);
			break;
		}

		FontRenderer.at(Count_)->SetPivot({ MarginX + _Pivot.x , 0 + _Pivot.y });
		//MiddleSortX -= 20.f;

		MarginX += 10.f;

	}
}

void Font::GameContentChangeNumberFont(int _Num, float4 _Pivot, FONT_COLOR _FontColor)
{
	std::vector<GameEngineRenderer*>::iterator Start = FontRenderer.begin();

	for (Start; Start != FontRenderer.end(); ++Start)
	{
		if ((*Start) != nullptr)
		{
			(*Start)->Death();
		}
	}

	FontRenderer.clear();

	std::stringstream ssInt;
	ssInt << _Num;

	FontRenderer.reserve(ssInt.str().size());
	size_t FontSize = ssInt.str().size();

	for (int i = 0; i < FontSize; ++i)
	{
		FontRenderer.push_back(CreateRenderer("HPnumber.bmp", static_cast<int>(RenderOrder::Font)));
		FontRenderer.at(i)->CameraEffectOn();
	}

	int ColorIndex = 0;

	switch (_FontColor)
	{
	case FONT_COLOR::White:
		ColorIndex = 0;
		break;
	case FONT_COLOR::Gray:
		ColorIndex = 10;
		break;
	case FONT_COLOR::Orange:
		ColorIndex = 20;
		break;
	case FONT_COLOR::Blue:
		ColorIndex = 30;
		break;
	case FONT_COLOR::Green:
		ColorIndex = 40;
		break;
	case FONT_COLOR::Yellow:
		ColorIndex = 50;
		break;
	case FONT_COLOR::SkyBlue:
		ColorIndex = 60;
		break;
	case FONT_COLOR::Pink:
		ColorIndex = 70;
		break;
	default:
		break;
	}


	float MarginX = 0;
	if (FontSize == 3)
	{
		MarginX = -10.f;
	}

	if (FontSize == 2)
	{
		MarginX = -5.f;
	}

	for (int Count_ = 0; Count_ < FontSize; ++Count_)
	{
		switch (ssInt.str().c_str()[Count_])
		{

		case '0':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Zero) + ColorIndex);
			break;
		case '1':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::One) + ColorIndex);
			break;
		case '2':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Two) + ColorIndex);
			break;
		case '3':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Three) + ColorIndex);
			break;
		case '4':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Four) + ColorIndex);
			break;
		case '5':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Five) + ColorIndex);
			break;
		case '6':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Six) + ColorIndex);
			break;
		case '7':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Seven) + ColorIndex);
			break;
		case '8':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Eight) + ColorIndex);
			break;
		case '9':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(NUMBER_FONT::Nine) + ColorIndex);
			break;
		}

		FontRenderer.at(Count_)->SetPivot({ MarginX + _Pivot.x , 0 + _Pivot.y });
		//MiddleSortX -= 10.f;

		MarginX += 10.f;

	}

}