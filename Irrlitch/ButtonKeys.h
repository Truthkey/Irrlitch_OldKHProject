#include "Headers.h"
void MaximizeKey(MyEventReceiver receiver,IrrlichtDevice *device)
{
	if(receiver.IsKeyDown(KEY_KEY_O))
	{
		device->maximizeWindow();
	}
}