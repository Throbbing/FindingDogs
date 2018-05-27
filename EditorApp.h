#pragma once
#include "Platform/GLFWApp.h"
class FDGameEditor : public GLFWApp
{
public:
	~FDGameEditor();
	virtual bool init();
	void load_avg_demo();
	class FDLevelLoader* loader;
	class WorldRender* world_renderer;
};