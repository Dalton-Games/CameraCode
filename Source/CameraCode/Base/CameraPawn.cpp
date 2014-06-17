

#include "../CameraCode.h"
#include "CameraPawn.h"

#include <UnrealMath.h>

#include <assert.h>

ACameraPawn::ACameraPawn(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
    Sphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("Sphere"));
    Sphere->InitSphereRadius(5.0f);
    RootComponent = Sphere;
    
    CameraArm = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArm"));
    CameraArm->AttachParent = RootComponent;

    MainCamera = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera"));
    MainCamera->AttachParent = CameraArm;

    this->MaxDistance = 2000; // 20 meters
    this->MinDistance = 100;  // 1 meters
    this->MaxPitch = -66;
    this->MinPitch = -45;

    this->Yaw = 0;
    this->Roll = 0;

    this->SetCameraDistance(1.0);


}

void ACameraPawn::SetCameraDistance(float distance)
{
    assert(distance < 1.0 && distance >= 0);

    // Gets distance and pitch angle from max/min and the normalized value
    this->FocusDistance = FMath::Lerp(this->MinDistance, this->MaxDistance, distance);
    this->Pitch = FMath::Lerp(this->MinPitch, this->MaxPitch, distance);

    CameraArm->TargetArmLength = this->FocusDistance;

    FRotator rot(this->Pitch, this->Yaw, this->Roll);
    CameraArm->SetRelativeRotation(rot, true);
}

