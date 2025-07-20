// Copyright Nixzxin


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeByTag(const FGameplayTag& Tag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo& AttributeInfo : AttributeInfos)
	{
		if (AttributeInfo.AttributeTag == Tag)
		{
			return AttributeInfo;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find attribute with tag '%s'"), *Tag.ToString());
	}
	return FAuraAttributeInfo();
}
