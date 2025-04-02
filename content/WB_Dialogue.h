#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WB_Dialogue.generated.h"

UCLASS()
class YOURGAME_API UWB_Dialogue : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* DialogueText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* SpeakerName;

    UPROPERTY(meta = (BindWidget))
    class UScrollBox* OptionScrollBox;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
    FText DialogueUserName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
    FText DialogueTextVariable;

    UFUNCTION(BlueprintCallable)
    void UpdateDialog(const FText& InText);

protected:
    virtual void NativeConstruct() override;
};
