// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"
#include "SimpleObjectPoolInterface.h"
#include "ObjectPoolManger.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ObjectPoolLog, Log, All);

UCLASS(BlueprintType, Blueprintable)
class ATestActor : public AActor, public ISimpleObjectPoolInterface
{
	GENERATED_BODY()
public:
	ATestActor();
	~ATestActor();
	virtual void PoolInitialize_Implementation() override;
};

UENUM(BlueprintType)
enum class EAllocationType : uint8 
{
	Lazy,	/*- 用时分配 -*/
	Eager	/*- 预先分配 -*/
};


UCLASS(BlueprintType, Blueprintable)
class AObjectPoolManger : public AActor
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly,	BlueprintReadOnly)
	TSubclassOf<AActor> ObjectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 1, ClampMax = 500))
	int32 PoolMaxSize {1};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAllocationType AllocationType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "AllocationType == EAllocationType::Lazy"))
	int32 LazyPreallocatedSize {0};

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void BeginPlay();

private:
	void InitializePool();
	void ClearPool();
	void SpawnObject(int32 SpawnSize);
	UPROPERTY()
	TArray<AActor*> Pool;
};
