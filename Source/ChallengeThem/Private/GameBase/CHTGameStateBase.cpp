// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBase/CHTGameStateBase.h"
void ACHTGameStateBase::SetCheckpoint(ACHTCheckpoint* CHTCheckpoint) {
	Checkpoint = CHTCheckpoint;
}
ACHTCheckpoint* ACHTGameStateBase::GetCheckpoint() const {
	return Checkpoint;
}