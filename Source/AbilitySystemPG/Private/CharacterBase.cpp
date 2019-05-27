
#include "CharacterBase.h"

ACharacterBase::ACharacterBase(){
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");


}

void ACharacterBase::BeginPlay(){
	Super::BeginPlay();
	
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


