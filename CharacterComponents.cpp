#include "CharacterComponents.h"

CharacterComponent::CharacterComponent(WIPSprite * s) :
	WIPTickComponent(s)
{

}

void CharacterComponent::init()
{
}

void CharacterComponent::update(f32 dt)
{

}

CharacterControll::CharacterControll(WIPSprite * s) :
	WIPTickComponent(s)
{

}

void CharacterControll::init()
{
	old_pos = RBVector3::zero_vector;
	map = (MapComponent*)g_scene->get_sprite_by_tag("bg")->get_component_by_name("MapComponent");
}

void CharacterControll::update(f32 dt)
{
	controll(dt);
	map->fix_sprite_position(host_object, old_pos);
	old_pos.x = host_object->_transform->world_x;
	old_pos.y = host_object->_transform->world_y;
}

CharacterPlayerControll::CharacterPlayerControll(WIPSprite * s)
	:CharacterControll(s)
{
	man_state = ManState::E_UP;
}

void CharacterPlayerControll::init()
{
	CharacterControll::init();
	stop_hs = get_string_hash("stop player controll");
	restore_hs = get_string_hash("restore player controll");
	subscribe_event(map, stop_hs, WIP_EVENT_HANDLER(CharacterPlayerControll, switch_controll));
	subscribe_event(map, restore_hs, WIP_EVENT_HANDLER(CharacterPlayerControll, switch_controll));

}

void CharacterPlayerControll::controll(f32 dt)
{
	if (!actived) return;
	auto* man = host_object;
	float speed = 13.2f;
	if (Input::get_key_pressed(WIP_W))
	{
		man->translate(0, speed*dt);
		man->_animation->play_name("walk_up", false);
		man_state = ManState::E_UP;
	}
	else if (Input::get_key_pressed(WIP_A))
	{
		man->translate(-speed*dt, 0);
		if (man->_animation->play_name("walk_left", false));
		man_state = ManState::E_LEFT;
	}
	else if (Input::get_key_pressed(WIP_S))
	{
		man->translate(0, -speed*dt);
		if (man->_animation->play_name("walk_down", false));
		man_state = ManState::E_DOWN;
	}
	else if (Input::get_key_pressed(WIP_D))
	{
		man->translate(speed*dt, 0);
		if (man->_animation->play_name("walk_right", false));
		man_state = ManState::E_RIGHT;
	}
	else
	{
		switch (man_state)
		{
		case ManState::E_DOWN:
			man->_animation->play_name("stand_down", false);
			break;
		case ManState::E_LEFT:
			man->_animation->play_name("stand_left", false);
			break;
		case ManState::E_RIGHT:
			man->_animation->play_name("stand_right", false);
			break;
		case ManState::E_UP:
			man->_animation->play_name("stand_up", false);
			break;
		}

	}
}

void CharacterPlayerControll::switch_controll(string_hash tp, void * data)
{
	actived = (tp == restore_hs);
}

CharacterAIControll::CharacterAIControll(WIPSprite * s) :CharacterControll(s)
{
}

void CharacterAIControll::init()
{
	CharacterControll::init();
	stop_hs = get_string_hash("stop ai controll");
	restore_hs = get_string_hash("restore ai controll");
	subscribe_event(map, stop_hs, WIP_EVENT_HANDLER(CharacterAIControll, switch_controll));
	subscribe_event(map, restore_hs, WIP_EVENT_HANDLER(CharacterAIControll, switch_controll));

}


void CharacterAIControll::controll(f32 dt)
{
	if (!actived)
	{
		
		return;
	}
	if (wait_seconds(1.523f,dt))
	{
		int i = RBMath::get_rand_i(4);
		switch (i)
		{
		case 0:
			sx = 1.f; sy = 0.f;
			man_state = ManState::E_LEFT;
			host_object->_animation->play_name("walk_left", true);
			break;
		case 1:
			sx = 0.f; sy = 1.f;
			man_state = ManState::E_UP;
			host_object->_animation->play_name("walk_up", true);
			break;
		case 2:
			sx = -1.f; sy = 0.f;
			man_state = ManState::E_RIGHT;
			host_object->_animation->play_name("walk_right", true);
			break;
		case 3:
			sx = 0.f; sy = -1.f;
			man_state = ManState::E_DOWN;
			host_object->_animation->play_name("walk_down", true);
			break;
		default:
			break;
		}
	}
	RBVector2 speed(sx, sy);
	speed *= dt;
	host_object->translate(speed.x, speed.y);
}

void CharacterAIControll::play_stand_animation()
{
	
	{
		switch (man_state)
		{
		case ManState::E_DOWN:
			host_object->_animation->play_name("stand_down", false);
			break;
		case ManState::E_LEFT:
			host_object->_animation->play_name("stand_left", false);
			break;
		case ManState::E_RIGHT:
			host_object->_animation->play_name("stand_right", false);
			break;
		case ManState::E_UP:
			host_object->_animation->play_name("stand_up", false);
			break;
		}
	}
}

void CharacterAIControll::switch_controll(string_hash tp, void * data)
{
	actived = (tp == restore_hs);
	if (!actived) play_stand_animation();
}

bool CharacterAIControll::wait_seconds(f32 seconds,f32 dt)
{
	sp_time += dt;
	if (sp_time >= seconds)
	{
		sp_time = 0.f;
		return true;
	}
	return false;
}
