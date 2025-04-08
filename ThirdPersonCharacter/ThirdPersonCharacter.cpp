
#include "ThirdPersonCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/BPInteract.h"
#include "DrawDebugHelpers.h"

AThirdPersonCharacter::AThirdPersonCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AThirdPersonCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void AThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AThirdPersonCharacter::Move);
        EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AThirdPersonCharacter::Look);
        EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &AThirdPersonCharacter::StartJump);
        EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &AThirdPersonCharacter::StopJump);
        EIC->BindAction(TalkAction, ETriggerEvent::Started, this, &AThirdPersonCharacter::Talk);
        EIC->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AThirdPersonCharacter::Interact);
    }
}

void AThirdPersonCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D Movement = Value.Get<FVector2D>();
    const FRotator Rotation = Controller->GetControlRotation();

    const FVector Forward = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
    const FVector Right = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

    AddMovementInput(Forward, Movement.Y);
    AddMovementInput(Right, Movement.X);
}

void AThirdPersonCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxis = Value.Get<FVector2D>();
    AddControllerYawInput(LookAxis.X);
    AddControllerPitchInput(LookAxis.Y);
}

void AThirdPersonCharacter::StartJump()
{
    Jump();
}

void AThirdPersonCharacter::StopJump()
{
    StopJumping();
}

void AThirdPersonCharacter::Talk()
{
    if (DialogActor && DialogActor->GetClass()->ImplementsInterface(UBPInteract::StaticClass()))
    {
        IBPInteract::Execute_Interact(DialogActor, this);
    }
}

void AThirdPersonCharacter::Interact()
{
    FVector Start = GetActorLocation();
    FVector End = Start + GetActorForwardVector() * 300.0f;

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
    {
        AActor* HitActor = Hit.GetActor();
        if (HitActor && HitActor->GetClass()->ImplementsInterface(UBPInteract::StaticClass()))
        {
            IBPInteract::Execute_Interact(HitActor, this);
        }
    }

    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f);
}
