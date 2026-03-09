// Copyright Nixzxin


#include "AbilitySystem/Abilities/SummonAbility.h"

TArray<FVector> USummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinions;

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);
	TArray<FVector> SpawnLocations;

	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChoseSpawnLocation = Location + Direction * FMath::RandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, ChoseSpawnLocation + FVector(0.f,0.f,400.f), ChoseSpawnLocation - FVector(0.f,0.f,400.f), ECC_Visibility);
		if (Hit.bBlockingHit)
		{
			ChoseSpawnLocation = Hit.ImpactPoint;
		}
		SpawnLocations.Add(ChoseSpawnLocation);
	}

	return SpawnLocations;
}

TSubclassOf<APawn> USummonAbility::GetRandomMinionClass()
{
	const int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);
	return MinionClasses[Selection];
}
