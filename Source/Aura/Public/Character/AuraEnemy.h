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
	/**Enemy Interface**/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/**End Enemy Interface**/
	AAuraEnemy();

private:
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
