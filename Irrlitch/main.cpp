#include "MyEventReceiver.h"
#include "HUD.h"
#include "PCaption.h"
#include "ButtonKeys.h"
#include "Definitions.h"

int main(int argc, const char** argv)
{
/*	- deviceType: Type of the device. This can currently be the Null-device,
	   one of the two software renderers, D3D8, D3D9, or OpenGL. In this
	   example we use EDT_SOFTWARE, but to try out, you might want to
	   change it to EDT_BURNINGSVIDEO, EDT_NULL, EDT_DIRECT3D8,
	   EDT_DIRECT3D9, or EDT_OPENGL.
	*/
	MyEventReceiver receiver;
	ISoundEngine* music = createIrrKlangDevice();
	IrrlichtDevice *device =
		createDevice( EDT_DIRECT3D9, dimension2d<u32>(640, 480), 32,
			false, false, false, &receiver);

	music->play2D("../media/MUSIC/Dark Impetus.mp3",true,false,true);

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	ICameraSceneNode *camera = smgr->addCameraSceneNode();
	IGUIFont* font = device->getGUIEnvironment()->getFont("../media/fonthaettenschweiler.bmp");
	camera->setFarValue(900);

	IAnimatedMesh* map = smgr->getMesh(DC_01);
	IAnimatedMeshSceneNode* mapnode = smgr->addAnimatedMeshSceneNode(map);
	mapnode->setMaterialFlag(EMF_LIGHTING,false);

	IAnimatedMesh* player1 = smgr->getMesh(SORA);
	IAnimatedMeshSceneNode* p1node = smgr->addAnimatedMeshSceneNode(player1);
	p1node->setMaterialFlag(EMF_LIGHTING, false);
	p1node->setScale(SORA_VECTOR3D);

	IAnimatedMesh* player2 = smgr->getMesh(AQUA);
	IAnimatedMeshSceneNode* p2node = smgr->addAnimatedMeshSceneNode(player2);
	p2node->setMaterialFlag(EMF_LIGHTING, false);
	p2node->setScale(NORMAL_VECTOR3D);

	vector3df Position = p1node->getPosition();
	vector3df P2Pos = p2node->getPosition();
	vector3df PosCam = p1node->getPosition();
	vector3df Rotate = p1node->getPosition();

	int CurrentHP = 300;
	int MaxHP = 400;
	int HeartP = 10;
	bool LockOn = false;
	bool LockCheck = false;
	stringw CoorCheck;

	while(device->run())
	{
		CoorCheck +=L"Your position\nX:";
		CoorCheck +=Position.X;
		CoorCheck +=L"\nY:";
		CoorCheck +=Position.Y;
		CoorCheck +=L"\nZ:";
		CoorCheck +=Position.Z;
		CoorCheck +=L"\n\nTarget Position:";
		CoorCheck +=P2Pos.X;
		if(LockCheck != true){
			if(receiver.IsKeyDown(KEY_KEY_J)){LockOn = true; LockCheck = true;}}
		else{
			if(receiver.IsKeyDown(KEY_KEY_J)){LockOn = false;LockCheck = false;}}

		//3D Rendering.
		MaximizeKey(receiver,device);
		GetCaption(driver,device);
		driver->beginScene(true, true, SColor(255,100,101,140));
		p1node->setPosition(Position);
		camera->setPosition(vector3df(PosCam.X,PosCam.Y+2,PosCam.Z+3));
		if(LockOn != false){camera->setTarget(P2Pos);}
		else{camera->setTarget(Position);}
		smgr->drawAll();

		//2D Rendering.
		if(CurrentHP<=0){font->draw(L"You are dead!!!",rect<s32>(120,140,250,210),SColor(255,255,255,255));}
		else{if(receiver.IsKeyDown(KEY_KEY_L)){--CurrentHP;}}
		if(CurrentHP>=MaxHP){}else{if(receiver.IsKeyDown(KEY_KEY_K)){++CurrentHP;}}

		if(receiver.IsKeyDown(KEY_KEY_N)){++MaxHP;}
		if(receiver.IsKeyDown(KEY_KEY_M) && CurrentHP<MaxHP){--MaxHP;}
		if(HeartP>=86){}else{
			if(receiver.IsKeyDown(KEY_KEY_F)){++HeartP;}}

		font->draw
		(L"Press O for full screen.\nPress Up-Down-Left-right to move.\nPress L to hurt the character.\nPress K to heal the character.\nPress N to increase Max HP.\nPress M to decrease Max HP.\nPress F to fill the Heart gauge.",rect<s32>(20,40,150,110),SColor(255,0,0,0));
		font->draw(CoorCheck,rect<s32>(20,140,150,110),SColor(255,0,0,0));

		//Button detection.
		if(receiver.IsKeyDown(KEY_UP)){
			Position.Z -= 0.1f;
			PosCam.Z = Position.Z;
			p1node->setRotation(vector3df(Rotate.X,Rotate.Y = 0,Rotate.Z));
			p1node->setPosition(Position);}
		if(receiver.IsKeyDown(KEY_DOWN)){
			Position.Z += 0.1f;
			PosCam.Z = Position.Z;
			p1node->setRotation(vector3df(Rotate.X,Rotate.Y -180,Rotate.Z));
			p1node->setPosition(Position);}
		if(receiver.IsKeyDown(KEY_LEFT)){
			Position.X += 0.1f;
			PosCam.X = Position.X;
			p1node->setRotation(vector3df(Rotate.X,Rotate.Y -90,Rotate.Z));
			p1node->setPosition(Position);}
		if(receiver.IsKeyDown(KEY_RIGHT)){
			Position.X -= 0.1f;
			PosCam.X = Position.X;
			p1node->setRotation(vector3df(Rotate.X,Rotate.Y +90,Rotate.Z));
			p1node->setPosition(Position);}

		HUD_Display(device,driver,receiver,font,CurrentHP,MaxHP,HeartP);

		guienv->drawAll();
		CoorCheck = L"";
		driver->endScene();
	}
	music->drop();
	device->drop();
	return 0;
}