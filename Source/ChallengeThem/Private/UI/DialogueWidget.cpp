// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DialogueWidget.h"
#include"Kismet/GameplayStatics.h"
#include"GameBase/CHTHUD.h"
void UDialogueWidget::InitTexts() {
	TextIndex = 0;
	CharacterIndex = 0;
	SigmaTime = 0;
	Texts.Empty();
	NowText = "";
	CanbeContinue = false;
}
void UDialogueWidget::DialogueContinue() {
	if (!CanbeContinue) return;
	++TextIndex;
	CharacterIndex = 0;
	NowText = "";
	if (TextIndex >= Texts.Num()) {
		DialogueOver();
		return;
	}
	TextRefresh();
	if (Texts[TextIndex].Len() <= 0) {
		DialogueContinue();
	}
	CanbeContinue = false;
}
void UDialogueWidget::DialogueOver() {
	if (auto PC = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
		if (auto CHTHUD = Cast<ACHTHUD>(PC->GetHUD())) {
			CHTHUD->RemoveDialogueWidget();
		}
	}
}
void UDialogueWidget::Write(float DeltaTime) {
	if (CanbeContinue) return;
	if (TextIndex >= Texts.Num()) {
		DialogueOver();
		return;
	}
	if (CharacterIndex == Texts[TextIndex].Len()) {
		WriteFinish();
		return;
	}
	check(CharacterPerSecond > 0);
	SigmaTime += DeltaTime;
	float SecondPerCharacter = 1.0f / CharacterPerSecond;
	while (SigmaTime >= SecondPerCharacter) {
		SigmaTime -= SecondPerCharacter;
		NowText.AppendChar(Texts[TextIndex][CharacterIndex++]);
		TextRefresh();
	}
}
void UDialogueWidget::WriteFinish() {
	CanbeContinue = true;
	UE_LOG(LogTemp, Display, TEXT("FINISH"));
}
void UDialogueWidget::SetTexts(const TArray<FString>& DialogueTexts) {
	Texts = DialogueTexts;
}