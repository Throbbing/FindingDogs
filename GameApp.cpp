#include "GameApp.h"
#include "LevelLoader.h"

#include "AudioManager.h"
#include "AnimationManager.h"
#include "Scene.h"


FDGame::~FDGame()
{
	delete loader;
	delete world_renderer;
}

bool FDGame::init()
	{
		window_w = 800;
		window_h = 600;
		bool ret = create_window("FindingDog");
		ret &= GLFWApp::init();
		world_renderer = new WorldRender();
		world_renderer->init();
		world_renderer->set_world(g_scene);
		g_scene->world_renderer = world_renderer;
		LOG_INFO("Renderer start up...");
		loader = new FDLevelLoader(g_scene);
		loader->game = this;
		g_scene->loader = loader;
		load_avg_demo();
		//use a big delta time to play first frame
		g_animation_manager->update(1);
		g_scene->init_components();
		return ret;
	}
	void FDGame::load_avg_demo()
	{
		g_audio_manager->LoadBank("./audio/Desktop/master bank.bank", false);
		g_audio_manager->LoadBank("./audio/Desktop/master bank.strings.bank", false);
		g_scene->loader->init_game();
		g_scene->loader->load_level(1, RBVector2(6.6f, -12.6f));
	}



