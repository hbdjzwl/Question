// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ComboData.h"
#include "ComboComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTION_API UComboComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComboComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	/*----- ³¢ÊÔ¹¥»÷ -----*/
	UFUNCTION(BlueprintCallable)
	void TryComboAttack(FKey InputKey);

	/*----- ÏÂÒ»´Î¹¥»÷ -----*/
	UFUNCTION(BlueprintCallable)
	void GoToNextAttack();

	/*----- ÖØÖÃ×´Ì¬ -----*/
	UFUNCTION(BlueprintCallable)
	void ResetComboState();

private:
	void ComboAttack();

	void LoadComboData();

	void OnNotifyBeginReceive(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	void OnNotifyEndReceive(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

public:
	UPROPERTY(EditAnywhere)
	UDataTable* ComboConfigData;

	UPROPERTY(BlueprintReadOnly)
	TArray<FKey> InputKeys;

	UPROPERTY(BlueprintReadOnly)
	TArray<FComboAnim> ComboAnimArray;

	//UPROPERTY(BlueprintAssignable)
	FPlayMontageAnimNotifyDelegate OnNotifyBegin;
	//UPROPERTY(BlueprintAssignable)
	FPlayMontageAnimNotifyDelegate OnNotifyEnd;


private:
	FString CurrentKey;
	ACharacter* OwnerCharacter;
	UAnimInstance* OwnerAnimInstance;
	bool bIsAttacking;
	bool bCanGoToNextAttack;
};

