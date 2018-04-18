#pragma once
#pragma once
#include "Sprite.h"
#include "Camera.h"
#include "Input.h"
#include "Scene.h"
#include "Render.h"
#include <fstream>
#include "AudioManager.h"
#include "Sound.h"
#include "ScriptManager.h"
#include <queue>
#include "GameAction.h"
#ifdef ML
#include "./tiny_dnn/tiny_dnn.h"

using namespace tiny_dnn;
using namespace tiny_dnn::activation;
using namespace tiny_dnn::layers;
#endif
struct Game_Varible
{
	Game_Varible()
	{
		text = "";
		number.integer = 0;
	}
	Game_Varible(const std::string& s)
	{
		text = s;
		tp = E_TEXT;
	}
	Game_Varible(float s)
	{
		tp = E_FLOAT;
		number.real = s;
	}
	explicit Game_Varible(int s)
	{
		tp = E_INT;
		number.integer = s;
	}
	enum VarType
	{
		E_TEXT,
		E_INT,
		E_FLOAT
	} tp;
	std::string text;
	union Number
	{
		int integer;
		float real;
	} number;

};
class GameData
{
public:
	GameData()
	{
		game_switch.resize(1024);
	}
	std::vector<int> game_switch;
	std::map<std::string, Game_Varible> game_varible;
};

extern GameData *g_game_data;

class MapGrid
{
public:
	MapGrid(WIPSprite*  sp, int sub)
	{
		bg = sp;
		w = bg->_render->mesh.get_witdh();
		h = bg->_render->mesh.get_height();
		bitmap = new char[sub*sub];
		memset(bitmap, 0, sub*sub);
		this->sub = sub;
	}
	void resize(int sub)
	{
		delete[] bitmap;
		bitmap = new char[sub*sub];
		memset(bitmap, 0, sub*sub);
		this->sub = sub;
	}
	void load_mask_data(const char* filename)
	{
		std::ifstream fin(filename, std::ios::binary);
		fin.read(bitmap, sub*sub);
		fin.close();
	}
	void save_mask_data(const char* filename)
	{
		std::ofstream fout(filename, std::ios::binary);
		fout.write(bitmap, sub*sub);
		fout.close();
	}
	unsigned char get_position_state(f32 wx, f32 wy)
	{
		RBVector2 v[4];
		bg->get_world_position(v);
		RBVector2 lb = v[1];
		f32 lx = wx - lb.x;
		f32 ly = wy - lb.y;
		f32 sx = lx / w;
		f32 sy = ly / h;
		int idx = sx*sub + int(sy*sub)*sub;
		return bitmap[idx];
	}
	void set_debug_tag(f32 wx, f32 wy, char tag)
	{
		RBVector2 v[4];
		bg->get_world_position(v);
		RBVector2 lb = v[1];
		f32 lx = wx - lb.x;
		f32 ly = wy - lb.y;
		f32 sx = lx / w;
		f32 sy = ly / h;
		int idx = sx*sub + int(sy*sub)*sub;
		bitmap[idx] = tag;
	}
	void clear_data()
	{
		memset(bitmap, 0, sub*sub);
	}
	void debug_draw(const WIPCamera* cam, const RBVector2& minp1)
	{
		f32 dx = w / sub;
		f32 dy = h / sub;
		RBVector2 v[4];
		bg->get_world_position(v);
		RBVector2 lb = v[1];
		RBVector2 minp;

		minp.y = minp1.y - lb.y;
		minp.x = minp1.x - lb.x;

		minp.y = ((int)(minp.y / dy))*dy + lb.y;
		minp.x = ((int)(minp.x / dx))*dx + lb.x;
		g_rhi->begin_debug_context();
		g_rhi->change_debug_color(RBColorf::blue);
		g_rhi->debug_draw_aabb2d(minp, minp + RBVector2(dx, dy), cam);
		g_rhi->debug_submit();
		g_rhi->end_debug_context();
	}
	void debug_draw(const WIPCamera* cam, char tag)
	{
		f32 dx = w / sub;
		f32 dy = h / sub;
		RBVector2 v[4];
		bg->get_world_position(v);
		RBVector2 lb = v[1];
		g_rhi->begin_debug_context();
		g_rhi->change_debug_color(RBColorf::blue);

		for (int i = 0; i < sub*sub; ++i)
		{
			if (bitmap[i] == tag)
			{
				f32 y = i / sub*dy + lb.y;
				f32 x = i % sub*dx + lb.x;
				g_rhi->debug_draw_aabb2d(RBVector2(x, y), RBVector2(x + dx, y + dy), cam);
			}
		}
		g_rhi->debug_submit();

		g_rhi->end_debug_context();
	}
	char* bitmap;
	WIPSprite*  bg;
	f32 w, h;
	int sub;

};






class MapComponent : public WIPTickComponent
{
public:

	enum class ManState
	{
		E_LEFT,
		E_RIGHT,
		E_UP, E_DOWN
	};
	
	WIPTICKCOMPONENT(MapComponent);
	WIPOBJECT(MapComponent, WIPTickComponent);
	WIP_MEM(MapComponent);

