#pragma once

#include "CoreMinimal.h"
#include "SimpleObjectPoolInterface.h"
#include "Pool_Actor.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SIMPLEOBJECTPOOL_API APool_Actor : public AActor , public ISimpleObjectPoolInterface
{
	GENERATED_UCLASS_BODY()
	//GENERATED_BODY()
public:
// 	APool_Actor();
// 	~APool_Actor();
	virtual void ObjectPreinitialized(TWeakObjectPtr<AObjectPoolManger> InOwningPool);
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static APool_Actor* SpawnActorFromPool(const UObject* WorldContextObject, AObjectPoolManger* InPool,const FTransform& SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride);

	UFUNCTION(BlueprintCallable)
	void PushObjectInPool();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	AObjectPoolManger* GetOwningPool();
};
