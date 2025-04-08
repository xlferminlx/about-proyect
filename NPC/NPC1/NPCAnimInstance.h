
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NPCAnimInstance.generated.h"

UCLASS()
class YOURGAME_API UNPCAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC State")
    bool bIsIdle = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC State")
    bool bIsTalking = false;
};
