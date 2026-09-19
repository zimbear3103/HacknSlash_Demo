// Copyright 2020 Dan Kestranek.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HacknSlash_DemoGameMode.generated.h"

UCLASS(minimalapi)
class AHacknSlash_DemoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHacknSlash_DemoGameMode();

	void HeroDied(AController* Controller);

protected:
	float RespawnDelay;

	TSubclassOf<class AGDHeroCharacter> HeroClass;

	AActor* EnemySpawnPoint;

	virtual void BeginPlay() override;

	void RespawnHero(AController* Controller);
};
