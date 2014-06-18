

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

    // Axis binding
    UFUNCTION()
    void MoveForward (float val);
    
    UFUNCTION()
    void MoveRight (float val);
    
    UFUNCTION()
    void Zoom (float val);

    // Action binding
    UFUNCTION()
    void ZoomIn ();
    
    UFUNCTION()
    void ZoomOut ();


	
protected:
    /** Allows the PlayerController to set up custom input bindings. */
    virtual void SetupInputComponent() OVERRIDE;
	
};
