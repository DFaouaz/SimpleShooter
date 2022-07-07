// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDWidget = CreateWidget(this, HUDClass);
	if (HUDWidget != nullptr)
	{
		HUDWidget->AddToViewport();
	}
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (HUDWidget != nullptr)
	{
		HUDWidget->RemoveFromViewport();
	}

	UUserWidget* EndScreen = CreateWidget(this, bIsWinner ? WinScreenClass : LoseScreenClass);
	if (EndScreen != nullptr)
	{
		EndScreen->AddToViewport();
	}

	GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &APlayerController::RestartLevel, RestartDelay);
}
