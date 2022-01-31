// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SimpleObjectPoolInterface.generated.h"

class AObjectPoolManger;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USimpleObjectPoolInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIMPLEOBJECTPOOL_API ISimpleObjectPoolInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	AObjectPoolManger* OwningPool;

	UFUNCTION(BlueprintCallable)
	virtual void SetObjectPoolManger();

	UFUNCTION(BlueprintNativeEvent)
	void PoolInitialize();
};
