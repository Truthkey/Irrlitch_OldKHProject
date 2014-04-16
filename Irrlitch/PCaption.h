#include "Headers.h"
void GetCaption(IVideoDriver* driver,IrrlichtDevice *device)
{
	stringw str = L"Kingdom Hearts: The Project -";
	str+=L" FPS:";
	str+=(s32)driver->getFPS();
	str+=L" - Resolution: ";
	str+=driver->getScreenSize().Width;
	str+=L"x";
	str+=driver->getScreenSize().Height;
	device->setWindowCaption(str.c_str());
}