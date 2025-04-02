#include "WB_Dialogue.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"

void UWB_Dialogue::NativeConstruct()
{
    Super::NativeConstruct();

    if (SpeakerName)
    {
        SpeakerName->SetText(DialogueUserName);
    }

    if (DialogueText)
    {
        DialogueText->SetText(DialogueTextVariable);
    }
}

void UWB_Dialogue::UpdateDialog(const FText& InText)
{
    if (DialogueText)
    {
        DialogueText->SetText(InText);
    }
}
