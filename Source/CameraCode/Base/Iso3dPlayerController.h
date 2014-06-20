

#pragma once

#include "GameFramework/PlayerController.h"
#include "Iso3dPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AIso3dPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

    /** Is active and listening mouse/touch/gamepad/keyboard events ? */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MouseInterface")
    bool bActive;

    // Axis binding
    UFUNCTION()
    void MoveForward (float val);
    
    UFUNCTION()
    void MoveRight (float val);
    
    UFUNCTION()
    void Zoom (float val);

    UFUNCTION()
    void RotateCCW(float val);

    // Action binding
    UFUNCTION()
    void ZoomIn ();
    
    UFUNCTION()
    void ZoomOut ();

    UFUNCTION()
    void CameraMovePressed ();
    
    UFUNCTION()
    void CameraMoveReleased ();

    /**
     * Does a trace collision test along the proyecto of the mouse cursors (aka searchs what is bellow the mpuse cursor in 3d world)
     * @param OutHit Object with the information of the trace
     * @param bHit Has hit something in the trace channel ?
     * @param distance How far should be the trace in unreal units
     * @param channel Trace channel to use
     * @param bDrawDebug Should draw debug lines of the trace ?
     */
    UFUNCTION(BlueprintCallable, Category="Collision")
    void GetMouse3dTrace(FHitResult& OutHit, bool& bHit, float distance, ECollisionChannel channel, bool bDrawDebug = false);

    virtual void BeginPlay() OVERRIDE;
	
protected:
    /** Move camera view button has been pressed ? */
    bool bCameraMovePressed;
    
    /** Mouses has been moved since CameraMovePressed hapened ? */
    bool bMouseMoved;

    FVector Old3dMouse; /// Were was pointing the mouse in 3d world when the button was pressed

    /** Allows the PlayerController to set up custom input bindings. */
    virtual void SetupInputComponent() OVERRIDE;
	
    virtual void Tick(float DeltaSeconds) OVERRIDE;
};
