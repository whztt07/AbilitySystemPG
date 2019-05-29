#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeSetBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangeDelegate, float, Health, float, MaxHealth);

UCLASS()
class ABILITYSYSTEMPG_API UAttributeSetBase : public UAttributeSet{
	GENERATED_BODY()

public:

	UAttributeSetBase();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
	FGameplayAttributeData Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
	FGameplayAttributeData MaxHealth;


	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


	FOnHealthChangeDelegate OnHealthChange;

};
