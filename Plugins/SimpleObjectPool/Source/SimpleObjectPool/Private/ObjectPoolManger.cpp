#include "ObjectPoolManger.h"
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

	ClearPool();
}



void AObjectPoolManger::ClearPool()
{
	if (!Pool.IsValidIndex(0)) 
	{ 
		UE_LOG(ObjectPoolLog, Log, TEXT("ClearPool() return"));
		return; 
	}
	
// 	for (int32 ID = Pool.Num() - 1; ID >= 0; --ID)
// 	{
// 		if (Pool[ID]->IsValidLowLevelFast())
// 		{
// 			Pool[ID]->Destroy(true);
// 		}
// 	}

	Pool.Empty();
	UE_LOG(ObjectPoolLog, Log, TEXT("ClearPool()"));

}

void AObjectPoolManger::SpawnObject(int32 SpawnSize)
{
	const FTransform InitTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector(1.f, 1.f, 1.f));
	for (int32 i = 0; i < SpawnSize; i++)
	{
		UE_LOG(ObjectPoolLog, Log, TEXT("---- %s"), this->GetOwner() ? TEXT("true") : TEXT("false"));

		//if (auto LocalNewObject = GetWorld()->SpawnActorDeferred<AActor>(ObjectClass, InitTransform, this->GetOwner(), nullptr/*GetOwner()->GetInstigator()*/, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn))
		if (auto LocalNewObject = GetWorld()->SpawnActor(ObjectClass,&InitTransform))
		{
			//LocalNewObject->FinishSpawning(InitTransform);
			Pool.Add(LocalNewObject);

			if (ISimpleObjectPoolInterface* ObjectInterface = Cast<ISimpleObjectPoolInterface>(LocalNewObject))
			{
				ObjectInterface->OwningPool = this;
				ObjectInterface->Execute_PoolInitialize(LocalNewObject);
			}
			else if(UFunction* p_Func = LocalNewObject->FindFunction("SetObjectPoolManger"))
			{
				//ObjectInterface->OwningPool = this;
				//UObjectProperty* FloatProp;
				//FloatProp = FindFieldChecked<UObjectProperty>(LocalNewObject->GetClass(), "MyActor");

				LocalNewObject->ProcessEvent(p_Func,nullptr);
			}
			
		}
	}
}

ATestActor::ATestActor()
{
	UE_LOG(ObjectPoolLog, Log, TEXT("ATestActoe() --- Construct"));
}

ATestActor::~ATestActor()
{
	UE_LOG(ObjectPoolLog, Log, TEXT("ATestActoe() --- Destruct"));
}

void ATestActor::PoolInitialize_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("C++≥ı ºªØ"));
}
