// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include"GameBase/CHTResetInterface.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGETHEM_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitTexts();
	void SetTexts(const TArray<FString>& DialogueTexts);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Write)
		int CharacterPerSecond = 3;
	int TextIndex = 0;
	TArray<FString> Texts;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Write)
	FString NowText = "";
	UFUNCTION(BlueprintCallable)
	void DialogueContinue();
	void DialogueOver();
	float SigmaTime = 0;
	UFUNCTION(BlueprintCallable)
	void Write(float DeltaTime);
	void WriteFinish();
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = Write)
	bool CanbeContinue = false;
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void TextRefresh();
	int CharacterIndex = 0;
};
