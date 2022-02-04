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
	OWnerCharacter = Cast<ACharacter>(GetOwner());
	check(OWnerCharacter && TEXT("ComboComponents can only hang on ACharacter!"));
	LoadComboData();
}


void UComboComponent::TryComboAttack(FKey InputKey)
{
	if (InputKeys.Contains(InputKey))
	{
		CurrentKey = InputKey.ToString();
		FComboAnim* LocalCurrentAttack  = &ComboAnimArray[CurrentKey.Len()-1];
		OWnerCharacter->GetMesh();
	}
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

				LocalInputKey = LocalInputKey + CurrentRow->ComboConfigInfo[i].InputKey.ToString();
				bool bFnish = i + 1 < CurrentRow->ComboConfigInfo.Num() ? false : true;	//是否是最后一个结束技能
				FAnimInfo LocalAnimInfo{ CurrentRow->ComboConfigInfo[i].AnimMontage ,bFnish };

// 				TPair<FString, FAnimInfo> a;
//				TTuple<FString, FAnimInfo> A;
// 				ComboAnimArray[i].ComboAnimInfo.Add(a);

				FComboAnim* ptr = new FComboAnim();
				if (i >= ComboAnimArray.Num())
				{
					TMap<FString, FAnimInfo> TempMap;
					TempMap.Add(LocalInputKey,LocalAnimInfo);
					ComboAnimArray.Add(FComboAnim{ TempMap });
				}
				else
				{
					ComboAnimArray[i].ComboAnimInfo.Add(LocalInputKey, LocalAnimInfo);
				}
			}
		}
	}
}

