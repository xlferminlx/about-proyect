
#include "NPCCharacter.h"
#include "NPCAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"

ANPCCharacter::ANPCCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ANPCCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ANPCCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ANPCCharacter::Interact_Implementation(AActor* Caller)
{
    UKismetSystemLibrary::PrintString(this, TEXT("INTERACT CALLED"));

    if (bIsAlreadyTalking)
    {
        if (NPCAnimRef)
        {
            NPCAnimRef->bIsTalking = true;
        }
    }
    else
    {
        if (NPCAnimRef)
        {
            NPCAnimRef->bIsIdle = true;
        }
        bIsAlreadyTalking = true;
    }
}

void ANPCCharacter::LeaveDialogue_Implementation()
{
    bIsAlreadyTalking = false;
    if (NPCAnimRef)
    {
        NPCAnimRef->bIsTalking = false;
    }
}
