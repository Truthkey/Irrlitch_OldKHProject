#include "Headers.h"
void HUD_Display(IrrlichtDevice *device, IVideoDriver* driver, MyEventReceiver receiver, IGUIFont* font, int CurHP, int MaxHP, int HeartP)
{
	u32 time = device->getTimer()->getTime();
	ITexture* HUD = driver->getTexture("../media/KH/HUD.png");
	driver->makeColorKeyTexture(HUD, position2d<s32>(0,0));
	ITexture* Portrait = driver->getTexture("../media/KH/Aqua.png");
	driver->makeColorKeyTexture(Portrait,position2d<s32>(0,0));
	ITexture* Bar = driver->getTexture("../media/KH/BARS.png");
	driver->makeColorKeyTexture(Portrait,position2d<s32>(0,0));

	stringw strg;
	strg += CurHP;
	strg += "/";
	strg += MaxHP;

	//HUD.png
	rect<s32> MaxHPEx(645-MaxHP,9,646,31);
	rect<s32> HPEnd(7,9,9,31);
	rect<s32> HeartEmpty(220,76,300,162);
	rect<s32> HeartFull(304,160-HeartP,382,162);
	rect<s32> DarkHeart(387,76,465,162);
	rect<s32> GaugeFill(645-CurHP,50,646,68);

	//Character Portrait.
	rect<s32> Face(0,0,63,79);

	//Drawing Max HP.
	driver->draw2DImage
		(Bar, position2d<s32>(600-MaxHP,440), MaxHPEx, 0, SColor(255,255,255,255), true);
	driver->draw2DImage
		(Bar, position2d<s32>(599-MaxHP,440), HPEnd,0, SColor(255,255,255,255), true);
	//Drawing the current HP.
	driver->draw2DImage
		(Bar, position2d<s32>(600-CurHP,442),GaugeFill,0,SColor(255,255,255,255), true);


	driver->draw2DImage
		(HUD, position2d<s32>(560,390),DarkHeart,0,SColor(255,255,255,255), true);
	driver->draw2DImage
		(Portrait, position2d<s32>(572,395),Face,0,SColor(255,255,255,255),true);
	driver->draw2DImage
		(HUD, position2d<s32>(560,390),HeartEmpty,0,SColor(255,255,255,255),true);

	if(HeartP < 86){
		driver->draw2DImage(HUD, position2d<s32>(560,475-HeartP),HeartFull,0,SColor(255,255,255,255),true);}
	else{
		driver->draw2DImage(HUD, position2d<s32>(560,475-HeartP),HeartFull,0,SColor(255,time%255,time%255,time%255),true);}

	font->draw
		(strg,rect<s32>(520,463,600,450),SColor(255,255,255,255));
}