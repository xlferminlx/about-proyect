#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WB_Options.generated.h"

class UDialogueComponent;

UCLASS()
class YOURGAME_API UWB_Options : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    class UButton* OptionButton;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* OptionName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FName Name;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FName RowName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UDataTable* DataTable;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UDialogueComponent* DialogueComponent;

protected:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void OnOptionClicked();
};
