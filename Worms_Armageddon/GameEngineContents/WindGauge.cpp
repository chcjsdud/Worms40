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

	//왼쪽방향 UI애니메이션
	WindLeftRenderer_ = CreateRenderer((int)RenderOrder::UI);
	WindLeftRenderer_->CreateAnimation("windBar.bmp", "WindBar", 0, 7,0.02f, true);
	WindLeftRenderer_->ChangeAnimation("WindBar");
	WindLeftRenderer_->SetPivot({-45,0 });
	WindLeftRenderer_->CameraEffectOff();

	//오른쪽방향 UI애니메이션
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

	//hider_x = 88 이 최대크기
	if (WindDir_ == WindType::Left)
	{
		//오른쪽바람게이지가 남아있으면
		if (88.0f > WindRightHider_x)
		{
			WindRightHider_x += 1;  //점점 없앤다
			WindRightHiderRenderer_->SetScale({ WindRightHider_x, WindRightHiderRenderer_->GetImageScale().y });
			HideWindFigure_ = 100.0f;
		}
		else
		{//오른쪽바람이 사라지면
			MyWindFigure_ = MaxWindFigure_ - WindFigure_;

			//같으면 변하지않게
			if (MyWindFigure_ == HideWindFigure_)
			{
				HideWindFigure_ = MyWindFigure_;
			}
			else if (MyWindFigure_ >= HideWindFigure_) //현재 바람세기가 바뀐바람보다 낮으면
			{
				HideWindFigure_++;
			}
			else if (MyWindFigure_ <= HideWindFigure_) //현재 바람세기가 바뀐바람세기보다 높으면
			{
				HideWindFigure_--;
			}

			//이미지 갱신 
			//자연스럽게 점점 줄어들게하기위해 이미지크기를 비율로 계산해서 변경
			WindLeftHider_x = WindLeftHiderRenderer_->GetImageScale().x * HideWindFigure_ / MaxWindFigure_;
			WindLeftHiderRenderer_->SetScale({WindLeftHider_x, WindLeftHiderRenderer_->GetImageScale().y });
		}

	}
	else if (WindDir_ == WindType::Right)
	{
		if (88.0f > WindLeftHider_x)  //WindBarx크기가 88
		{
			WindLeftHider_x += 1;  //점점 없앤다 Hiderx의 수치가 높을수록 가려짐
			WindLeftHiderRenderer_->SetScale({ WindLeftHider_x, WindLeftHiderRenderer_->GetImageScale().y });
			HideWindFigure_ = 100.0f;
		}
		else
		{//왼쪽바람이 사라지면
			MyWindFigure_ = MaxWindFigure_ - WindFigure_;  //가려야할 이미지는 최대바람세기 - 현재바람세기

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
	//이미지크기 * 현재 scale / max scale
	
}

void WindGauge::Render()
{

}