	MapComponent(WIPSprite*  s) :WIPTickComponent(s)
	{

	}
	~MapComponent() {}
	void load_collision_mask()
	{

	}
	void change_to_talk(string_hash tp, void* data);
	void change_to_player(string_hash tp, void* data);
	void fix_sprite_position(WIPSprite*  sprite)
	{
		if (1 == grid->get_position_state(man->_transform->world_x, man->_transform->world_y))
		{
			man->translate_to(old_pos.x, old_pos.y);
		}
	}
	void init();
	void destroy();
	void update(f32 dt);

	void fix_update(f32 dt)
	{

	}
	void on_load(void* data)
	{

	}


	float alpha_s = 1.f;
	float alpha = 1.f;

	std::vector<class Ac*> actions;

	WIPSprite*  man;
	WIPSprite*  fogs;
	RBVector2 fog_dir;
	WIPSprite*  bg;
	WIPSprite* woman;

	WIPCamera* cam;
	WIPScene* scene;
	ManState man_state;
	WIPAnimationClip* clip;
	WIPAnimationClip* clip1;
	WIPAnimationClip* clip2;
	WIPAnimationClip* clip3;
	WIPAnimationClip* clip_s;
	WIPAnimationClip* clip1_s;
	WIPAnimationClip* clip2_s;
	WIPAnimationClip* clip3_s;
	WIPAnimationClip* pre_clip;

	RBVector2 old_pos;
	MapGrid* grid;
	bool draw_debug;
	f32 newpx;
	f32 newpy;

	StudioSound* sound;
	StudioSound* sound_t;

	int old_ms=0;

	UIRender* ui_renderer;
	//#define Text1
#ifdef Text1
	class LargeTexture_TextRender* text_renderer;
#else
	class TextRender* text_renderer;
#endif

	bool edit_mode;

	int gsize;

	//test event system
	class IMButton* imbt;
	class A* a;
	class A* a1;
	class B* b;
	class IMMainMenuBar* main_bar;
	class IMCheckBox* cb;

	string_hash component_update;


	GameState game_state = GameState::E_PLAYER_CONTROLL;
	const NPCDisplayData* cur_npc_ui = nullptr;


	//title resouces
	WIPTexture2D* ext_bt;
	WIPTexture2D* ctn_bt;
	WIPTexture2D* stt_bt;
	WIPTexture2D* t_bg;
	WIPTexture2D* title;
	int title_state = 0;

	WIPTexture2D* cards[3];

	WIPTexture2D* move_bar;
	WIPTexture2D* end_tex;

	bool action_bg = false;
	RBVector2 trans_target;

	std::string mask_path;

};

class NPCComponent : public WIPTickComponent
{
public:
	WIPTICKCOMPONENT(NPCComponent);
	WIPOBJECT(NPCComponent, WIPTickComponent);
	WIP_MEM(NPCComponent);
	NPCComponent(WIPSprite*  s);
	~NPCComponent();
	virtual void init();
	virtual void update(f32 dt);
	virtual void fix_update(f32 dt)
	{

	}
	virtual void destroy();
	void add_faces(std::string name, WIPTexture2D* tex);
	void set_face(std::string name);
	void set_no_face();
	void set_default_face();
	void on_begin_contact(const WIPSprite* s);
	void on_end_contact(const WIPSprite* s);
	void on_contact(const WIPSprite* s, float dt);
	NPCDisplayData data;
	std::queue<wchar_t*> words[2];
	std::map<int, WIPTexture2D*> npc_faces;
	MapComponent* map_component = nullptr;
	void on_load(void* data)
	{

	}
};

#define UPDATE_EVENT 0
#define BEGIN_EVENT 1
#define CONTACT_EVENT 2
#define END_EVENT 3
#define LEVEL_START 4
#define LEVEL_END 5



class TransformComponent : public WIPTickComponent
{
public:
	WIPTICKCOMPONENT(TransformComponent);
	WIPOBJECT(TransformComponent, WIPTickComponent);
	WIP_MEM(TransformComponent);
	TransformComponent(WIPSprite*  s);
	~TransformComponent();
	virtual void init();
	virtual void update(f32 dt);
	virtual void fix_update(f32 dt)
	{

	}
	virtual void destroy();
	void on_begin_contact(const WIPSprite* s);
	void on_end_contact(const WIPSprite* s);
	void on_contact(const WIPSprite* s, float dt);
	MapComponent* map_component = nullptr;
	void on_load(void* data)
	{

	}
	virtual void start();
	virtual void end();
	//be sure to use pod data!
	void* call_data[6];
	//event callback
	void(*func_begin)(void*, const WIPSprite*, TransformComponent* t) = 0;
	void(*func_contact)(void*, const WIPSprite*, float, TransformComponent* t) = 0;
	void(*func_end)(void*, const WIPSprite*, TransformComponent* t) = 0;
	void(*func_update)(void*, float, TransformComponent* t) = 0;
	void(*func_level_start)(void*, TransformComponent* t) = 0;
	void(*func_level_end)(void*, TransformComponent* t) = 0;



};


