// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboComponent.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UComboComponent::UComboComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UComboComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	OwnerAnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	check(OwnerCharacter && TEXT("ComboComponents can only hang on ACharacter!"));
	LoadComboData();
}


void UComboComponent::TryComboAttack(FKey InputKey)
{
	if (InputKeys.Contains(InputKey))
	{
		//首次攻击
		if (!bIsAttacking)
		{
			bIsAttacking = true;
			CurrentKey = CurrentKey + InputKey.ToString();
			ComboAttack();
		}
		//连招攻击
		else if(!bCanGoToNextAttack)
		{
			bCanGoToNextAttack = true;
			CurrentKey = CurrentKey + InputKey.ToString();
		}
	}


}

void UComboComponent::GoToNextAttack()
{
	if (bIsAttacking && bCanGoToNextAttack)
	{
		bCanGoToNextAttack = false;
		ComboAttack();
	}

}

void UComboComponent::ComboAttack()
{
	const TMap<FString, FAnimInfo>& CurrentComboAnim = ComboAnimArray[CurrentKey.Len() - 1].ComboAnimInfo;

	/*-------  判断攻击连招是否正确 -------*/
	if (const FAnimInfo* LocalAnimMontage = CurrentComboAnim.Find(CurrentKey))
	{
		OwnerCharacter->PlayAnimMontage(LocalAnimMontage->AnimMontage);
		OwnerAnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UComboComponent::OnNotifyBeginReceive);
		OwnerAnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &UComboComponent::OnNotifyEndReceive);

		if (LocalAnimMontage->bFinish)
		{
			//连招结束
			ResetComboState();
		}
	}
	else
	{
		//输错按键
		ResetComboState();
	}
}

void UComboComponent::ResetComboState()
{
	bIsAttacking = false;
	bCanGoToNextAttack = false;
	CurrentKey.Empty();
}

void UComboComponent::LoadComboData()
{

	TArray<FComboConfig*> RowName;
	if (ComboConfigData)
	{
		ComboConfigData->GetAllRows(TEXT("Row"), RowName);

		for (const auto& CurrentRow : RowName)
		{
			FString LocalInputKey;

			//数据表每一行对应一套连招
			for (int i = 0; i < CurrentRow->ComboConfigInfo.Num() ; i++)
			{
				InputKeys.Add(CurrentRow->ComboConfigInfo[i].InputKey);//添加可交互的输入按键

				LocalInputKey = LocalInputKey + CurrentRow->ComboConfigInfo[i].InputKey.ToString();	//连招的Key
				bool bFnish = i + 1 < CurrentRow->ComboConfigInfo.Num() ? false : true;	//是否是最后一个结束技能
				FAnimInfo LocalAnimInfo{ CurrentRow->ComboConfigInfo[i].AnimMontage ,bFnish };
				TPair<FString, FAnimInfo> ComboAnimInfo(LocalInputKey, LocalAnimInfo);


				FComboAnim* ptr = new FComboAnim();
				if (i >= ComboAnimArray.Num())
				{
					TMap<FString, FAnimInfo> TempMap;
					TempMap.Add(ComboAnimInfo);
					ComboAnimArray.Add(FComboAnim{ TempMap });
				}
				else
				{
					ComboAnimArray[i].ComboAnimInfo.Add(ComboAnimInfo);
				}
			}
		}
	}
}

void UComboComponent::OnNotifyBeginReceive(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	
	//OnNotifyBegin.ExecuteIfBound(NotifyName, BranchingPointPayload);
}

void UComboComponent::OnNotifyEndReceive(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	//OnNotifyEnd.ExecuteIfBound(NotifyName, BranchingPointPayload);
}
