#pragma once
#include <GameEngine/GameEngineActor.h>


// 설명 :	PlayLevel에서 테스트용으로 쓸 BackGorundActor 클래스
class PlayLevelTestMap	:public GameEngineActor
{
public:
	// constrcuter destructer
	PlayLevelTestMap();
	~PlayLevelTestMap();

	// delete Function
	PlayLevelTestMap(const PlayLevelTestMap& _Other) = delete;
	PlayLevelTestMap(PlayLevelTestMap&& _Other) noexcept = delete;
	PlayLevelTestMap& operator=(const PlayLevelTestMap& _Other) = delete;
	PlayLevelTestMap& operator=(PlayLevelTestMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* BackGround_;
	GameEngineRenderer* Ground_;
	GameEngineRenderer* MidGround_;
	GameEngineRenderer* ColImage_;

private:
	bool ChangeMode_;


private:
	void ChangePixelMode();

public:
	GameEngineRenderer* GetBackGround()
	{
		return BackGround_;
	}
};

