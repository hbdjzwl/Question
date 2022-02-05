// Fill out your copyright notice in the Description page of Project Settings.


#include "Combo_AnimNotify.h"
#include "ComboComponent.h"

void UCombo_AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp,Animation);
	if (UActorComponent* ActorComponent = MeshComp->GetOwner()->GetComponentByClass(UComboComponent::StaticClass()))
	{
		switch (ComboNotifyState)
		{
			case EComboNotifyState::NETCOMBO:
				Cast<UComboComponent>(ActorComponent)->GoToNextAttack();
				break;
			case EComboNotifyState::ENDCOMBO:
				Cast<UComboComponent>(ActorComponent)->ResetComboState();
				break;
		}
	}
}

FString UCombo_AnimNotify::GetNotifyName_Implementation() const 
{
	switch (ComboNotifyState)
	{
		case EComboNotifyState::NETCOMBO:	return TEXT("AN_NetCombo");
		case EComboNotifyState::ENDCOMBO:	return TEXT("AN_EndCombo");
	}
	return TEXT("UCombo_AnimNotify");
}
