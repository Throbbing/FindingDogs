#pragma once
#include "GameAction.h"
#include "CharacterComponents.h"
#include "Camera.h"
#include "Logger.h"
//actions

Ac::Ac()
{
	end = false;
	begin = false;
	time = 0.f;
	id = RBMath::get_rand_i(1999);
}
bool Ac::run(float dt)
{
	if (end)
		return true;
	if (!begin)
	{
		//init
		begin = true;
	}
	time += dt;
	LOG_NOTE("Doing %d", id);
	if (time > 2)
	{
		end = true;
		LOG_NOTE("Change");
		return true;
	}
	return false;
}
bool Ac::doing(float dt) { return true; }
void Ac::init(float dt) {}
void Ac::reset()
{
	time = 0.f;
	begin = false;
	end = false;
}


MovetoPlayer::MovetoPlayer(WIPSprite* s, const std::string& ani, float inspeed) : Ac()
{
	mover = s;
	ani_name = ani;
	speed = inspeed;
}



Moveto::Moveto(WIPSprite* s, const std::string& ani, float inspeed, const RBVector2& pos) : Ac()
{
	mover = s;
	ani_name = ani;
	speed = inspeed;
	tar = pos;
}
bool MovetoPlayer::run(float dt)
{
	if (!mover) return true;
	if (end)
		return true;
	if (!begin)
	{
		init(dt);
		begin = true;
	}
	/*
	RBVector2 target(s->_transform->world_x, s->_transform->world_y);
	RBVector2 mp(mover->_transform->world_x, mover->_transform->world_y);
	RBVector2 dis(target - mp);
	dis.normalize();
	dis = dis*dt*speed;
	if ((dis + mp - target).squared_size()<1.5f)
	{
	mover->_animation->play_name("stand_down", true);
	end = true;
	return true;
	}
	mover->translate(dis.x, dis.y);
	*/
	if (doing(dt))
	{
		end = true;
		return true;
	}
	return false;
}
bool MovetoPlayer::doing(float dt)
{
	RBVector2 target(s->_transform->world_x, s->_transform->world_y);
	RBVector2 mp(mover->_transform->world_x, mover->_transform->world_y);
	RBVector2 dis(target - mp);
	dis.normalize();
	dis = dis*dt*speed;
	if ((dis + mp - target).squared_size() < 1.5f)
	{
		mover->_animation->play_name("stand_down", true);
		end = true;
		return true;
	}
	mover->translate(dis.x, dis.y);
	time += dt;
	return false;
}
void MovetoPlayer::init(float dt)
{
	mover->_animation->play_name(ani_name, true);
	s = g_scene->get_sprite_by_tag("man");
}


bool Moveto::run(float dt)
{
	if (!mover) return true;
	if (end)
		return true;
	if (!begin)
	{
		init(dt);
		begin = true;
	}
	if (doing(dt))
	{
		end = true;
		return true;
	}
	return false;
}
bool Moveto::doing(float dt)
{
	RBVector2 target(tar);
	RBVector2 mp(mover->_transform->world_x, mover->_transform->world_y);
	RBVector2 dis(target - mp);
	dis.normalize();
	dis = dis*dt*speed;
	mover->_animation->play_name(ani_name, true);
	if ((dis + mp - target).squared_size() < 0.005f)
	{
		mover->_animation->play_name("stand_down", false);

		return true;
	}
	mover->translate(dis.x, dis.y);
	time += dt;
	return false;
}
void Moveto::init(float dt)
{
	mover->_animation->play_name(ani_name, true);
}



TurnoffBGM::TurnoffBGM(const std::string& name) { event_name = name; }
bool TurnoffBGM::run(float dt)
{
	if (event_name.empty()) return true;
	if (end)
		return true;
	if (!begin)
	{
		g_audio_manager->Stop(event_name);
		begin = true;
	}
	end = true;
	return true;
}



PlayBGM::PlayBGM(const std::string& name) { event_name = name; }
bool PlayBGM::run(float dt)
{
	if (event_name.empty()) return true;
	if (end)
		return true;
	if (!begin)
	{
		g_audio_manager->Play(event_name);
		begin = true;
	}
	end = true;
	return true;
}
ChangeGameState::ChangeGameState(MapComponent* it, GameState games) :
	t(it), g_s(games), Ac()
{ }
bool ChangeGameState::run(float dt)
{
	if (!t) return true;
	if (t->game_state == g_s)
		return true;
	if (end)
		return true;
	if (!begin)
	{
		t->game_state = g_s;
		begin = true;
	}
	end = true;
	return true;
}


