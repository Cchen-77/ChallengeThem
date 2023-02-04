// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBase/CHTGameInstance.h"
#include"Character/CHTPlayerCharacter.h"
#include"GameBase/CHTCheckpoint.h"
#include"GameBase/CHTGameStateBase.h"
#include"Kismet/GameplayStatics.h"
#include"GameBase/CHTResetInterface.h"
#include"GameFramework/GameUserSettings.h"
#include"MoviePlayer.h"
void UCHTGameInstance::Init() {
	Super::Init();
	GEngine->GetGameUserSettings()->SetScreenResolution(FIntPoint(1920, 1080));
	GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Fullscreen);
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UCHTGameInstance::StartLoadingScreen);
}
void UCHTGameInstance::StartLoadingScreen(const FString& MapName)
{
	if (!IsRunningDedicatedServer()) {
		FLoadingScreenAttributes LoadingScreenAttributes;
		LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = false;
		LoadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
	}
}
APawn* UCHTGameInstance::ResetToCheckpoint()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UCHTResetInterface::StaticClass(), OutActors);
	for (AActor* ResetActor : OutActors) {
		if (auto CHTResetActor = Cast<ICHTResetInterface>(ResetActor)) {
			CHTResetActor->Reset();
		}
	}
	FRotator RespawnRotation = FRotator(0, 0, 0);
	FVector RespawnLocation = FVector(0, 0, 0);
	auto CHTGameState = Cast<ACHTGameStateBase>(GetWorld()->GetGameState());
	auto Checkpoint = CHTGameState->GetCheckpoint();
	if (Checkpoint) {
		RespawnLocation = Checkpoint->GetActorLocation();
	}
	auto PlayerPawnClass = UGameplayStatics::GetGameMode(GetWorld())->DefaultPawnClass;
	auto NewPawn = Cast<APawn>(GetWorld()->SpawnActor(PlayerPawnClass,&RespawnLocation,&RespawnRotation));
	check(NewPawn);
	return NewPawn;
	
}
