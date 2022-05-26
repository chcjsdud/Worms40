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
	WindGaugeRenderer_ = CreateRenderer((int)RenderOrder::UI);
	WindGaugeRenderer_->SetImage("WindGauge.bmp");
	WindGaugeRenderer_->CameraEffectOff();

	//���ʹ��� UI�ִϸ��̼�
	WindLeftRenderer_ = CreateRenderer((int)RenderOrder::UI);
	WindLeftRenderer_->CreateAnimation("windBar.bmp", "WindBar", 0, 7,0.02f, true);
	WindLeftRenderer_->ChangeAnimation("WindBar");
	WindLeftRenderer_->SetPivot({-45,0 });
	WindLeftRenderer_->CameraEffectOff();

	//�����ʹ��� UI�ִϸ��̼�
	WindRightRenderer_= CreateRenderer((int)RenderOrder::UI);
	WindRightRenderer_->CreateAnimation("windBar.bmp", "WindBar", 8, 15, 0.02f, true);
	WindRightRenderer_->ChangeAnimation("WindBar");
	WindRightRenderer_->SetPivot({ 45,0 });
	WindRightRenderer_->CameraEffectOff();



	WindLeftHiderRenderer_ = CreateRenderer("WindBarHider.bmp", (int)RenderOrder::UI, RenderPivot::LEFT);
	WindLeftHiderRenderer_->SetPivot({ -90,0 });
	WindLeftHiderRenderer_->CameraEffectOff();

	WindRightHiderRenderer_ = CreateRenderer("WindBarHider.bmp", (int)RenderOrder::UI, RenderPivot::RIGHT);
	WindRightHiderRenderer_->SetPivot({ 89,0 });
	WindRightHiderRenderer_->CameraEffectOff();
	

	//WindDir_ = WindType::Left;
	//WindRightHider_x = 0;


}

void WindGauge::Update()
{

	//hider_x = 88 �� �ִ�ũ��
	if (WindDir_ == WindType::Left)
	{
		//�����ʹٶ��������� ����������
		if (88.0f > WindRightHider_x)
		{
			WindRightHider_x += 1;  //���� ���ش�
			WindRightHiderRenderer_->SetScale({ WindRightHider_x, WindRightHiderRenderer_->GetImageScale().y });
			HideWindFigure_ = 100.0f;
		}
		else
		{//�����ʹٶ��� �������
			MyWindFigure_ = MaxWindFigure_ - WindFigure_;

			//������ �������ʰ�
			if (MyWindFigure_ == HideWindFigure_)
			{
				HideWindFigure_ = MyWindFigure_;
			}
			else if (MyWindFigure_ >= HideWindFigure_) //���� �ٶ����Ⱑ �ٲ�ٶ����� ������
			{
				HideWindFigure_++;
			}
			else if (MyWindFigure_ <= HideWindFigure_) //���� �ٶ����Ⱑ �ٲ�ٶ����⺸�� ������
			{
				HideWindFigure_--;
			}

			//�̹��� ���� 
			//�ڿ������� ���� �پ����ϱ����� �̹���ũ�⸦ ������ ����ؼ� ����
			WindLeftHider_x = WindLeftHiderRenderer_->GetImageScale().x * HideWindFigure_ / MaxWindFigure_;
			WindLeftHiderRenderer_->SetScale({WindLeftHider_x, WindLeftHiderRenderer_->GetImageScale().y });
		}

	}
	else if (WindDir_ == WindType::Right)
	{
		if (88.0f > WindLeftHider_x)  //WindBarxũ�Ⱑ 88
		{
			WindLeftHider_x += 1;  //���� ���ش� Hiderx�� ��ġ�� �������� ������
			WindLeftHiderRenderer_->SetScale({ WindLeftHider_x, WindLeftHiderRenderer_->GetImageScale().y });
			HideWindFigure_ = 100.0f;
		}
		else
		{//���ʹٶ��� �������
			MyWindFigure_ = MaxWindFigure_ - WindFigure_;  //�������� �̹����� �ִ�ٶ����� - ����ٶ�����

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
			WindRightHiderRenderer_->SetScale({ WindRightHider_x, WindRightHiderRenderer_->GetImageScale().y });
		}

	}
	//�̹���ũ�� * ���� scale / max scale
	
}

void WindGauge::Render()
{

}
