

#include "../CameraCode.h"
#include "Iso3dPlayerController.h"
#include "CameraPawn.h"


AIso3dPlayerController::AIso3dPlayerController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}


void AIso3dPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    // Control by axis of the camera (keys and gamepad)
    InputComponent->BindAxis("MoveForward", this, &AIso3dPlayerController::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &AIso3dPlayerController::MoveRight);
    InputComponent->BindAxis("Zoom", this, &AIso3dPlayerController::Zoom);
    
}

void AIso3dPlayerController::MoveForward (float val)
{
    auto camera = Cast<ACameraPawn>(this->GetControlledPawn());
    if (camera != nullptr) {
        camera->MoveForward(val);
    }
}

void AIso3dPlayerController::MoveRight (float val)
{
    auto pawn = this->GetControlledPawn();
    if (pawn->IsA(ACameraPawn::StaticClass())) {
        auto camera = Cast<ACameraPawn>(pawn);
        camera->MoveRight(val);
    }
}

void AIso3dPlayerController::Zoom (float val)
{
    auto pawn = this->GetControlledPawn();
    if (pawn->IsA(ACameraPawn::StaticClass())) {
        auto camera = Cast<ACameraPawn>(pawn);
        camera->Zoom(val);
    }
}

