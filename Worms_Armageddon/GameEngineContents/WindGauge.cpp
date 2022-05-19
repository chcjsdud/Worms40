#include "WindGauge.h"
#include "Enums.h"
#include "GameEngine/GameEngineRenderer.h"

WindGauge::WindGauge() :
	MaxWindFigure_(100.0f),
	WindFigure_(0),
	IsEnd(false)
{
}

WindGauge::~WindGauge() 
{
}

void WindGauge::Start()
{
	WindGaugeRenderer_ = CreateRenderer((int)ActorGroup::UI);
	WindGaugeRenderer_->SetImage("WindGauge.bmp");

	//���ʹ��� UI�ִϸ��̼�
	WindLeftRenderer_ = CreateRenderer((int)ActorGroup::UI);
	WindLeftRenderer_->CreateAnimation("windBar.bmp", "WindBar", 0, 7,0.02f, true);
	WindLeftRenderer_->ChangeAnimation("WindBar");
	WindLeftRenderer_->SetPivot({-45,0 });

	//�����ʹ��� UI�ִϸ��̼�
	WindRightRenderer_= CreateRenderer((int)ActorGroup::UI);
	WindRightRenderer_->CreateAnimation("windBar.bmp", "WindBar", 8, 15, 0.02f, true);
	WindRightRenderer_->ChangeAnimation("WindBar");
	WindRightRenderer_->SetPivot({ 45,0 });




	WindLeftHiderRenderer_ = CreateRenderer("WindBarHider.bmp", (int)ActorGroup::UI, RenderPivot::LEFT);
	WindLeftHiderRenderer_->SetPivot({ -90,0 });

	WindRightHiderRenderer_ = CreateRenderer("WindBarHider.bmp", (int)ActorGroup::UI, RenderPivot::RIGHT);
	WindRightHiderRenderer_->SetPivot({ 89,0 });
	

	//WindDir_ = WindType::Left;
	//WindRightHider_x = 0;

}

void WindGauge::Update()
{
	//hider_x = 88 �� �ִ�ũ��
	if (WindDir_ == WindType::Left)
	{
		//�����ʹٶ��������� ����������
		if (88 > WindRightHider_x)
		{
			WindRightHider_x += 1;  //���� ���ش�
			WindRightHiderRenderer_->SetScale({ static_cast<float>(WindRightHider_x), WindRightHiderRenderer_->GetImageScale().y });
			HideWindFigure_ = 100;
		}
		else
		{//�����ʹٶ��� �������
			MyWindFigure_ = MaxWindFigure_ - WindFigure_;

			if (MyWindFigure_ == HideWindFigure_)
			{
				HideWindFigure_ = MyWindFigure_;
			}
			else if (MyWindFigure_ >= HideWindFigure_)
			{
				HideWindFigure_++;
			}
			else if (MyWindFigure_ <= HideWindFigure_)
			{
				HideWindFigure_--;
			}

			WindLeftHider_x = WindLeftHiderRenderer_->GetImageScale().x * HideWindFigure_ / MaxWindFigure_;
			WindLeftHiderRenderer_->SetScale({ static_cast<float>(WindLeftHider_x), WindLeftHiderRenderer_->GetImageScale().y });
		}

	}
	else if (WindDir_ == WindType::Right)
	{
		if (88 > WindLeftHider_x)
		{
			WindLeftHider_x += 1;  //���� ���ش�
			WindLeftHiderRenderer_->SetScale({ static_cast<float>(WindLeftHider_x), WindLeftHiderRenderer_->GetImageScale().y });
			HideWindFigure_ = 100;
		}
		else
		{//�����ʹٶ��� �������
			MyWindFigure_ = MaxWindFigure_ - WindFigure_;

			if (MyWindFigure_ == HideWindFigure_)
			{
				HideWindFigure_ = MyWindFigure_;
			}
			else if (MyWindFigure_ >= HideWindFigure_)
			{
				HideWindFigure_++;
			}
			else if (MyWindFigure_ <= HideWindFigure_)
			{
				HideWindFigure_--;
			}

			WindRightHider_x = WindRightHiderRenderer_->GetImageScale().x * HideWindFigure_ / MaxWindFigure_;
			WindRightHiderRenderer_->SetScale({ static_cast<float>(WindRightHider_x), WindRightHiderRenderer_->GetImageScale().y });
		}

	}
	//�̹���ũ�� * ���� scale / max scale
	
}

void WindGauge::Render()
{

}
