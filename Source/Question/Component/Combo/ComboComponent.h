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

	UFUNCTION(BlueprintCallable)
	void TryComboAttack(FKey InputKey);

public:
	UPROPERTY(EditAnywhere)
	UDataTable* ComboConfigData;

	void LoadComboData();

	UPROPERTY(BlueprintReadOnly)
	TArray<FKey> InputKeys;

	UPROPERTY(BlueprintReadOnly)
	TArray<FComboAnim> ComboAnimArray;

private:
	FString CurrentKey;
	ACharacter* OWnerCharacter;
};
