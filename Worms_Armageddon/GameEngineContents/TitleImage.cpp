#include "TitleImage.h"

TitleImage::TitleImage()
	:
	TitleImageRenderer_(nullptr)
{
}

TitleImage::~TitleImage()
{
}

void TitleImage::Start()
{
	TitleImageRenderer_ = CreateRenderer("Fade_Black.bmp");
}

void TitleImage::Update()
{
}
