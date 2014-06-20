

#pragma once

#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "CameraPawn.generated.h"

/**
 * 3d Camera Pawn that spins around Z axis, moves along the XY plane and Z positions are fixed to "floors"
 * It's centered on a focus point, that is were, in 3d world, will be centered the camera
 */
UCLASS()
class ACameraPawn : public APawn
{
	GENERATED_UCLASS_BODY()

    /** Base component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components")
    TSubobjectPtr<USphereComponent> Sphere;

    /** Spring Arm were the camera is attached */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components")
    TSubobjectPtr<USpringArmComponent> CameraArm;

    /** Camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TSubobjectPtr<UCameraComponent> MainCamera;

	/** Movement component */
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly)
	TSubobjectPtr<class UFloatingPawnMovement> MovementComponent;


    /** Camera Max distance from the focus point */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Position")
    float MaxDistance;

    /** Camera Min distance from the focus point */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Position")
    float MinDistance;

    /** Camera distance from the focus point */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Position")
    float FocusDistance;
    
    /** Normalized Camera distance from the focus point */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Position")
    float NormDistance;
    
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
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Position")
    float Yaw;

    /** Roll Angle at were the camera is located respect focus point*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Position")
    float Roll;
    
    // FUNCTIONS ************************************************************************

    /**
     * Update camera distance and rotation
     */
    UFUNCTION(BlueprintCallable, Category = "Camera Control")
    void UpdateCameraDistance();

    /**
     * Sets Camera Yaw angle
     */
    UFUNCTION(BlueprintCallable, Category = "Camera Control")
    void AddYaw (float degress);
    
    /**
     * Sets Camera Roll angle
     */
    UFUNCTION(BlueprintCallable, Category = "Camera Control")
    void AddRoll (float degress);

    /**
     * Sets Camera Yaw and Roll angles
     */
    UFUNCTION(BlueprintCallable, Category = "Camera Control")
    void SetOrientation (float rYaw, float rRoll);
    
    /**
     * Sets Camera Yaw and Roll angles plus sets the camera normalized distance between max and min distance
     * @param distance Normalized distance, were 1.0 is the max distance and 0.0 is the minimal distance 
     */
    UFUNCTION(BlueprintCallable, Category = "Camera Control")
    void SetOrientationDistance (float distance, float rYaw, float rRoll);

    /**
     * handles moving forward/backward
     */
    UFUNCTION(BlueprintCallable, Category = "Camera Control")
    void MoveForward(float Val);

     /**
      * handles strafing
      */
    UFUNCTION(BlueprintCallable, Category = "Camera Control")
    void MoveRight(float Val);

    /**
     * handles zoom change
     */
    UFUNCTION(BlueprintCallable, Category = "Camera Control")
    void Zoom(float Val);


    // OVERRIDES
	virtual class UPawnMovementComponent* GetMovementComponent() const OVERRIDE { return MovementComponent; }
};
