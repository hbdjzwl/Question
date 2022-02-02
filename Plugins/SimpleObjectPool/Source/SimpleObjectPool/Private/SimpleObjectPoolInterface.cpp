// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleObjectPoolInterface.h"
//#include "UObject/UObjectBase.h"
#include "ObjectPoolManger.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/PrimitiveComponent.h"

void ActivatedOrDeactivated(TWeakObjectPtr<AActor> InActor,bool Activated)
{
	InActor->SetActorHiddenInGame(Activated ? false : true);
	InActor->SetActorTickEnabled(Activated ? true : false);
	InActor->SetActorEnableCollision(Activated ? true : false);

	TInlineComponentArray<UActorComponent*>Components;
	InActor->GetComponents(Components);

	for (UActorComponent* Component : Components) {
		const auto& PS = Cast<UParticleSystemComponent>(Component);
		if (PS) { PS->DeactivateSystem(); }

		Component->SetActive(Activated ? true : false);
		Component->SetComponentTickEnabled(Activated ? true : false);

		const auto& LocalPrimitiveComponent = Cast<UPrimitiveComponent>(Component);
		if (LocalPrimitiveComponent && !LocalPrimitiveComponent->IsA(UParticleSystemComponent::StaticClass()))
		{
			LocalPrimitiveComponent->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
			LocalPrimitiveComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
			LocalPrimitiveComponent->SetComponentTickEnabled(Activated ? true : false);
			//LocalPrimitiveComponent->SetSimulatePhysics(Activated ? true : false);
			LocalPrimitiveComponent->SetCollisionEnabled(Activated ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
			LocalPrimitiveComponent->SetVisibility(Activated ? true : false, Activated ? true : true);

		}
	}
}

void ISimpleObjectPoolInterface::ObjectPreinitialized(TWeakObjectPtr<AObjectPoolManger> InOwningPool)
{
	ThisActorPtr = Cast<AActor>(this);
	check(ThisActorPtr.Get() && "ObjectClass must inherit AActor Or subclasses of AActor!");

	OwningPool = InOwningPool;
	UE_LOG(LogTemp, Error, TEXT("--------------== SetPool ==---------------"));
	ActivatedOrDeactivated(ThisActorPtr,false);
	ISimpleObjectPoolInterface::Execute_BP_ObjectPreinitialized(Cast<AActor>(this));
}

void ISimpleObjectPoolInterface::PopObject()
{
	ActivatedOrDeactivated(ThisActorPtr,true);
	ISimpleObjectPoolInterface::Execute_BP_PopObject(Cast<AActor>(this));

}

void ISimpleObjectPoolInterface::PushObject()
{
	ActivatedOrDeactivated(ThisActorPtr,false);
	ISimpleObjectPoolInterface::Execute_BP_PushObject(Cast<AActor>(this));
	OwningPool.Get()->PushObject(ThisActorPtr);
}
