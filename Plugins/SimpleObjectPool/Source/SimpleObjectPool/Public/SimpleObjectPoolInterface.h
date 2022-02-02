// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SimpleObjectPoolInterface.generated.h"

class AObjectPoolManger;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
//UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))
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

	TWeakObjectPtr<AObjectPoolManger> OwningPool;
	TWeakObjectPtr<AActor> ThisActorPtr;

	//Is called only on the first initialization
	virtual void ObjectPreinitialized(TWeakObjectPtr<AObjectPoolManger> InOwningPool);
	//Is called only on the first initialization
	UFUNCTION(BlueprintImplementableEvent)
	void BP_ObjectPreinitialized();

	void PopObject();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_PopObject();

	//void Begin();
	void PushObject();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_PushObject();

};

