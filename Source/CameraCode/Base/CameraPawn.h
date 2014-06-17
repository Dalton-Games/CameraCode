

#pragma once

#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

/**
 * 3d Camera Pawn that spins around Z axis, moves along the XY plane and Z positions are fixed to "floors"
 * It's centered on a focus point, that is were, in 3d world, will be centered the camera
 */
UCLASS()
class ACameraPawn : public APawn
{
	GENERATED_UCLASS_BODY()

    /** point light component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components")
    TSubobjectPtr<USphereComponent> Sphere;

    /** Spring Arm were the camera is attached */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components")
    TSubobjectPtr<USpringArmComponent> CameraArm;

    /** Camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TSubobjectPtr<UCameraComponent> MainCamera;


    /** Camera Max distance from the focus point */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Position")
    float MaxDistance;

    /** Camera Min distance from the focus point */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Position")
    float MinDistance;

    /** Camera distance from the focus point */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Position")
    float FocusDistance;
    
    /** Max Pitch Angle at were the camera is located respect focus point when the camera is far*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Position")
    float MaxPitch;

    /** Min Pitch Angle at were the camera is located respect focus point when the camera is near*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Position")
    float MinPitch;

    /** Pitch Angle at were the camera is located respect focus point*/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Position")
    float Pitch;

    /** Yaw Angle at were the camera is located respect focus point*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Position")
    float Yaw;

    /** Roll Angle at were the camera is located respect focus point*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Position")
    float Roll;

    /**
     * Sets the camera distance between max and min distance
     * @param distance Normalized distance, were 1.0 is the max distance and 0.0 is the minimal distance 
     */
    UFUNCTION(BlueprintCallable, Category = "Camera Position")
    void SetCameraDistance(float distance);



};
