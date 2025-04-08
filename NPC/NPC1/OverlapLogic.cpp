
// In the constructor or BeginPlay of AThirdPersonCharacter

// Assuming you have a USphereComponent* called InteractionSphere created in the constructor

InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AThirdPersonCharacter::OnOverlapBegin);
InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &AThirdPersonCharacter::OnOverlapEnd);

// Functions
void AThirdPersonCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this) return;

    if (OtherActor->GetClass()->ImplementsInterface(UBPInteract::StaticClass()))
    {
        TArray<UActorComponent*> Components = OtherActor->GetComponentsByInterface(UBPInteract::StaticClass());
        if (Components.Num() > 0)
        {
            DialogActor = OtherActor;
        }
    }
}

void AThirdPersonCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (DialogActor && DialogActor == OtherActor)
    {
        if (DialogActor->GetClass()->ImplementsInterface(UBPInteract::StaticClass()))
        {
            IBPInteract::Execute_LeaveDialogue(DialogActor);
        }

        DialogActor = nullptr;
    }
}
