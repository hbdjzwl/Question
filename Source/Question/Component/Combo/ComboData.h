// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ComboData.generated.h"

class UAnimMontage;

/*bengin-------------- ComboComponent ���浱ǰ������Ϣ -------------*/
USTRUCT(BlueprintType)
struct QUESTION_API FAnimInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	UAnimMontage* AnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	bool bFinish;
};

USTRUCT(BlueprintType)
struct QUESTION_API FComboAnim
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	TMap<FString, FAnimInfo> ComboAnimInfo;
};
/*end-------------- ComboComponent ���浱ǰ������Ϣ -------------*/



/*begin------------- ����Combo���е��������ݱ� -------------*/
USTRUCT(BlueprintType)
struct QUESTION_API FComboConfigInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	FKey InputKey;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	UAnimMontage* AnimMontage;
};

USTRUCT(BlueprintType)
struct QUESTION_API FComboConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	TArray<FComboConfigInfo> ComboConfigInfo;
};


USTRUCT(BlueprintType)
struct QUESTION_API FComboConfigData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	FComboConfig ComboConfig;
};

/*end------------- ����Combo���е��������ݱ� -------------*/
