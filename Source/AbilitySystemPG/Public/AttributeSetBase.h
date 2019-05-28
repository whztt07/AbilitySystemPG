#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeSetBase.generated.h"


UCLASS()
class ABILITYSYSTEMPG_API UAttributeSetBase : public UAttributeSet{
	GENERATED_BODY()

public:

	UAttributeSetBase();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
	FGameplayAttributeData Health;
	


};
