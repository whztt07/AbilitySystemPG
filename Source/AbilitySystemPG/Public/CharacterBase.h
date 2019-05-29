#pragma once

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UAttributeSetBase;

UCLASS()
class ABILITYSYSTEMPG_API ACharacterBase : public ACharacter, public IAbilitySystemInterface{

	GENERATED_BODY()

public:
	ACharacterBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	void AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterBase")
	UAbilitySystemComponent* AbilitySystemComp;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterBase")
	UAttributeSetBase* AttributeSetBaseComp;

	UFUNCTION()
	void OnHealthChanged(float Health, float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnHealthChanged"))
	void BP_OnHealthChanged(float Health, float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "Die"))
	void BP_Die();

protected:


	bool bIsDead{false};



};
