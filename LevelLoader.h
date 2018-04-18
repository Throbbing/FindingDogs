#pragma once
#include "scene.h"

class FDLevelLoader :public WIPLevelLoader
{
public:
	FDLevelLoader(WIPScene* sce) :scene(sce) { scene->loader = this; }
	~FDLevelLoader() {}
	//clear current level 
	void reload_level(const char* level_name);
	//keep old level
	void load_level(const char* level_name);

	//test
	void test_load_persistent();
	void test_load_level1();
	void test_reload_level();
	void test_load_level();

	void load_level_findingdogs_1();

	void load_caodi(const RBVector2& postion);
	void load_huangdi(const RBVector2& postion);
	void load_mudi(const RBVector2& postion);

	void init_game();
	void load_level(int id, const RBVector2& pos)
	{
		switch (id)
		{
		case 0:
			test_load_level();
			break;
		case 1:
			load_caodi(pos);
			break;
		case 2:
			load_huangdi(pos);
			break;
		case 3:
			load_mudi(pos);
			break;
		default:
			break;
		}
	}
	/*
	void test_reload_level1();
	void test_load_level1();
	*/
	class FDGame* game=0;
private:
	FDLevelLoader() {}
	WIPScene* scene;
};