// Shoot Them Up 4.26.All Rights reserved


#include "STUGameInstance.h"
#include "Sound/STUSoundFunctionLib.h"

void USTUGameInstance::ToogleVolume()
{
	USTUSoundFunctionLib::ToggleSoundClassVolume(MasterSoundClass);
}