ShowTexture::ShowTexture(MapComponent* tex) { t = tex; }
bool ShowTexture::run(float dt)
{
	if (!t) return true;
	if (end)
		return true;
	if (!begin)
	{
		t->game_state = GameState::E_END;
		//g_temp_uisys->draw_picture(0, 0, t->get_width(), t->get_height(), t);
		begin = true;
	}
	end = true;
	return true;
}



CameraZoom::CameraZoom(float tar, WIPCamera* c, float sp) { target = tar; cam = c; speed = sp; }
bool CameraZoom::run(float dt)
{
	if (end)
		return true;
	if (!begin)
	{
		init(dt);
		begin = true;
	}
	if (doing(dt))
	{
		end = true;
		return true;
	}
	return false;
}
void CameraZoom::init(float dt)
{

}
bool CameraZoom::doing(float dt)
{
	float d = dt*(target - cam->_zoom)*speed;
	if (RBMath::abs(cam->_zoom + d - target) < 0.05f)
	{
		return true;
	}
	cam->_zoom += d;
	//!!todo:bound!
	return false;
}

CameraMove::CameraMove(const RBVector2& tar, WIPCamera* c, float sp) { target = tar; cam = c; speed = sp; }
bool CameraMove::run(float dt)
{
	if (end)
		return true;
	if (!begin)
	{
		init(dt);
		begin = true;
	}
	if (doing(dt))
	{
		end = true;
		return true;
	}
	return false;
}
void CameraMove::init(float dt)
{

}
bool CameraMove::doing(float dt)
{
	RBVector2 d = dt*(target - RBVector2(cam->world_x, cam->world_y))*speed;
	if ((RBVector2(cam->world_x, cam->world_y) + d - target).squared_size() < 0.025)
	{
		return true;
	}
	cam->move(d.x, d.y);
	//!!todo:bound!
	return false;
}

WaitCameraStay::WaitCameraStay(WIPCamera* c) { cam = c; }
bool WaitCameraStay::run(float dt)
{
	if (end)
		return true;
	if (!begin)
	{
		init(dt);
		begin = true;
	}
	if (doing(dt))
	{
		end = true;
		return true;
	}
	return false;
}
void WaitCameraStay::init(float dt)
{
	old_cam_pos = RBVector2(0, 0);
	t = 0.f;
}
bool WaitCameraStay::doing(float dt)
{
	f32 d = RBVector2::dist(RBVector2(cam->world_x, cam->world_y), old_cam_pos);
	if (d < 0.001f)
	{
		return true;
	}
	t += dt;
	if (t > 4.f*dt)
	{
		old_cam_pos.x = cam->world_x;
		old_cam_pos.y = cam->world_y;
		t = 0.f;
	}

	return false;
}

//if you want use combine action you must implemente the doing function and init function

CombineAc2::CombineAc2(Ac* ac1, Ac* ac2)
{
	a = ac1;
	b = ac2;
}
bool CombineAc2::run(float dt)
{
	if (!a || !b) return true;

	bool ad = a->run(dt);
	bool bd = b->run(dt);
	return ad&&bd;
	if (end)
		return true;
	if (!begin)
	{
		init(dt);
		begin = true;
	}

	if (doing(dt))
	{
		end = true;
		return true;
	}
	return false;
}
void CombineAc2::init(float dt)
{
	a->init(dt);
	b->init(dt);
}
bool CombineAc2::doing(float dt)
{
	bool ad = a->doing(dt);
	bool bd = b->doing(dt);
	return ad&&bd;
}



