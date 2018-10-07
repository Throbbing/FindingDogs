#pragma once
#include "Vector2.h"
#include "Sprite.h"
#include "Texture2D.h"
#include <string>
enum class GameState
{
	E_TITLE,
	E_TALK,
	E_PLAYER_CONTROLL,
	E_ACTION,
	E_UI,
	E_END,
	E_TOTAL
};
//actions
struct Ac
{
	Ac();
	virtual bool run(float dt);
	virtual bool doing(float dt);
	virtual void init(float dt);
	void reset();
	int id;
	float time;
	bool end;
	bool begin;
	bool loop = false;
};



struct MovetoPlayer :public Ac
{
	MovetoPlayer(class WIPSprite* s, const std::string& ani, float speed);
	bool run(float dt);
	virtual bool doing(float dt);
	void init(float dt);
	WIPSprite* mover = 0;
	std::string ani_name;
	WIPSprite* s = 0;
	float speed;
};

struct Moveto :public Ac
{
	Moveto(WIPSprite* s, const std::string& ani, float speed, const RBVector2& pos);
	bool run(float dt);
	bool doing(float dt);
	void init(float dt);
	WIPSprite* mover = 0;
	std::string ani_name;
	float speed;
	RBVector2 tar;
};

struct TurnoffBGM : public Ac
{
	TurnoffBGM(const std::string& name);
	bool run(float dt);
	std::string event_name;
};

struct PlayBGM :public Ac
{
	PlayBGM(const std::string& name);
	bool run(float dt);
	std::string event_name;
};

struct ChangeGameState :public Ac
{
	ChangeGameState(class MapComponent* t, GameState games);
	bool run(float dt);
	class MapComponent* t;
	GameState g_s;
};

struct ShowTexture :public Ac
{
	ShowTexture(class MapComponent* tex);
	bool run(float dt);
	class MapComponent* t;
};

struct CameraZoom :public Ac
{
	CameraZoom(float tar, class WIPCamera* c, float speed);
	bool run(float dt);
	void init(float dt);
	bool doing(float dt);
	float target;
	float speed;
	class WIPCamera* cam;
};
struct CameraMove :public Ac
{
	CameraMove(const RBVector2& tar, class WIPCamera* c, float speed);
	bool run(float dt);
	void init(float dt);
	bool doing(float dt);
	RBVector2 target;
	float speed;
	class WIPCamera* cam;
};

struct WaitCameraStay :public Ac
{
	WaitCameraStay( class WIPCamera* c);
	bool run(float dt);
	void init(float dt);
	bool doing(float dt);
	WIPSprite* player;
	class WIPCamera* cam;
	RBVector2 old_cam_pos;
	f32 t;
};

//if you want use combine action you must implemente the doing function and init function
struct CombineAc2 :public Ac
{
	CombineAc2(Ac* ac1, Ac* ac2);
	bool run(float dt);
	void init(float dt);
	bool doing(float dt);
	Ac* a;
	Ac* b;
};
struct NPCDisplayData
{
	NPCDisplayData() :word_tp(WordType::E_SIMPLE_TALK), npc_size(RBVector3::zero_vector), words(nullptr), face(nullptr)
	{}
	enum WordType
	{
		E_SIMPLE_TALK = 0,
		E_TALK,
		E_TOTAL,
	} word_tp;
	//position+height
	RBVector3 npc_size;
	wchar_t* words;
	WIPTexture2D* face;
};
struct TalkAc :public Ac
{
	TalkAc(wchar_t* words, NPCDisplayData* data, class MapComponent* mc, class TransformComponent* host);
	bool run(float dt);
	virtual bool doing(float dt);
	void init(float dt);
	wchar_t* _words; NPCDisplayData* _data; class MapComponent* _mc;
	WIPSprite* s;class TransformComponent* _tc;
};

struct NPCTalkParam
{
	NPCTalkParam()
	{
		memset(s, 0, 100 * sizeof(TalkAc*));
	}
	//npc word is a type of resource
	Ac* s[100];
};

