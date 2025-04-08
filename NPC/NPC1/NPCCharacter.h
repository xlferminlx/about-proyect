
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BPInteract.h"
#include "NPCCharacter.generated.h"

UCLASS()
class YOURGAME_API ANPCCharacter : public AActor, public IBPInteract
{
    GENERATED_BODY()

public:
    ANPCCharacter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    class UNPCAnimInstance* NPCAnimRef;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    bool bIsAlreadyTalking = false;

    UFUNCTION(BlueprintCallable)
    virtual void Interact_Implementation(AActor* Caller) override;

    UFUNCTION(BlueprintCallable)
    virtual void LeaveDialogue_Implementation() override;
};