TalkAc::TalkAc(wchar_t* words, NPCDisplayData* data, MapComponent* mc, TransformComponent* host) :
	_words(words), _data(data), _mc(mc), _tc(host), s(nullptr), Ac()
{

}
bool TalkAc::run(float dt)
{
	if (!_mc || !_data || !_words) return true;
	if (end)
		return true;
	if (!begin)
	{
		init(dt);
		begin = true;
	}
	if (doing(dt))
	{
		end = true;
		return true;
	}
	return false;
}
bool TalkAc::doing(float dt)
{
	if (s->get_tag() == "man")
	{
		if (_mc->cur_npc_ui != nullptr&&_mc->cur_npc_ui != _data)
			return false;
		
		
			//g_temp_uisys->clear();
			
			_data->words = _words;
			_tc->send_event(get_string_hash("npc talk"), _data);
			if (Input::eat_sys_key_down(WIP_SPACE))
			{
				_mc->cur_npc_ui = nullptr;
				g_temp_uisys->clear();
				end = true;
				return true;
			}
		

	}
	time += dt;
	return false;
}
void TalkAc::init(float dt)
{
	s = g_scene->get_sprite_by_tag("man");
	g_audio_manager->Play("event:/talk_se");
}





bool TalkResetAc::run(float dt)
{
	if (!p) return true;
	if (end)
		return true;
	if (!begin)
	{
		init(dt);
		begin = true;
	}
	if (doing(dt))
	{
		end = true;
		return true;
	}
	return false;
}
bool TalkResetAc::doing(float dt)
{
	if (s->get_tag() == "man")
	{
		if (Input::get_sys_key_down(WIP_SPACE))
		{
			/*
			for (int i = 0; i < 100; ++i)
				if (p->s[i] && p->s[i] != this)
					p->s[i]->reset();
			*/
			_tc->send_event(get_string_hash("player"));

			end = true;
			return true;
		}
	}
	time += dt;
	return false;
}
void TalkResetAc::init(float dt)
{
	s = g_scene->get_sprite_by_tag("man");
}



TalkStartAc::TalkStartAc(TalkResetAc* ip) :
	p(ip), Ac()
{

}
bool TalkStartAc::run(float dt)
{
	if (!p) return true;
	if (end)
		return true;
	if (!begin)
	{
		init(dt);
		begin = true;
	}
	if (doing(dt))
	{
		end = true;
		return true;
	}
	return false;
}
bool TalkStartAc::doing(float dt)
{
	p->reset();
	end = true;
	return true;
}
void TalkStartAc::init(float dt)
{

}


TalkResetAc::TalkResetAc(NPCTalkParam* ip, TalkStartAc* e, TransformComponent* tc) :
	p(ip), ends(e), _tc(tc), Ac()
{
}

ActionRunner * ActionRunner::get_instance()
{
	static ActionRunner* instance = nullptr;
	if (!instance)
	{
		instance = new ActionRunner();
	}
	return instance;
}

bool ActionRunner::run_action(Actions * acs,f32 dt)
{
	if (run_seq.empty())
	{
		if (!acs->loop)
			acs->fin = true;
		acs->reset();
		begin_run = false;
		return true;
	}

	if (!cur_ac)
	{
		cur_ac = run_seq.front();
		run_seq.pop();
	}

	bool r = cur_ac->run(dt);
	if (r)
		cur_ac = nullptr;
	return false;

}

void ActionRunner::ready_run_action(Actions * acs)
{
	if (!acs || acs->acs.empty())
		return;
	if (acs->fin)
		return;
	for (int i = 0; i<acs->acs.size(); ++i)
	{
		run_seq.push(acs->acs[i]);
	}
	begin_run = true;
}

void ActionRunner::end_run_action()
{
	while (!run_seq.empty())
	{
		run_seq.front()->reset();
		run_seq.pop();
		
	}
	if (cur_ac)
		cur_ac->reset();
	cur_ac = nullptr;
	begin_run = false;
}

//todo : move to main code
ActionRunner* g_action_runner = ActionRunner::get_instance();

Actions::Actions(int pages)
{
}

void Actions::reset()
{
	cur_ac = nullptr;
	for (int i = 0; i < acs.size(); ++i)
	{
		acs[i]->reset();
	}
}

void Actions::put_action(Ac * ac,int page)
{
	acs.push_back(ac);
}

void Actions::next_action()
{

}

WaitTriggerPushKey::WaitTriggerPushKey()
{

}

bool WaitTriggerPushKey::run(float dt)
{
	if (end)
		return true;
	if (!begin)
	{
		init(dt);
		begin = true;
	}
	if (doing(dt))
	{
		end = true;
		return true;
	}
	return false;
}

