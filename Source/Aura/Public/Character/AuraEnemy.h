// Copyright Nixzxin

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{


public:
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	AAuraEnemy();

private:
	GENERATED_BODY()
};

inline AAuraEnemy::AAuraEnemy()
{
	GetMesh() -> SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}
