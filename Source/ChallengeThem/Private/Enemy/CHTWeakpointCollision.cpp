// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/CHTWeakpointCollision.h"
void UCHTWeakpointCollision::BeHit() {
	OnWeakpointHit.Broadcast();
}