struct TalkResetAc :public Ac
{
	TalkResetAc(NPCTalkParam* ip, struct TalkStartAc* e,class TransformComponent* tc);
	bool run(float dt);
	virtual bool doing(float dt);
	void init(float dt);
	NPCTalkParam* p;
	Ac* ends;
	class TransformComponent* _tc;
	WIPSprite* s;
};

struct TalkStartAc :public Ac
{
	TalkStartAc(TalkResetAc* ip);
	bool run(float dt);
	virtual bool doing(float dt);
	void init(float dt);
	TalkResetAc* p;
};

//reset all actions you need
struct ResetAc : public Ac
{

	std::vector<Ac> v;
};

//auto talk anda wait for pressing space
//dont change game state
struct TalkWait : public Ac
{

};

//just wait for some time
struct Wait : public Ac
{
	Wait(f32 ttt);
	bool run(float dt);
	virtual bool doing(float dt);
	void init(float dt);
	f32 _ttt;
};

//for event triggered due to push button
struct WaitTriggerPushKey : public Ac
{
	WaitTriggerPushKey();
	bool run(float dt);
	virtual bool doing(float dt);
	void init(float dt);
};

struct SetGameVaribleReal : public Ac
{
	SetGameVaribleReal(const std::string& name,float t);
	bool run(float dt);
	virtual bool doing(float dt);
	void init(float dt);
	std::string var_name;
	float tg;

};

struct SetGameVaribleInt : public Ac
{
	SetGameVaribleInt(const std::string& name, int t);
	bool run(float dt);
	virtual bool doing(float dt);
	void init(float dt);
	std::string var_name;
	int tg;

};

struct SetGameVaribleText : public Ac
{
	SetGameVaribleText(const std::string& name,const std::string& t);
	bool run(float dt);
	virtual bool doing(float dt);
	void init(float dt);
	std::string var_name;
	std::string tg;

};

struct ImmediateAction :public Ac
{
	ImmediateAction() {}
	bool run(float dt) final;
	virtual bool doing(float dt) = 0;
	virtual void init(float dt) = 0;
};

enum CALLBACKTYPE
{
	PLAY_BEGINCONTACT,
	PLAY_ONCONTACT,
	PLAY_ENDCONTACT,
	PLAY_UPDATE,
};


struct ChangeObjectCallbackState : public ImmediateAction
{
	ChangeObjectCallbackState(WIPSprite* s, CALLBACKTYPE ctp,bool v);
	virtual bool doing(float dt);
	void init(float dt);

	class WIPSprite* s = 0;
	class EventComponent* evc = 0;
	CALLBACKTYPE tp;
	bool val;
};

struct ChangeCharracterAIControllState : public ImmediateAction
{
	ChangeCharracterAIControllState(WIPSprite* s, bool v);
	virtual bool doing(float dt);
	void init(float dt);

	class WIPSprite* s = 0;
	class CharacterAIControll* evc = 0;
	bool val;
};


/*
struct SaveCameraState : public ImmediateAction
{
	class WIPCamera* cam;
	
};

struct RestoreCameraState : public ImmediateAction
{

};
*/
struct SetCharacterState : public ImmediateAction
{
	SetCharacterState();
	virtual bool doing(float dt);
	void init(float dt);
};


#include <stack>
#include <queue>


class Actions
{
public:
	Actions(int pages = 1);
	void reset();
	void put_action(Ac* ac,int page=0);
	void next_action();
	std::vector<Ac*> acs;
	Ac* cur_ac = nullptr;
	int cur_page = 0;

	bool event_begin = false;
	int counter = 0;
	bool loop = false;
	bool fin = false;
};

class ActionSet
{
public:
	std::vector<Actions*> acss;
};

class ActionRunner
{
public:
	bool begin_run = false;
	std::queue<Ac*> run_seq;
	static ActionRunner* get_instance();
	bool run_action(Actions* acs,f32 dt);
	void ready_run_action(Actions* acs);
	void end_run_action();
	Ac* cur_ac = nullptr;
};



extern ActionRunner* g_action_runner;