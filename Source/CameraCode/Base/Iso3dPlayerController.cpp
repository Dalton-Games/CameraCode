

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
    
    // Control by axis of the camera (WASD and gamepad)
    InputComponent->BindAxis("MoveForward", this, &AIso3dPlayerController::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &AIso3dPlayerController::MoveRight);
    InputComponent->BindAxis("Zoom", this, &AIso3dPlayerController::Zoom); // Not use this for mouse wheel, only for mapping gamepad control of zoom

    // Control by action of the camera (Mouse wheel, etc...)
    InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AIso3dPlayerController::ZoomIn);
    InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AIso3dPlayerController::ZoomOut);
}

void AIso3dPlayerController::MoveForward (float val)
{
    auto pawn = this->GetControlledPawn();
    if (pawn->IsA(ACameraPawn::StaticClass())) { // A bit redundant, but this way allow to expand i na future to use different type of Pawns
        auto camera = Cast<ACameraPawn>(pawn);
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
        camera->Zoom(val); // Axis value should be 0.1 or -0.1
    }
}

void AIso3dPlayerController::ZoomIn()
{
    auto pawn = this->GetControlledPawn();
    if (pawn->IsA(ACameraPawn::StaticClass())) {
        auto camera = Cast<ACameraPawn>(pawn);
        camera->Zoom(0.1); // TODO Put this value in variable so could be changed in blueprints defaults
    }
}


void AIso3dPlayerController::ZoomOut()
{
    auto pawn = this->GetControlledPawn();
    if (pawn->IsA(ACameraPawn::StaticClass())) {
        auto camera = Cast<ACameraPawn>(pawn);
        camera->Zoom(-0.1);
    }
}
