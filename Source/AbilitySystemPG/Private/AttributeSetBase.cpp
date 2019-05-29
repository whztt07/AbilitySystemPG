#include "AttributeSetBase.h"

// ENGINE - Gameplay Ability System
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"

UAttributeSetBase::UAttributeSetBase() : Health(200.0f), MaxHealth(200.f) {
	
}

void UAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data){
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Health))) {
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.0f, MaxHealth.GetCurrentValue()));

		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());

		UE_LOG(LogTemp, Warning, TEXT("%s HEALTH CHANGED: %f"), *GetName(), Health.GetCurrentValue());
	}
	
}
