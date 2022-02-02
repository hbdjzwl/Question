#include "Object/Pool_Actor.h"
#include "ObjectPoolManger.h"

// APool_Actor::APool_Actor()
// {
// 	UE_LOG(LogTemp, Log, TEXT("APool_Actor() --- Construct"));
// }
// 
// APool_Actor::~APool_Actor()
// {
// 	UE_LOG(LogTemp, Error, TEXT("APool_Actor() --- Destruct"));
// }

APool_Actor::APool_Actor(const FObjectInitializer& OBJ) : Super(OBJ) {

}

void APool_Actor::ObjectPreinitialized(TWeakObjectPtr<AObjectPoolManger> InOwningPool)
{
	ISimpleObjectPoolInterface::ObjectPreinitialized(InOwningPool);

}

APool_Actor* APool_Actor::SpawnActorFromPool(const UObject* WorldContextObject, AObjectPoolManger* InPool, const FTransform& SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride)
{
	if (InPool)
	{
		if (AActor* NewObject = InPool->PopObject_Manager(SpawnTransform))
		{
			return Cast<APool_Actor>(NewObject);
		}
	}

	return nullptr;
}

void APool_Actor::PushObjectInPool()
{
	PushObject();
}

AObjectPoolManger* APool_Actor::GetOwningPool()
{
	return OwningPool.Get();
}

