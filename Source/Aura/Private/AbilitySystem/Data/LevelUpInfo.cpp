// Copyright Nixzxin


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXp(int32 XP) const
{
	int32 CurrentLevel = 1;
	if (LevelUpInformation.Num() -1 <= CurrentLevel) return CurrentLevel;
	for (int32 i = 0; i < LevelUpInformation.Num(); i++)
	{
		if (XP >= LevelUpInformation[i].LevelUpRequirement)
		{
			CurrentLevel = CurrentLevel + i;
		}
		else 
		{
			return CurrentLevel;
		}
	}
	return CurrentLevel;
}
