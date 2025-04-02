#include "WB_Options.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "DialogueComponent.h"

void UWB_Options::NativeConstruct()
{
    Super::NativeConstruct();

    if (OptionName)
    {
        OptionName->SetText(FText::FromName(Name));
    }

    if (OptionButton)
    {
        OptionButton->OnClicked.AddDynamic(this, &UWB_Options::OnOptionClicked);
    }
}

void UWB_Options::OnOptionClicked()
{
    if (DialogueComponent)
    {
        DialogueComponent->OptionSelected(RowName, DataTable);
    }
}
