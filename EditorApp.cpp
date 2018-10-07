#include "EditorApp.h"
#include "LevelLoader.h"

#include "AudioManager.h"
#include "AnimationManager.h"
#include "Scene.h"


FDGameEditor::~FDGameEditor()
{
	delete loader;
	delete world_renderer;
}

bool FDGameEditor::init()
{
	window_w = 1920 * 0.9f;
	window_h = 1080 * 0.9f;
	bool ret = create_window("FindingDog Editor");
	ret &= GLFWApp::init();
	world_renderer = new WorldRender();
	world_renderer->init();
	world_renderer->set_world(g_scene);
	g_scene->world_renderer = world_renderer;
	LOG_INFO("Renderer start up...");

	g_animation_manager->update(1);
	g_scene->init_components();
	return ret;
}
void FDGameEditor::load_avg_demo()
{
	//load editor
}


/*
Resources:
-	Animation Clip
-	Texture2D
-	Callback parameter
-	Actions(Event)
-	Action
	-	MovetoPlayer
	-	Moveto
	-	TurnoffBGM
	-	PlayBGM
	-	ChangeGameState
	-	ShowTexture
	-	CameraZoom
	-	CameraMove
	-	WaitCameraStay
	-	CombineAc2
	-	TalkAc
	-	TalkResetAc
	-	TalkStartAc
	-	ResetAc
	-	Wait
	-	WaitTrigger
	-	SetGameVaribleReal
	-	SetGameVaribleInt
	-	SetGameVaribleText
	-	ImmediateAction
		-	SetCharacterState

Objects:
-	Camera
-	Sprite
	-	Trigger
	-	SceneTransformer
	-	Avator
	-	NPC_TalkOnly
	-	NPC_Event

///////////////
//Save file
///////////////
GameData(whole game):
-	game_varibles...
*/


