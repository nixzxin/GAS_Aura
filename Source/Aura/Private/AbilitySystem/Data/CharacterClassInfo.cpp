// Copyright Nixzxin


#include "AbilitySystem/Data/CharacterClassInfo.h"

FCharacterDefaultClassInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInformation.FindChecked(CharacterClass);
}
