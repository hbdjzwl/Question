#include "ObjectPoolManger.h"
#include "SimpleObjectPoolInterface.h"


DEFINE_LOG_CATEGORY(ObjectPoolLog);

#if WITH_EDITOR
void AObjectPoolManger::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.GetPropertyName().ToString() == TEXT("LazyPreallocatedSize")
	|| PropertyChangedEvent.GetPropertyName().ToString() == TEXT("PoolMaxSize"))
	{
		LazyPreallocatedSize = FMath::Clamp(LazyPreallocatedSize, 0, PoolMaxSize);
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void AObjectPoolManger::BeginPlay()
{
	Super::BeginPlay();
	InitializePool();

	UE_LOG(ObjectPoolLog, Warning, TEXT("Number--%i"), Pool.Num());

	for (auto& r : Pool)
	{
		UE_LOG(ObjectPoolLog, Warning, TEXT("Name:%s"),*r->GetName());
	}
}

void AObjectPoolManger::InitializePool()
{

	if (ObjectClass == nullptr)
	{
		UE_LOG(ObjectPoolLog,Warning,TEXT("Invalid Object Class!"));
		return;
	}

	if (!ObjectClass->ImplementsInterface(USimpleObjectPoolInterface::StaticClass()))
	{
		UE_LOG(ObjectPoolLog, Warning, TEXT("ObjectClass must inherit ISimpleObjectPoolInterface!"));
		return;
	}

	ClearPool();

	switch (AllocationType)
	{
	case EAllocationType::Lazy:
		SpawnObject(LazyPreallocatedSize);
		break;
	case EAllocationType::Eager:
		SpawnObject(PoolMaxSize);
		break;
	default:
		ensure(0 && "AllocationType error");
		break;
	}

}



void AObjectPoolManger::ClearPool()
{
	if (!Pool.IsValidIndex(0)) 
	{ 
		return; 
	}
	
	for (int32 ID = Pool.Num() - 1; ID >= 0; --ID)
	{
		if (Pool[ID]->IsValidLowLevelFast())
		{
			Pool[ID]->Destroy(true);
		}
	}
	PoolCurrentSize = 0;
	Pool.Empty();
	UE_LOG(ObjectPoolLog, Log, TEXT("ClearPool()"));
}

void AObjectPoolManger::PushObject(TWeakObjectPtr<AActor> InObject)
{
	Pool.Add(InObject.Get());
}

AActor* AObjectPoolManger::PopObject_Manager(const FTransform& SpawnTransform)
{
	if (!(Pool.Num() > 0))
	{
		if (PoolCurrentSize >= PoolMaxSize)
		{
			UE_LOG(ObjectPoolLog, Warning, TEXT("Pool Array Num is 0"));
			return nullptr;
		}
		SpawnObject(1);
	}

	AActor* LocalPtr = Pool[Pool.Num()-1];
	LocalPtr->SetActorTransform(SpawnTransform);

	Cast<ISimpleObjectPoolInterface>(LocalPtr)->PopObject();

	Pool.RemoveAt(Pool.Num() - 1);

	for (auto& r : Pool)
	{
		UE_LOG(ObjectPoolLog, Warning, TEXT("Number:%i ---- PopName:%s"), Pool.Num(),*r->GetName());
	}

	return LocalPtr;
}

void AObjectPoolManger::ForceGarbageCollection()
{
	GEngine->ForceGarbageCollection(true);
}

void AObjectPoolManger::SpawnObject(int32 SpawnSize)
{
	const FTransform InitTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector(1.f, 1.f, 1.f));
	for (int32 i = 0; i < SpawnSize; i++)
	{
		UE_LOG(ObjectPoolLog, Log, TEXT("---- %s"), this->GetOwner() ? TEXT("true") : TEXT("false"));

		//if (auto LocalNewObject = GetWorld()->SpawnActor(ObjectClass,&InitTransform))
		if (auto LocalNewObject = GetWorld()->SpawnActorDeferred<AActor>(ObjectClass, InitTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn))
		{
			Pool.Add(LocalNewObject);
			PoolCurrentSize++;
			if (ISimpleObjectPoolInterface* ObjectInterface = Cast<ISimpleObjectPoolInterface>(LocalNewObject))
			{
				ObjectInterface->ObjectPreinitialized(this);
			}

			LocalNewObject->FinishSpawning(InitTransform);
		}
	}
}




