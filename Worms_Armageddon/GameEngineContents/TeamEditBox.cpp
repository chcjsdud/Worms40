#include "TeamEditBox.h"
#include "Enums.h"

#include <GameEngine/GameEngineRenderer.h>

// ���� : ������ ��(ex. 1-UPŬ��)�� TeamListBox�� �ø���

//TODO:: ��ư ����Ʈ
//TODO:: ��ư���� ���� ��ũ��
//TODO:: ��ư Ŭ�� �� TeamListBox�� �ø�

TeamEditBox::TeamEditBox() 
	: BoxRenderer_(nullptr)
{
}

TeamEditBox::~TeamEditBox() 
{
}

void TeamEditBox::Start()
{
	BoxRenderer_ = CreateRenderer("6836.bmp", static_cast<int>(RenderOrder::BackGround_1));
	BoxRenderer_->SetScale(float4{ 302, 161 });
	BoxRenderer_->SetPivot(BoxRenderer_->GetScale().Half());
}

void TeamEditBox::Update()
{
}

