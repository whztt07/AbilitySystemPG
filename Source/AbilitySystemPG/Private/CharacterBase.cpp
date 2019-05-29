
#include "CharacterBase.h"

#include "AttributeSetBase.h"

ACharacterBase::ACharacterBase(){
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	AttributeSetBaseComp = CreateDefaultSubobject<UAttributeSetBase>("AttributeSetBaseComp");
	bIsDead = false;
}

void ACharacterBase::BeginPlay(){
	Super::BeginPlay();
	
	if (AttributeSetBaseComp) {
		AttributeSetBaseComp->OnHealthChange.AddDynamic(this, &ACharacterBase::OnHealthChanged);
	}

}

void ACharacterBase::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const{
	return(AbilitySystemComp);
}

void ACharacterBase::AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire){
	if (AbilitySystemComp) {
		if (HasAuthority() && AbilityToAquire) {
			FGameplayAbilitySpecDef SpecDef = FGameplayAbilitySpecDef();
			SpecDef.Ability = AbilityToAquire;
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(SpecDef, 1);
			AbilitySystemComp->GiveAbility(AbilitySpec);
		}
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

void ACharacterBase::OnHealthChanged(float Health, float MaxHealth){

	if (Health <= 0.0f && !bIsDead) {
		bIsDead = true;
		BP_Die();
	}

	BP_OnHealthChanged(Health, MaxHealth);
}


