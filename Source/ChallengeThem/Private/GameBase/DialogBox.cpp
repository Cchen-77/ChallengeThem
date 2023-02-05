// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBase/DialogBox.h"

// Sets default values
ADialogBox::ADialogBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADialogBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADialogBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

