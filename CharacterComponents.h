#include "FDGameComponent.h"


class CharacterComponent : public WIPTickComponent
{
public:
	WIPTICKCOMPONENT(CharacterComponent);
	WIPOBJECT(CharacterComponent, WIPTickComponent);
	WIP_MEM(CharacterComponent);
	CharacterComponent(WIPSprite*  s);
	~CharacterComponent() {}
	virtual void init();
	virtual void update(f32 dt);
	virtual void fix_update(f32 dt) {}
	virtual void destroy() {}
};

class CharacterControll : public WIPTickComponent
{
public:
	WIPTICKCOMPONENT(CharacterControll);
	WIPOBJECT(CharacterControll, WIPTickComponent);
	WIP_MEM(CharacterControll);
	CharacterControll(WIPSprite* s);
	~CharacterControll() {}
	virtual void init();
	virtual void update(f32 dt);
	virtual void fix_update(f32 dt) {}
	virtual void destroy() {}
	virtual void controll(f32 dt) {}

	//charecter states
	RBVector2 old_pos;
	MapComponent* map;
	bool actived = true;
};

class CharacterPlayerControll : public CharacterControll
{
public:
	WIPTICKCOMPONENT(CharacterPlayerControll);
	WIPOBJECT(CharacterPlayerControll, CharacterControll);
	WIP_MEM(CharacterPlayerControll);
	CharacterPlayerControll(WIPSprite* s);
	~CharacterPlayerControll() {}
	virtual void init();
	//virtual void update(f32 dt);
	virtual void fix_update(f32 dt) {}
	virtual void destroy() {}
	virtual void controll(f32 dt);
	void switch_controll(string_hash tp, void* data);
	enum class ManState
	{
		E_LEFT,
		E_RIGHT,
		E_UP, E_DOWN
	};
	ManState man_state;
	string_hash stop_hs;
	string_hash restore_hs;

	
};

class CharacterAIControll : public CharacterControll
{
public:
	WIPTICKCOMPONENT(CharacterAIControll);
	WIPOBJECT(CharacterAIControll, CharacterControll);
	WIP_MEM(CharacterAIControll);
	CharacterAIControll(WIPSprite* s);
	~CharacterAIControll() {}
	virtual void init();
	virtual void fix_update(f32 dt) {}
	virtual void destroy() {}
	virtual void controll(f32 dt);
	void play_stand_animation();
	void switch_controll(string_hash tp, void* data);
	
	bool wait_seconds(f32 seconds,f32 dt);
	enum class ManState
	{
		E_LEFT,
		E_RIGHT,
		E_UP, E_DOWN
	};
	ManState man_state;
	f32 sp_time = 0.f;
	string_hash stop_hs;
	string_hash restore_hs;
	f32 sx = 0, sy=0;
};