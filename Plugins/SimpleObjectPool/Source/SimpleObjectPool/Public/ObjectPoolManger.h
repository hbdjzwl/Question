// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"
#include "ObjectPoolManger.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ObjectPoolLog, Log, All);


UENUM(BlueprintType)
enum class EAllocationType : uint8 
{
	Lazy,	/*- 用时分配 -*/
	Eager	/*- 预先分配 -*/
};

UCLASS(BlueprintType, Blueprintable)
class SIMPLEOBJECTPOOL_API AObjectPoolManger : public AActor
{
	GENERATED_BODY()

public:
	friend class ISimpleObjectPoolInterface;

	UPROPERTY(EditAnywhere,	BlueprintReadOnly)
	TSubclassOf<AActor> ObjectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 1, ClampMax = 500))
	int32 PoolMaxSize {1};

	int32 PoolCurrentSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EAllocationType AllocationType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "AllocationType == EAllocationType::Lazy"))
	int32 LazyPreallocatedSize {0};

	UFUNCTION(BlueprintCallable)
	void ClearPool();
	

	


	UFUNCTION(BlueprintCallable)
	void ForceGarbageCollection();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void BeginPlay();
private:
	void InitializePool();
	void SpawnObject(int32 SpawnSize);
	void PushObject(TWeakObjectPtr<AActor> InObject);
	UPROPERTY()
	TArray<AActor*> Pool;

public:
	AActor* PopObject_Manager(const FTransform& SpawnTransform);

};
