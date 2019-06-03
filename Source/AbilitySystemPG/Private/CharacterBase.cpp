 
#include "CharacterBase.h"

#include "AttributeSetBase.h"

// ENGINE
#include "AIController.h"
#include "GameFramework/PlayerController.h"
#include "BrainComponent.h"

ACharacterBase::ACharacterBase(){
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	AttributeSetBaseComp = CreateDefaultSubobject<UAttributeSetBase>("AttributeSetBaseComp");
	bIsDead = false;
	TeamID = 255;
}

void ACharacterBase::BeginPlay(){
	Super::BeginPlay();
	
	if (AttributeSetBaseComp) {
		AttributeSetBaseComp->OnHealthChange.AddDynamic(this, &ACharacterBase::OnHealthChanged);
		AttributeSetBaseComp->OnManaChange.AddDynamic(this, &ACharacterBase::OnManaChange);
		AttributeSetBaseComp->OnStrengthChange.AddDynamic(this, &ACharacterBase::OnStrengthChange);
	}
	AutoDetermineTeamIDByControllerType();
	AddGameplayTag(FullHealthTag);
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
		Dead();
		BP_Die();
	}

	BP_OnHealthChanged(Health, MaxHealth);
}

void ACharacterBase::OnManaChange(float Mana, float MaxMana){
	BP_OnManaChange(Mana, MaxMana);
}

void ACharacterBase::OnStrengthChange(float Strength, float MaxStrength){
	BP_OnStrengthChange(Strength, MaxStrength);
}

bool ACharacterBase::IsOtherHostile(ACharacterBase* Other){
	return(TeamID != Other->GetTeamId());
}

void ACharacterBase::AddGameplayTag(FGameplayTag& TagToAdd){
	GetAbilitySystemComponent()->AddLooseGameplayTag(TagToAdd);
	GetAbilitySystemComponent()->SetTagMapCount(TagToAdd, 1);
}

void ACharacterBase::RemoveGameplayTag(FGameplayTag& TagToRemove){
	GetAbilitySystemComponent()->RemoveLooseGameplayTag(TagToRemove);
}

void ACharacterBase::AutoDetermineTeamIDByControllerType(){
	TeamID = (GetController() && GetController()->IsPlayerController()) ? 0 : 1;
}

void ACharacterBase::Dead(){
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC) {
		PC->DisableInput(PC);
	}

	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC) {
		AIC->GetBrainComponent()->StopLogic("Dead");
	}

}


