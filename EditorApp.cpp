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
		window_w = 800;
		window_h = 600;
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



