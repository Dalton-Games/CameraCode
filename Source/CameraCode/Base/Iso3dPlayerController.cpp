

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
    InputComponent->BindAxis("CameraRotateCCW", this, &AIso3dPlayerController::RotateCCW);

    // Control by action of the camera (Mouse wheel, etc...)
    InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AIso3dPlayerController::ZoomIn);
    InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AIso3dPlayerController::ZoomOut);
    
    // Mouse/Touch camera move
    InputComponent->BindAction("CameraMove", IE_Pressed, this, &AIso3dPlayerController::CameraMovePressed);
    InputComponent->BindAction("CameraMove", IE_Released, this, &AIso3dPlayerController::CameraMoveReleased);
}

void AIso3dPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Init internal state flags when we begin the game
    bActive = true;
    bShowMouseCursor = true;

    bCameraMovePressed = false;
    bMouseMoved = false;

    Old3dMouse *= 0;
}

void AIso3dPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (bActive) {
        auto Pawn = this->GetControlledPawn();
        if (Pawn != nullptr && Pawn->IsA(ACameraPawn::StaticClass())) {
            auto Camera = Cast<ACameraPawn>(Pawn);

            float dx, dy;
            GetInputMouseDelta(dx, dy);
            if (bMouseMoved || abs(dx) > 0.1 || abs(dy) > 0.1) { // If the mouse moved ...
                bMouseMoved = true;

                if (bCameraMovePressed) { // Button to move the camera has been pressed
                    FHitResult OutHit;
                    bool bHit;
                    this->GetMouse3dTrace(OutHit, bHit, 20000, ECollisionChannel::ECC_Visibility);
                    if (bHit) {
                        // Move Camera enought to emplace OutHit.Location ~= Old3dMouse
                        FVector NewPos = (Old3dMouse - OutHit.Location) + Camera->GetActorLocation();
                        NewPos.Z = Camera->GetActorLocation().Z;
                        Camera->SetActorLocation(NewPos, true);
                    }
                }

            }
        }
    }
}

// Event handlers ***********************************************************

void AIso3dPlayerController::MoveForward(float val)
{
    if (bActive) {
        auto Pawn = this->GetControlledPawn();
        if (Pawn != nullptr && Pawn->IsA(ACameraPawn::StaticClass())) { // A bit redundant, but this way allow to expand i na future to use different type of Pawns
            auto Camera = Cast<ACameraPawn>(Pawn);
            Camera->MoveForward(val);
        }
    }
}

void AIso3dPlayerController::MoveRight(float val)
{
    if (bActive) {
        auto Pawn = this->GetControlledPawn();
        if (Pawn != nullptr && Pawn->IsA(ACameraPawn::StaticClass())) {
            auto Camera = Cast<ACameraPawn>(Pawn);
            Camera->MoveRight(val);
        }
    }
}

void AIso3dPlayerController::Zoom (float val)
{
    if (bActive) {
        auto Pawn = this->GetControlledPawn();
        if (Pawn != nullptr && Pawn->IsA(ACameraPawn::StaticClass())) {
            auto Camera = Cast<ACameraPawn>(Pawn);
            Camera->Zoom(val); // Axis value should be 0.1 or -0.1
        }
    }
}

void AIso3dPlayerController::ZoomIn()
{
    if (bActive) {
        auto Pawn = this->GetControlledPawn();
        if (Pawn != nullptr && Pawn->IsA(ACameraPawn::StaticClass())) {
            auto Camera = Cast<ACameraPawn>(Pawn);
            Camera->Zoom(0.1); // TODO Put this value in variable so could be changed in blueprints defaults
        }
    }
}


void AIso3dPlayerController::ZoomOut()
{
    if (bActive) {
        auto Pawn = this->GetControlledPawn();
        if (Pawn != nullptr && Pawn->IsA(ACameraPawn::StaticClass())) {
            auto Camera = Cast<ACameraPawn>(Pawn);
            Camera->Zoom(-0.1);
        }
    }
}

void AIso3dPlayerController::RotateCCW(float val)
{
    if (bActive) {
        auto Pawn = this->GetControlledPawn();
        if (Pawn != nullptr && Pawn->IsA(ACameraPawn::StaticClass())) {
            auto Camera = Cast<ACameraPawn>(Pawn);
            Camera->AddYaw(val);
        }
    }
}


void AIso3dPlayerController::CameraMovePressed ()
{
    if (bActive) {
        auto Pawn = this->GetControlledPawn();
        if (Pawn != nullptr && Pawn->IsA(ACameraPawn::StaticClass())) {
            auto Camera = Cast<ACameraPawn>(Pawn);

            bCameraMovePressed = true;
            bMouseMoved = false;

            // Store 3d world coords pointed when we press
            FHitResult OutHit;
            bool bHit;
            this->GetMouse3dTrace(OutHit, bHit, 20000, ECollisionChannel::ECC_Visibility);
            if (bHit) {
                Old3dMouse = OutHit.Location;
            }
        }
    }
}

void AIso3dPlayerController::CameraMoveReleased ()
{
    if (bActive) {
        auto Pawn = this->GetControlledPawn();
        if (Pawn != nullptr && Pawn->IsA(ACameraPawn::StaticClass())) {
            auto Camera = Cast<ACameraPawn>(Pawn);

            bCameraMovePressed = false;
            if (!bMouseMoved) { // Not moved, so it's a "click", so we move the camera to the 3d coords
                
                // Gets 3d position and moves camera to these place
                FHitResult OutHit;
                bool bHit;
                this->GetMouse3dTrace(OutHit, bHit, 20000, ECollisionChannel::ECC_Visibility);
                
                if (bHit) { // TODO Code that enforces Z values to be in floors
                    FVector newLoc = OutHit.Location + FVector(0, 0, Camera->Sphere->GetScaledSphereRadius() * 2 + 0.1f);
                    Camera->SetActorLocation(newLoc, true);
                }

            }
        }
    }
}


void AIso3dPlayerController::GetMouse3dTrace(FHitResult& OutHit, bool& bHit, float distance, ECollisionChannel channel, bool bDrawDebug)
{
    FVector loc, dir;
    this->DeprojectMousePositionToWorld(loc, dir);

    FVector end = (dir * distance) + loc; 

    FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
    RV_TraceParams.bTraceComplex = false;
    RV_TraceParams.bTraceAsyncScene = true;
    RV_TraceParams.bReturnPhysicalMaterial = true;
     
    //Re-initialize hit info
    OutHit = FHitResult(ForceInit);
     
    //call GetWorld() from within an actor extending class
    bHit = GetWorld()->LineTraceSingle(
        OutHit,       //result
        loc, //start
        end, //end
        channel, //collision channel
        RV_TraceParams
    );

    // draw debug lines take from KismetSystemLibrary.h
    if (bDrawDebug) {
        if (bHit && OutHit.bBlockingHit) {
            // Red up to the blocking hit, green thereafter
            ::DrawDebugLine(GetWorld(), loc, OutHit.ImpactPoint, FColor::Red, false, 5.f);
            ::DrawDebugLine(GetWorld(), OutHit.ImpactPoint, end, FColor::Green, false, 5.f);
            ::DrawDebugPoint(GetWorld(), OutHit.ImpactPoint, 16.f, FColor::Red, false, 5.f);
        }
        else {
            // no hit means all red
            ::DrawDebugLine(GetWorld(), loc, end, FLinearColor::Red, false, 5.f);
        }
    }
}