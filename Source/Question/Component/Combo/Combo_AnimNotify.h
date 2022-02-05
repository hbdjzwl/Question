// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Combo_AnimNotify.generated.h"

class UComboComponent;

UENUM(BlueprintType)
enum class EComboNotifyState : uint8
{
	NETCOMBO  UMETA(DisplayName = "NexCombo"),
	ENDCOMBO  UMETA(DisplayName = "EndCombo")
};
/**
 * 
 */
UCLASS()
class QUESTION_API UCombo_AnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	virtual FString GetNotifyName_Implementation() const override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EComboNotifyState ComboNotifyState;
};
