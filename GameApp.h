#pragma once
#include "Platform/GLFWApp.h"
class FDGame : public GLFWApp
{
public:
	~FDGame();
	virtual bool init();
	void load_avg_demo();
	class FDLevelLoader* loader;
	class WorldRender* world_renderer;
};