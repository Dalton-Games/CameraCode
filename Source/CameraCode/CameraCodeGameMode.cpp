

#include "CameraCode.h"
#include "CameraCodeGameMode.h"
#include "CameraCodePlayerController.h"

ACameraCodeGameMode::ACameraCodeGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PlayerControllerClass = ACameraCodePlayerController::StaticClass();
}


