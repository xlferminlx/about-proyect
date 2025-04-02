#include "DialogueComponent.h"
#include "WB_Dialogue.h"
#include "WB_Options.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"

UDialogueComponent::UDialogueComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    bEndDialogue = false;
}

void UDialogueComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UDialogueComponent::Interact()
{
    if (bEndDialogue || !DataTable || RowName.IsNone()) return;
    StartDialogue();
}

void UDialogueComponent::StartDialogue()
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!PC || !DialogueWidgetClass) return;

    DialogueWidget = CreateWidget<UWB_Dialogue>(PC, DialogueWidgetClass);
    if (!DialogueWidget) return;

    DialogueWidget->AddToViewport();

    FInputModeGameAndUI InputMode;
    InputMode.SetWidgetToFocus(DialogueWidget->TakeWidget());
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    PC->SetInputMode(InputMode);
    PC->bShowMouseCursor = true;

    LoadDialogueRow();
}

void UDialogueComponent::LoadDialogueRow()
{
    if (!DataTable) return;

    const FDialogStructure* Row = DataTable->FindRow<FDialogStructure>(RowName, TEXT("Load Dialogue"));
    if (!Row || !DialogueWidget) return;

    DialogueWidget->UpdateDialog(Row->Dialogue);

    if (DialogueWidget->OptionScrollBox)
    {
        DialogueWidget->OptionScrollBox->ClearChildren();
    }

    RowName = Row->Row;
    DataTable = Row->DataTable;
    bEndDialogue = Row->EndDialogue;

    if (bEndDialogue)
    {
        EndDialogueSequence();
        return;
    }

    if (Row->OpenEndedDialogueOptions.Num() > 0)
    {
        CreateOptions(Row->OpenEndedDialogueOptions);
    }
}

void UDialogueComponent::OptionSelected(FName InRowName, UDataTable* InDataTable)
{
    if (!InDataTable || InRowName.IsNone() || !DialogueWidget) return;

    const FDialogStructure* Row = InDataTable->FindRow<FDialogStructure>(InRowName, TEXT("Option Selected"));
    if (!Row) return;

    if (DialogueWidget->OptionScrollBox)
    {
        DialogueWidget->OptionScrollBox->ClearChildren();
    }

    DialogueWidget->UpdateDialog(Row->Dialogue);

    RowName = Row->Row;
    DataTable = Row->DataTable;
    bEndDialogue = Row->EndDialogue;

    if (bEndDialogue)
    {
        EndDialogueSequence();
        return;
    }

    if (Row->OpenEndedDialogueOptions.Num() > 0)
    {
        CreateOptions(Row->OpenEndedDialogueOptions);
    }
}

void UDialogueComponent::EndDialogueSequence()
{
    if (DialogueWidget)
    {
        DialogueWidget->RemoveFromParent();
        DialogueWidget = nullptr;
    }

    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PC)
    {
        PC->SetInputMode(FInputModeGameOnly());
        PC->bShowMouseCursor = false;
    }
}

void UDialogueComponent::CreateOptions(const TArray<FOptionsDialogStructure>& Options)
{
    if (!DialogueWidget || !OptionWidgetClass) return;

    for (const FOptionsDialogStructure& Option : Options)
    {
        UWB_Options* OptionWidget = CreateWidget<UWB_Options>(GetWorld(), OptionWidgetClass);
        if (!OptionWidget) continue;

        OptionWidget->Name = Option.OptionName;
        OptionWidget->RowName = Option.Row;
        OptionWidget->DataTable = Option.DataTable;
        OptionWidget->DialogueComponent = this;

        if (DialogueWidget->OptionScrollBox)
        {
            DialogueWidget->OptionScrollBox->AddChild(OptionWidget);
        }
    }
}
