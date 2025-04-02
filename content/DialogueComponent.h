#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "DialogueComponent.generated.h"

class UWB_Dialogue;
class UWB_Options;
class UScrollBox;

USTRUCT(BlueprintType)
struct FOptionsDialogStructure
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName OptionName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Row;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable* DataTable;
};

USTRUCT(BlueprintType)
struct FDialogStructure
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Dialogue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Row;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable* DataTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool EndDialogue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool OpenEndedDialogue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FOptionsDialogStructure> OpenEndedDialogueOptions;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOURGAME_API UDialogueComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDialogueComponent();

    UFUNCTION(BlueprintCallable)
    void Interact();

    UFUNCTION(BlueprintCallable)
    void OptionSelected(FName InRowName, UDataTable* InDataTable);

protected:
    virtual void BeginPlay() override;

    void StartDialogue();
    void LoadDialogueRow();
    void EndDialogueSequence();
    void CreateOptions(const TArray<FOptionsDialogStructure>& Options);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RowName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable* DataTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UWB_Dialogue> DialogueWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UWB_Options> OptionWidgetClass;

private:
    UPROPERTY()
    UWB_Dialogue* DialogueWidget;

    UPROPERTY()
    bool bEndDialogue;
};