bool WaitTriggerPushKey::doing(float dt)
{
	if (Input::eat_sys_key_down(WIP_SPACE))
	{
		end = true;
		return true;
	}
	time += dt;
	return false;
}

void WaitTriggerPushKey::init(float dt)
{
}

SetGameVaribleReal::SetGameVaribleReal(const std::string& name, float t)
{
	var_name = name;
	tg = t;
}

bool SetGameVaribleReal::run(float dt)
{
	if (end)
		return true;
	if (!begin)
	{
		init(dt);
		begin = true;
	}
	if (doing(dt))
	{
		end = true;
		return true;
	}
	return false;
}

bool SetGameVaribleReal::doing(float dt)
{
	
	g_game_data->game_varible[var_name].number.real = tg;
	end = true;
	return true;
	
	time + dt;
	return false;
}

void SetGameVaribleReal::init(float dt)
{
}

SetGameVaribleInt::SetGameVaribleInt(const std::string& name, int t)
{
	var_name = name;
	tg = t;
}

bool SetGameVaribleInt::run(float dt)
{
	if (end)
		return true;
	if (!begin)
	{
		init(dt);
		begin = true;
	}
	if (doing(dt))
	{
		end = true;
		return true;
	}
	return false;
}

bool SetGameVaribleInt::doing(float dt)
{

	g_game_data->game_varible[var_name].number.integer = tg;
	end = true;
	return true;

	time + dt;
	return false;
}
void SetGameVaribleInt::init(float dt)
{
}


SetGameVaribleText::SetGameVaribleText(const std::string& name, const std::string& t)
{
	var_name = name;
	tg = t;
}

bool SetGameVaribleText::run(float dt)
{
	if (end)
		return true;
	if (!begin)
	{
		init(dt);
		begin = true;
	}
	if (doing(dt))
	{
		end = true;
		return true;
	}
	return false;
}

bool SetGameVaribleText::doing(float dt)
{

	g_game_data->game_varible[var_name].text = tg;
	end = true;
	return true;

	time + dt;
	return false;
}

void SetGameVaribleText::init(float dt)
{
}

Wait::Wait(f32 ttt)
{
	_ttt = ttt;
}

bool Wait::run(float dt)
{
	if (end)
		return true;
	if (!begin)
	{
		init(dt);
		begin = true;
	}
	if (doing(dt))
	{
		end = true;
		return true;
	}
	return false;
}

bool Wait::doing(float dt)
{
	if (time >= _ttt)
	{
		end = true;
		return true;
	}
	time += dt;
	return false;
}

void Wait::init(float dt)
{
}

bool ImmediateAction::run(float dt)
{
	if (end)
		return true;
	if (!begin)
	{
		init(dt);
		begin = true;
	}
	if (doing(dt))
	{
		end = true;
		return true;
	}
	return false;
}

ChangeObjectCallbackState::ChangeObjectCallbackState(WIPSprite* sp, CALLBACKTYPE ctp,bool c)
{
	s = sp;
	tp = ctp;
	val = c;
}

bool ChangeObjectCallbackState::doing(float dt)
{
	switch (tp)
	{
	case PLAY_BEGINCONTACT:
		evc->set_onbegincontact(val);
		break;
	case PLAY_ONCONTACT:
		evc->set_oncontact(val);
		break;
	case PLAY_ENDCONTACT:
		evc->set_onendcontact(val);
		break;
	case PLAY_UPDATE:
		evc->set_update(val);
		break;
	default:
		break;
	}
	return true;
}

void ChangeObjectCallbackState::init(float dt)
{
	evc = (EventComponent*)s->get_component_by_name("EventComponent");
}

void SetCharacterState::init(float dt)
{
}

ChangeCharracterAIControllState::ChangeCharracterAIControllState(WIPSprite * ts, bool v)
	:s(ts),val(v)
{}

bool ChangeCharracterAIControllState::doing(float dt)
{
	evc->actived = val;
	if(!val)
		evc->play_stand_animation();
	return false;
}

void ChangeCharracterAIControllState::init(float dt)
{
	evc = (CharacterAIControll*)s->get_component<CharacterAIControll>();
}
