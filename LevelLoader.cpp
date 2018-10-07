#include "LevelLoader.h"
#include "PhysicsManager.h"
#include "FDGameComponent.h"
#include "GameApp.h"
#include "Input.h"
#include "InputManager.h"
#include "GameAction.h"
#include "CharacterComponents.h"

//时间轴，时间驱动动画，所有涉及动画的object都有一条时间轴，所有object的属性变化全部根据事件计算出来 
//动画系统实现
//各个模块与时间挂钩的都要实现一个方法：给定当前时间，返回当前状态


void FDLevelLoader::test_load_persistent()
{
	scene->set_level_load();

}

void FDLevelLoader::test_load_level1()
{

}

void FDLevelLoader::test_reload_level()
{
	//scene->reset_level_load_state();
	scene->set_level_unload();
	//scene->set_level_load();

	test_load_level();
}


void FDLevelLoader::load_level_findingdogs_1()
{
	scene->set_level_unload();
	scene->set_level_load();
	WIPCamera* cam = WIPScene::create_camera(20.f, 20.f, 0,0,game->window_w, game->window_h, game->window_w, game->window_h);
	cam->set_name("MainCam");
	cam->move_to(5.f, 5.f);
	g_temp_uisys->change_camera(cam);
	g_physics_manager->set_debug_camera(cam);
	scene->load_camera(cam);
	WorldRender* world_renderer = game->world_renderer;
	auto *clip_down = WIPAnimationClip::create_with_atlas("walk_down", "./pic/fd/fd_clip_0.clip");
	auto *clip_left = WIPAnimationClip::create_with_atlas("walk_left", "./pic/fd/fd_clip_1.clip");
	auto *clip_right = WIPAnimationClip::create_with_atlas("walk_right", "./pic/fd/fd_clip_2.clip");
	auto *clip_up = WIPAnimationClip::create_with_atlas("walk_up", "./pic/fd/fd_clip_3.clip");
	auto *clip_s_down = WIPAnimationClip::create_with_atlas("stand_down", "./pic/fd/fd_clip_0_s.clip");
	auto *clip_s_left = WIPAnimationClip::create_with_atlas("stand_left", "./pic/fd/fd_clip_1_s.clip");
	auto *clip_s_right = WIPAnimationClip::create_with_atlas("stand_right", "./pic/fd/fd_clip_2_s.clip");
	auto *clip_s_up = WIPAnimationClip::create_with_atlas("stand_up", "./pic/fd/fd_clip_3_s.clip");

	auto res_handle_background = g_res_manager->load_resource("./pic/fd/mudian.jpg", WIPResourceType::TEXTURE);
	int bg_w = ((TextureData *)(res_handle_background->extra))->width;
	int bg_h = ((TextureData *)(res_handle_background->extra))->height;


	auto res_handle_c1 = g_res_manager->load_resource("./pic/fd/c1.png", WIPResourceType::TEXTURE);
	int c1_w = ((TextureData *)(res_handle_c1->extra))->width;
	int c1_h = ((TextureData *)(res_handle_c1->extra))->height;

	auto res_handle_c2 = g_res_manager->load_resource("./pic/fd/c2.png", WIPResourceType::TEXTURE);
	int c2_w = ((TextureData *)(res_handle_c2->extra))->width;
	int c2_h = ((TextureData *)(res_handle_c2->extra))->height;

	auto res_handle_fls = g_res_manager->load_resource("./pic/fd/flash1.png", WIPResourceType::TEXTURE);
	int fls_w = ((TextureData *)(res_handle_fls->extra))->width;
	int fls_h = ((TextureData *)(res_handle_fls->extra))->height;

	auto *tex2d_bg = g_rhi->RHICreateTexture2D(bg_w, bg_h, res_handle_background->ptr);
	auto *tex2d_c1 = g_rhi->RHICreateTexture2D(c1_w, c1_h, res_handle_c1->ptr, 0, 0, 0, 1);
	auto *tex2d_c2 = g_rhi->RHICreateTexture2D(c2_w, c2_h, res_handle_c2->ptr);
	auto *tex2d_c3 = g_rhi->RHICreateTexture2D(fls_w, fls_h, res_handle_fls->ptr);


	//avator
	WIPSpriteCreator ctor_c1(3.6f*0.5, 3.6f, WIPMaterialType::E_TRANSLUCENT);
	ctor_c1.texture = tex2d_c1;
	ctor_c1.world_render = world_renderer;
	ctor_c1.body_tp = WIPCollider::_CollisionTypes::E_RIGIDBODY;
	ctor_c1.collider_sx = 0.5f;
	ctor_c1.collider_sy = 0.2f;
	auto* man_c1 = WIPSpriteFactory::create_sprite(ctor_c1);
	man_c1->_animation->add_clip(clip_down, clip_down->name);
	man_c1->_animation->add_clip(clip_left, clip_left->name);
	man_c1->_animation->add_clip(clip_right, clip_right->name);
	man_c1->_animation->add_clip(clip_up, clip_up->name);
	man_c1->_animation->add_clip(clip_s_down, clip_s_down->name);
	man_c1->_animation->add_clip(clip_s_left, clip_s_left->name);
	man_c1->_animation->add_clip(clip_s_right, clip_s_right->name);
	man_c1->_animation->add_clip(clip_s_up, clip_s_up->name);
	man_c1->_animation->play(clip_s_down);
	man_c1->set_anchor(0.5f, 0.05f);
	man_c1->set_tag("man");
	man_c1->set_type_tag("character");
	scene->load_sprite(man_c1);
	man_c1->translate_to(8.f, 1.f);
	man_c1->set_z_order(0.4f);
	man_c1->add_tick_component(
		(CharacterPlayerControll*)WIPObject::create_tick_component("CharacterPlayerControll", man_c1)
	);


	WIPSpriteCreator ctor_bg(40.f, 40.f*((float)bg_h / bg_w), WIPMaterialType::E_TRANSLUCENT);
	ctor_bg.texture = tex2d_bg;
	ctor_bg.world_render = world_renderer;
	ctor_bg.body_tp = WIPCollider::_CollisionTypes::E_NO_PHYSICS;
	auto* bg = WIPSpriteFactory::create_sprite(ctor_bg);
	MapComponent* mc = (MapComponent*)WIPObject::create_tick_component("MapComponent", bg);
	bg->add_tick_component(mc);
	bg->translate_to(0.f, 0.f);
	bg->set_z_order(0.9f);
	scene->load_sprite(bg);

	auto res_handle1fog = g_res_manager->load_resource("./pic/fog.png", WIPResourceType::TEXTURE);
	int ww1fog = ((TextureData *)(res_handle1fog->extra))->width;
	int hh1fog = ((TextureData *)(res_handle1fog->extra))->height;
	auto *tex2d_fog = g_rhi->RHICreateTexture2D(ww1fog, hh1fog, res_handle1fog->ptr);
	WIPSpriteCreator ctor_fog(20.f, 20.f, WIPMaterialType::E_TRANSLUCENT);
	ctor_fog.texture = tex2d_fog;
	ctor_fog.world_render = world_renderer;
	ctor_fog.body_tp = WIPCollider::_CollisionTypes::E_NO_PHYSICS;
	auto* fogs = WIPSpriteFactory::create_sprite(ctor_fog);
	fogs->set_tag("fog");
	scene->load_sprite(fogs);
	fogs->set_type_tag("scene");
	fogs->translate_to(0.f, 0.f);
	fogs->set_z_order(0.05f);
}

struct MoveParam
{
	MoveParam(int i, const RBVector2& p) :id(i), pos(p) {}
	int id;
	RBVector2 pos;
};

void transform_event(void* data, const WIPSprite* s, float dt, TransformComponent* t)
{
	MoveParam* p = (MoveParam*)data;
	g_scene->load_level(p->id, p->pos);
}





//todo : release level resource ! include Acs textures and so on.
void FDLevelLoader::load_caodi(const RBVector2& postion)
{
	scene->set_level_unload();
	scene->set_level_load();
	WIPCamera* cam = WIPScene::create_camera(20.f, 20.f,0,0, game->window_w, game->window_h, game->window_w, game->window_h);
	cam->set_name("MainCam");
	cam->move_to(postion.x - 0.3f, postion.y - 0.3f);
	g_temp_uisys->change_camera(cam);
	g_physics_manager->set_debug_camera(cam);
	scene->load_camera(cam);
	WorldRender* world_renderer = game->world_renderer;
	auto *clip_down = WIPAnimationClip::create_with_atlas("walk_down", "./pic/fd/fd_clip_0.clip");
	auto *clip_left = WIPAnimationClip::create_with_atlas("walk_left", "./pic/fd/fd_clip_1.clip");
	auto *clip_right = WIPAnimationClip::create_with_atlas("walk_right", "./pic/fd/fd_clip_2.clip");
	auto *clip_up = WIPAnimationClip::create_with_atlas("walk_up", "./pic/fd/fd_clip_3.clip");
	auto *clip_s_down = WIPAnimationClip::create_with_atlas("stand_down", "./pic/fd/fd_clip_0_s.clip");
	auto *clip_s_left = WIPAnimationClip::create_with_atlas("stand_left", "./pic/fd/fd_clip_1_s.clip");
	auto *clip_s_right = WIPAnimationClip::create_with_atlas("stand_right", "./pic/fd/fd_clip_2_s.clip");
	auto *clip_s_up = WIPAnimationClip::create_with_atlas("stand_up", "./pic/fd/fd_clip_3_s.clip");

	auto res_handle_background = g_res_manager->load_resource("./pic/fd/caodi.png", WIPResourceType::TEXTURE);
	int bg_w = ((TextureData *)(res_handle_background->extra))->width;
	int bg_h = ((TextureData *)(res_handle_background->extra))->height;

	auto res_handle1mask = g_res_manager->load_resource("./pic/fd/caodi_mask.png", WIPResourceType::TEXTURE);
	int ww1mask = ((TextureData *)(res_handle1mask->extra))->width;
	int hh1mask = ((TextureData *)(res_handle1mask->extra))->height;

	auto res_handle_c1 = g_res_manager->load_resource("./pic/fd/c1.png", WIPResourceType::TEXTURE);
	int c1_w = ((TextureData *)(res_handle_c1->extra))->width;
	int c1_h = ((TextureData *)(res_handle_c1->extra))->height;

	auto res_handle_c2 = g_res_manager->load_resource("./pic/fd/c2.png", WIPResourceType::TEXTURE);
	int c2_w = ((TextureData *)(res_handle_c2->extra))->width;
	int c2_h = ((TextureData *)(res_handle_c2->extra))->height;

	auto res_handle_fls = g_res_manager->load_resource("./pic/fd/flash1.png", WIPResourceType::TEXTURE);
	int fls_w = ((TextureData *)(res_handle_fls->extra))->width;
	int fls_h = ((TextureData *)(res_handle_fls->extra))->height;

	auto *tex2d_bg = g_rhi->RHICreateTexture2D(bg_w, bg_h, res_handle_background->ptr);
	auto *tex2d1mask = g_rhi->RHICreateTexture2D(ww1mask, hh1mask, res_handle1mask->ptr, 0, 0, 0, 1);
	auto *tex2d_c1 = g_rhi->RHICreateTexture2D(c1_w, c1_h, res_handle_c1->ptr, 0, 0, 0, 1);
	auto *tex2d_c2 = g_rhi->RHICreateTexture2D(c2_w, c2_h, res_handle_c2->ptr);
	auto *tex2d_c3 = g_rhi->RHICreateTexture2D(fls_w, fls_h, res_handle_fls->ptr);


	//avator
	WIPSpriteCreator ctor_c1(3.6f*0.5, 3.6f, WIPMaterialType::E_TRANSLUCENT);
	ctor_c1.texture = tex2d_c1;
	ctor_c1.world_render = world_renderer;
	ctor_c1.body_tp = WIPCollider::_CollisionTypes::E_RIGIDBODY;
	ctor_c1.collider_sx = 0.5f;
	ctor_c1.collider_sy = 0.2f;
	auto* man_c1 = WIPSpriteFactory::create_sprite(ctor_c1);
	man_c1->_animation->add_clip(clip_down, clip_down->name);
	man_c1->_animation->add_clip(clip_left, clip_left->name);
	man_c1->_animation->add_clip(clip_right, clip_right->name);
	man_c1->_animation->add_clip(clip_up, clip_up->name);
	man_c1->_animation->add_clip(clip_s_down, clip_s_down->name);
	man_c1->_animation->add_clip(clip_s_left, clip_s_left->name);
	man_c1->_animation->add_clip(clip_s_right, clip_s_right->name);
	man_c1->_animation->add_clip(clip_s_up, clip_s_up->name);
	man_c1->_animation->play(clip_s_down);
	man_c1->set_anchor(0.5f, 0.05f);
	man_c1->set_tag("man");
	man_c1->set_type_tag("character");
	scene->load_sprite(man_c1);
	man_c1->translate_to(postion.x, postion.y);
	man_c1->set_z_order(0.4f);
	man_c1->add_tick_component(
		(CharacterPlayerControll*)WIPObject::create_tick_component("CharacterPlayerControll", man_c1)
	);
	//man_c1->set_persistent();

	WIPSpriteCreator ctor_trs1(3.6f, 3.6f, WIPMaterialType::E_TRANSLUCENT);
	ctor_trs1.texture = tex2d_c3;
	ctor_trs1.world_render = world_renderer;
	ctor_trs1.body_tp = WIPCollider::_CollisionTypes::E_GHOST;
	ctor_trs1.collider_sx = 0.5f;
	ctor_trs1.collider_sy = 0.2f;
	auto* man_trans1 = WIPSpriteFactory::create_sprite(ctor_trs1);
	man_trans1->_animation->add_clip(clip_down, clip_s_down->name);
	man_trans1->_animation->play_name(clip_s_down->name, true);
	man_trans1->set_anchor(0.5f, 0.05f);
	man_trans1->set_tag("trans1");
	man_trans1->set_type_tag("character");
	TransformComponent* tc1 = (TransformComponent*)WIPObject::create_tick_component("TransformComponent", man_trans1);
	tc1->call_data[2] = new MoveParam(2, RBVector2(9.5, -15));
	tc1->func_contact = [](void* data, const WIPSprite* s, float dt, TransformComponent* t)->void
	{
		std::map<std::string, Game_Varible>::iterator v = g_game_data->game_varible.find("step_in");
		if (v == g_game_data->game_varible.end())
		{
			g_game_data->game_varible["step_in"] = Game_Varible(0);
		}
		if (g_game_data->game_varible["step_in"].number.integer != 0)
		{
			transform_event(data, s, dt, t);
		}
		else
		{
			g_scene->get_sprite_by_tag("man")->translate_to(6.6, -12.6);
			//if (g_scene->game_varible["know cannot pass"].number.integer == 0)
			g_game_data->game_varible["know cannot pass"].number.integer += 1;
		}
	};
	man_trans1->add_tick_component(tc1);
	scene->load_sprite(man_trans1);
	man_trans1->translate_to(-3.4, 13.4);
	man_trans1->set_z_order(0.4f);





	WIPSpriteCreator ctor_bg(25.f, 25.f*((float)bg_h / bg_w), WIPMaterialType::E_TRANSLUCENT);
	ctor_bg.texture = tex2d_bg;
	ctor_bg.world_render = world_renderer;
	ctor_bg.body_tp = WIPCollider::_CollisionTypes::E_NO_PHYSICS;
	auto* bg = WIPSpriteFactory::create_sprite(ctor_bg);
	MapComponent* mc = (MapComponent*)WIPObject::create_tick_component("MapComponent", bg);
	mc->mask_path = "./caodi.mask";
	bg->add_tick_component(mc);
	bg->translate_to(0.f, 0.f);
	bg->set_z_order(0.9f);
	bg->set_tag("bg");
	scene->load_sprite(bg);

	WIPSpriteCreator ctor_mask(25.f, 25.f*((float)bg_h / bg_w), WIPMaterialType::E_TRANSLUCENT);
	ctor_mask.texture = tex2d1mask;
	ctor_mask.world_render = world_renderer;
	ctor_mask.body_tp = WIPCollider::_CollisionTypes::E_NO_PHYSICS;
	auto* bg_mask = WIPSpriteFactory::create_sprite(ctor_mask);
	bg_mask->set_tag("mask");
	bg_mask->set_type_tag("scene");
	bg_mask->translate_to(0.f, 0.f);
	bg_mask->set_z_order(0.1f);
	scene->load_sprite(bg_mask);

	auto res_handle1fog = g_res_manager->load_resource("./pic/fog.png", WIPResourceType::TEXTURE);
	int ww1fog = ((TextureData *)(res_handle1fog->extra))->width;
	int hh1fog = ((TextureData *)(res_handle1fog->extra))->height;
	auto *tex2d_fog = g_rhi->RHICreateTexture2D(ww1fog, hh1fog, res_handle1fog->ptr);
	WIPSpriteCreator ctor_fog(20.f, 20.f, WIPMaterialType::E_TRANSLUCENT);
	ctor_fog.texture = tex2d_fog;
	ctor_fog.world_render = world_renderer;
	ctor_fog.body_tp = WIPCollider::_CollisionTypes::E_NO_PHYSICS;
	auto* fogs = WIPSpriteFactory::create_sprite(ctor_fog);
	fogs->set_tag("fog");
	scene->load_sprite(fogs);
	fogs->set_type_tag("scene");

	fogs->translate_to(RBMath::get_rand_range_f(scene->world_size_x, scene->world_size_y), RBMath::get_rand_range_f(scene->world_size_x, scene->world_size_y));
	fogs->set_z_order(0.05f);

	{
		WIPSpriteCreator ctor_trs1(1.000000, 1.000000, WIPMaterialType::E_OTHER);
		ctor_trs1.texture = 0;
		ctor_trs1.world_render = 0;
		ctor_trs1.body_tp = WIPCollider::_CollisionTypes::E_STATIC_RIGIDBODY;
		ctor_trs1.collider_sx = 1.0f;
		ctor_trs1.collider_sy = 1.0f;
		auto* man_trans1 = WIPSpriteFactory::create_sprite(ctor_trs1);
		man_trans1->set_anchor(0.f, 0.f);
		man_trans1->set_tag("eat_host");
		man_trans1->set_type_tag("trigger");
		man_trans1->translate_to(-7.20000, -10.60000);
		man_trans1->_render->is_visible = false;
		man_trans1->rotate_to(0.000000);
		TransformComponent* tc1 = (TransformComponent*)WIPObject::create_tick_component("TransformComponent", man_trans1);
		tc1->func_end = [](void* data, const WIPSprite* s, TransformComponent* t)->void
		{
			t->send_event(get_string_hash("player"));
		};
		auto* data = new NPCTalkParam();
		auto* npcdata = new NPCDisplayData();
		npcdata->word_tp = NPCDisplayData::E_TALK;
		npcdata->npc_size = RBVector3(man_trans1->_transform->world_x, man_trans1->_transform->world_y, 100);


		ActionSet* as = new ActionSet();
		Actions* evt = new Actions();
		evt->loop = true;
		
		evt->put_action(new WaitTriggerPushKey());
		evt->put_action(new TalkAc(L"老夫光绪三十年来此，年生不好啊...", npcdata, mc, tc1));
		evt->put_action(new TalkAc(L"什么东西都卖不出去，回去的路也找不到了......", npcdata, mc, tc1));
		evt->put_action(new TalkAc(L"今天来一个人吃了一天了...", npcdata, mc, tc1));
		evt->put_action(new TalkAc(L"......", npcdata, mc, tc1));
		evt->put_action(new TalkAc(L"年轻人你这么匆忙，要去哪儿呀？", npcdata, mc, tc1));
		evt->put_action(new ChangeGameState(mc,GameState::E_PLAYER_CONTROLL));
		Actions* evt1 = new Actions();
		evt1->loop = true;
		evt1->put_action(new WaitTriggerPushKey());

		evt1->put_action(new TalkAc(L"年轻人，你要离开了吗？...", npcdata, mc, tc1));
		evt1->put_action(new TalkAc(L"请你喝碗茶再走吧...", npcdata, mc, tc1));
		evt1->put_action(new ChangeGameState(mc,GameState::E_PLAYER_CONTROLL));

		as->acss.push_back(evt1);
		as->acss.push_back(evt);

		tc1->call_data[BEGIN_EVENT] = as;
		tc1->func_begin = [](void* da, const WIPSprite* s, TransformComponent* t)
		{
			ActionSet* data = (ActionSet*)da;
			if (g_game_data->game_varible["step_in"].number.integer == 0)
			{
				g_action_runner->ready_run_action(data->acss[1]);
			}
			else
			{
				g_action_runner->ready_run_action(data->acss[0]);
			}
		};

		tc1->call_data[CONTACT_EVENT] = as;
		tc1->func_contact = [](void* data1, const WIPSprite* s, float dt, TransformComponent* t)->void
		{
			ActionSet* data = (ActionSet*)data1;
			MapComponent* map_component = t->map_component;
			{
				bool r;
				if (g_game_data->game_varible["step_in"].number.integer == 0)
				{
					g_action_runner->run_action(data->acss[1], dt);
				}
				else
				{
					g_action_runner->run_action(data->acss[0], dt);
				}

			}
			g_input_manager->restore_eat();
		};

		tc1->func_end = [](void* da, const WIPSprite* s, TransformComponent* t)
		{
			g_action_runner->end_run_action();
		};

		man_trans1->add_tick_component(tc1);

		scene->load_sprite(man_trans1);


		mc->subscribe_event(tc1, get_string_hash("npc talk"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_talk, mc));
		mc->subscribe_event(tc1, get_string_hash("player"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_player, mc));
	}

	{
		WIPSpriteCreator ctor_trs1(1.000000, 1.000000, WIPMaterialType::E_OTHER);
		ctor_trs1.texture = 0;
		ctor_trs1.world_render = 0;
		ctor_trs1.body_tp = WIPCollider::_CollisionTypes::E_STATIC_RIGIDBODY;
		ctor_trs1.collider_sx = 1.0f;
		ctor_trs1.collider_sy = 1.0f;
		auto* man_trans1 = WIPSpriteFactory::create_sprite(ctor_trs1);
		man_trans1->set_anchor(0.f, 0.f);
		man_trans1->set_tag("eat_peopel");
		man_trans1->set_type_tag("trigger");
		EventComponent* tc1 = (EventComponent*)WIPObject::create_tick_component("TransformComponent", man_trans1);





		//tc1->func_end = [](void* data, const WIPSprite* s, TransformComponent* t)->void
		//{
			//t->send_event(get_string_hash("player"));
		//};
		auto* data = new NPCTalkParam();
		auto* npcdata = new NPCDisplayData();

		ActionSet* as = new ActionSet();
		Actions* evt = new Actions();
		evt->loop = true;
		evt->put_action(new WaitTriggerPushKey());
		evt->put_action(new TalkAc(L"年轻人，你是不是一直在这里走不出去?", npcdata, mc, tc1));
		evt->put_action(new TalkAc(L"你是不是会莫名其妙地被挡住去路？", npcdata, mc, tc1));
		evt->put_action(new TalkAc(L"你怕是碰见鬼打墙了...", npcdata, mc, tc1));
		evt->put_action(new ChangeGameState(mc,GameState::E_PLAYER_CONTROLL));

		Actions* evt1 = new Actions();
		evt1->loop = true;
		evt1->put_action(new WaitTriggerPushKey());
		evt1->put_action(new TalkAc(L"嘻嘻，跟你开个玩笑，现在你可以走了...", npcdata, mc, tc1));
		evt1->put_action(new TalkAc(L"年生不好，吃饭不饱...", npcdata, mc, tc1));
		evt1->put_action(new TalkAc(L"好吃，吃啊，吃啊，吃啊吃...", npcdata, mc, tc1));
		evt1->put_action(new ChangeGameState(mc,GameState::E_PLAYER_CONTROLL));

		as->acss.push_back(evt);
		as->acss.push_back(evt1);

		tc1->call_data[BEGIN_EVENT] = as;
		tc1->func_begin = [](void* da, const WIPSprite* s, TransformComponent* t)
		{
			ActionSet* data = (ActionSet*)da;
			if (g_game_data->game_varible["know cannot pass"].number.integer > 3)
			{
				g_action_runner->ready_run_action(data->acss[1]);
			}
			else
			{
				g_action_runner->ready_run_action(data->acss[0]);
			}
		};

		tc1->call_data[CONTACT_EVENT] = as;
		tc1->func_contact = [](void* data1, const WIPSprite* s, float dt, TransformComponent* t)->void
		{
			ActionSet* data = (ActionSet*)data1;
			MapComponent* map_component = t->map_component;
			{
				bool r;
				if (g_game_data->game_varible["know cannot pass"].number.integer > 3)
				{
					if (g_action_runner->run_action(data->acss[1], dt))
					{
						std::map<std::string, Game_Varible>::iterator v = g_game_data->game_varible.find("step_in");
						if (v == g_game_data->game_varible.end())
						{
							g_game_data->game_varible["step_in"] = Game_Varible(0);
						}
						if (g_game_data->game_varible["step_in"].number.integer == 0)
						{
							g_game_data->game_varible["step_in"] = Game_Varible(1);
						}
					}
				}
				else
				{
					g_action_runner->run_action(data->acss[0], dt);
				}

			}
			g_input_manager->restore_eat();
		};

		//tc1->func_end = [](void* da, const WIPSprite* s, TransformComponent* t)
		//{
			//g_action_runner->end_run_action();
		//};
		man_trans1->add_tick_component(tc1);

		scene->load_sprite(man_trans1);
		man_trans1->translate_to(-5.40000, -2.60000);
		man_trans1->_render->is_visible = false;
		man_trans1->rotate_to(0.000000);

		npcdata->word_tp = NPCDisplayData::E_TALK;
		npcdata->npc_size = RBVector3(man_trans1->_transform->world_x, man_trans1->_transform->world_y, 100);

		mc->subscribe_event(tc1, get_string_hash("npc talk"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_talk, mc));
		mc->subscribe_event(tc1, get_string_hash("player"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_player, mc));
	}

	//场景处理触发器
	{
		WIPSpriteCreator ctor_trs1(1.000000, 1.000000, WIPMaterialType::E_OTHER);
		ctor_trs1.texture = 0;
		ctor_trs1.world_render = 0;
		ctor_trs1.body_tp = WIPCollider::_CollisionTypes::E_NO_PHYSICS;
		ctor_trs1.collider_sx = 1.0f;
		ctor_trs1.collider_sy = 1.0f;
		auto* man_trans1 = WIPSpriteFactory::create_sprite(ctor_trs1);
		man_trans1->set_anchor(0.f, 0.f);
		man_trans1->set_tag("tile");
		man_trans1->set_type_tag("trigger");
		TransformComponent* tc1 = (TransformComponent*)WIPObject::create_tick_component("TransformComponent", man_trans1);
		tc1->call_data[LEVEL_START] = mc;
		tc1->func_level_start = [](void* data, TransformComponent* t)->void
		{
			if (g_game_data->game_varible["title"].number.integer == 1)
			{
				MapComponent* mc = (MapComponent*)data;
				mc->game_state = GameState::E_TITLE;
			}

		};

		man_trans1->add_tick_component(tc1);



		scene->load_sprite(man_trans1);
		man_trans1->translate_to(-15.40000, -2.60000);
		man_trans1->_render->is_visible = false;
		man_trans1->rotate_to(0.000000);


	}

}
void FDLevelLoader::load_huangdi(const RBVector2& postion)
{
	scene->set_level_unload();
	scene->set_level_load();
	WIPCamera* cam = WIPScene::create_camera(20.f, 20.f, 0,0,g_app->window_w, g_app->window_h, g_app->window_w, g_app->window_h);
	cam->set_name("MainCam");
	cam->move_to(postion.x - 0.3f, postion.y - 0.3f);
	g_temp_uisys->change_camera(cam);
	g_physics_manager->set_debug_camera(cam);
	scene->load_camera(cam);
	WorldRender* world_renderer = game->world_renderer;
	auto *clip_down = WIPAnimationClip::create_with_atlas("walk_down", "./pic/fd/fd_clip_0.clip");
	auto *clip_left = WIPAnimationClip::create_with_atlas("walk_left", "./pic/fd/fd_clip_1.clip");
	auto *clip_right = WIPAnimationClip::create_with_atlas("walk_right", "./pic/fd/fd_clip_2.clip");
	auto *clip_up = WIPAnimationClip::create_with_atlas("walk_up", "./pic/fd/fd_clip_3.clip");
	auto *clip_s_down = WIPAnimationClip::create_with_atlas("stand_down", "./pic/fd/fd_clip_0_s.clip");
	auto *clip_s_left = WIPAnimationClip::create_with_atlas("stand_left", "./pic/fd/fd_clip_1_s.clip");
	auto *clip_s_right = WIPAnimationClip::create_with_atlas("stand_right", "./pic/fd/fd_clip_2_s.clip");
	auto *clip_s_up = WIPAnimationClip::create_with_atlas("stand_up", "./pic/fd/fd_clip_3_s.clip");

	auto res_handle_background = g_res_manager->load_resource("./pic/fd/huangdi.png", WIPResourceType::TEXTURE);
	int bg_w = ((TextureData *)(res_handle_background->extra))->width;
	int bg_h = ((TextureData *)(res_handle_background->extra))->height;


	auto res_handle_c1 = g_res_manager->load_resource("./pic/fd/c1.png", WIPResourceType::TEXTURE);
	int c1_w = ((TextureData *)(res_handle_c1->extra))->width;
	int c1_h = ((TextureData *)(res_handle_c1->extra))->height;

	auto res_handle_c2 = g_res_manager->load_resource("./pic/fd/c2.png", WIPResourceType::TEXTURE);
	int c2_w = ((TextureData *)(res_handle_c2->extra))->width;
	int c2_h = ((TextureData *)(res_handle_c2->extra))->height;

	auto res_handle_fls = g_res_manager->load_resource("./pic/fd/flash1.png", WIPResourceType::TEXTURE);
	int fls_w = ((TextureData *)(res_handle_fls->extra))->width;
	int fls_h = ((TextureData *)(res_handle_fls->extra))->height;

	auto *tex2d_bg = g_rhi->RHICreateTexture2D(bg_w, bg_h, res_handle_background->ptr);
	auto *tex2d_c1 = g_rhi->RHICreateTexture2D(c1_w, c1_h, res_handle_c1->ptr, 0, 0, 0, 1);
	auto *tex2d_c2 = g_rhi->RHICreateTexture2D(c2_w, c2_h, res_handle_c2->ptr);
	auto *tex2d_c3 = g_rhi->RHICreateTexture2D(fls_w, fls_h, res_handle_fls->ptr);


	//avator
	WIPSpriteCreator ctor_c1(3.6f*0.5, 3.6f, WIPMaterialType::E_TRANSLUCENT);
	ctor_c1.texture = tex2d_c1;
	ctor_c1.world_render = world_renderer;
	ctor_c1.body_tp = WIPCollider::_CollisionTypes::E_RIGIDBODY;
	ctor_c1.collider_sx = 0.5f;
	ctor_c1.collider_sy = 0.2f;
	auto* man_c1 = WIPSpriteFactory::create_sprite(ctor_c1);
	man_c1->_animation->add_clip(clip_down, clip_down->name);
	man_c1->_animation->add_clip(clip_left, clip_left->name);
	man_c1->_animation->add_clip(clip_right, clip_right->name);
	man_c1->_animation->add_clip(clip_up, clip_up->name);
	man_c1->_animation->add_clip(clip_s_down, clip_s_down->name);
	man_c1->_animation->add_clip(clip_s_left, clip_s_left->name);
	man_c1->_animation->add_clip(clip_s_right, clip_s_right->name);
	man_c1->_animation->add_clip(clip_s_up, clip_s_up->name);
	man_c1->_animation->play(clip_s_down);
	man_c1->set_anchor(0.5f, 0.05f);
	man_c1->set_tag("man");
	man_c1->set_type_tag("character");
	scene->load_sprite(man_c1);
	man_c1->translate_to(postion.x, postion.y);
	man_c1->set_z_order(0.4f);
	man_c1->add_tick_component(
		(CharacterPlayerControll*)WIPObject::create_tick_component("CharacterPlayerControll", man_c1)
	);
	WIPSprite* man = man_c1;


	WIPSpriteCreator ctor_bg(40.f, 40.f*((float)bg_h / bg_w), WIPMaterialType::E_TRANSLUCENT);
	ctor_bg.texture = tex2d_bg;
	ctor_bg.world_render = world_renderer;
	ctor_bg.body_tp = WIPCollider::_CollisionTypes::E_NO_PHYSICS;
	auto* bg = WIPSpriteFactory::create_sprite(ctor_bg);
	MapComponent* mc = (MapComponent*)WIPObject::create_tick_component("MapComponent", bg);
	mc->mask_path = "./huangdi.mask";
	bg->add_tick_component(mc);
	bg->set_tag("bg");
	bg->translate_to(0.f, 0.f);
	bg->set_z_order(0.9f);
	scene->load_sprite(bg);

	auto res_handle1fog = g_res_manager->load_resource("./pic/fog.png", WIPResourceType::TEXTURE);
	int ww1fog = ((TextureData *)(res_handle1fog->extra))->width;
	int hh1fog = ((TextureData *)(res_handle1fog->extra))->height;
	auto *tex2d_fog = g_rhi->RHICreateTexture2D(ww1fog, hh1fog, res_handle1fog->ptr);
	WIPSpriteCreator ctor_fog(20.f, 20.f, WIPMaterialType::E_TRANSLUCENT);
	ctor_fog.texture = tex2d_fog;
	ctor_fog.world_render = world_renderer;
	ctor_fog.body_tp = WIPCollider::_CollisionTypes::E_NO_PHYSICS;
	auto* fogs = WIPSpriteFactory::create_sprite(ctor_fog);
	fogs->set_tag("fog");
	scene->load_sprite(fogs);
	fogs->set_type_tag("scene");
	fogs->translate_to(RBMath::get_rand_range_f(scene->world_size_x, scene->world_size_y), RBMath::get_rand_range_f(scene->world_size_x, scene->world_size_y));
	fogs->set_z_order(0.05f);

	WIPSprite* woman;
	{
		WIPSpriteCreator ctor_c1(3.6f*0.5, 3.6f, WIPMaterialType::E_TRANSLUCENT);
		ctor_c1.texture = tex2d_c2;
		ctor_c1.world_render = world_renderer;
		ctor_c1.body_tp = WIPCollider::_CollisionTypes::E_STATIC_RIGIDBODY;
		ctor_c1.collider_sx = 0.5f;
		ctor_c1.collider_sy = 0.2f;
		auto* man_c1 = WIPSpriteFactory::create_sprite(ctor_c1);
		man_c1->_animation->add_clip(clip_down, clip_down->name);
		man_c1->_animation->add_clip(clip_left, clip_left->name);
		man_c1->_animation->add_clip(clip_right, clip_right->name);
		man_c1->_animation->add_clip(clip_up, clip_up->name);
		man_c1->_animation->add_clip(clip_s_down, clip_s_down->name);
		man_c1->_animation->add_clip(clip_s_left, clip_s_left->name);
		man_c1->_animation->add_clip(clip_s_right, clip_s_right->name);
		man_c1->_animation->add_clip(clip_s_up, clip_s_up->name);
		man_c1->_animation->play(clip_s_down);
		man_c1->set_anchor(0.5f, 0.05f);
		man_c1->set_tag("npc1");
		man_c1->set_type_tag("character");
		scene->load_sprite(man_c1);
		man_c1->translate_to(5, -1.5);
		man_c1->set_z_order(0.4f);
		woman = man_c1;
		woman->add_tick_component(
			(CharacterAIControll*)WIPObject::create_tick_component("CharacterAIControll", woman)
		);

		EventComponent* tc1 = (EventComponent*)WIPObject::create_tick_component("EventComponent", man_c1);

		auto* data = new NPCTalkParam();
		auto* npcdata = new NPCDisplayData();

		ActionSet* as = new ActionSet();
		Actions* evt = new Actions();
		evt->loop = true;
		evt->put_action(new ChangeCharracterAIControllState(woman, false));
		//evt->put_action(new ChangeObjectCallbackState(woman, CALLBACKTYPE::PLAY_UPDATE, false));
		evt->put_action(new WaitTriggerPushKey());
		
		evt->put_action(new TalkAc(L"年轻人，你是不是一直在这里走不出去?", npcdata, mc, tc1));
		evt->put_action(new TalkAc(L"你是不是会莫名其妙地被挡住去路？", npcdata, mc, tc1));
		evt->put_action(new TalkAc(L"你怕是碰见鬼打墙了...", npcdata, mc, tc1));
		
		evt->put_action(new ChangeCharracterAIControllState(woman, true));
		//evt->put_action(new CombineAc2(new ChangeGameState(mc, GameState::E_PLAYER_CONTROLL),new ChangeObjectCallbackState(woman, CALLBACKTYPE::PLAY_UPDATE, true)));
		evt->put_action(new ChangeGameState(mc, GameState::E_PLAYER_CONTROLL));
		
		//evt->put_action(new ChangeObjectCallbackState(woman, CALLBACKTYPE::PLAY_UPDATE, true));
		as->acss.push_back(evt);

		tc1->add_event_varible("t", Game_Varible(0.f));
		tc1->add_event_varible("dx", Game_Varible(1.f));
		tc1->add_event_varible("dy", Game_Varible(0.f));



		tc1->call_data[BEGIN_EVENT] = as;
		tc1->func_begin = [](void* da, const WIPSprite* s, TransformComponent* t)
		{
			EventComponent* tt = (EventComponent*)t;
			tt->set_update(false);
			ActionSet* data = (ActionSet*)da;
			{
				g_action_runner->ready_run_action(data->acss[0]);
			}
		};

		tc1->call_data[CONTACT_EVENT] = as;
		tc1->func_contact = [](void* data1, const WIPSprite* s, float dt, TransformComponent* t)->void
		{
#if 0
			ActionSet* data = (ActionSet*)data1;
			MapComponent* map_component = t->map_component;
			{
				{
					g_action_runner->run_action(data->acss[0], dt);
				}

			}
			g_input_manager->restore_eat();
#endif
		};

		tc1->call_data[END_EVENT] = as;
		tc1->func_end = [](void* da, const WIPSprite* s, TransformComponent* t)
		{
			g_action_runner->end_run_action();
			EventComponent* tt = (EventComponent*)t;
			tt->set_update(true);
		};

		tc1->call_data[UPDATE_EVENT] = as;
		tc1->func_update = [](void* da, float dt, TransformComponent* t)
		{
			ActionSet* data = (ActionSet*)da;
			MapComponent* map_component = t->map_component;
			{
				{
					g_action_runner->run_action(data->acss[0], dt);
				}

			}
			g_input_manager->restore_eat();
#if 0
			//npc update event 
			///!!todo:bound motion range
			///!!todo:bound by level block
			WIPSprite* sp = t->host_object;

			float& st = t->event_varible["t"].number.real;
			float& sx = t->event_varible["dx"].number.real;
			float& sy = t->event_varible["dy"].number.real;
			st += dt;
			if (st > 1.523f)
			{
				st = 0.f;
				int i = RBMath::get_rand_i(4);
				switch (i)
				{
				case 0:
					sx = 1.f; sy = 0.f;
					sp->_animation->play_name("walk_left",true);
					break;
				case 1:
					sx = 0.f; sy = 1.f; 
					sp->_animation->play_name("walk_up", true);
					break;
				case 2:
					sx = -1.f; sy = 0.f; 
					sp->_animation->play_name("walk_right", true);
					break;
				case 3:
					sx = 0.f; sy = -1.f; 
					sp->_animation->play_name("walk_down", true);
					break;
				default:
					break;
				}
			}
			RBVector2 speed(sx,sy);
			speed *= dt;
			sp->translate(speed.x, speed.y);
#endif
		};
		man_c1->add_tick_component(tc1);

		mc->subscribe_event(tc1, get_string_hash("npc talk"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_talk, mc));
		mc->subscribe_event(tc1, get_string_hash("player"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_player, mc));
	}
	WIPSprite* huyao;
	{
		WIPSpriteCreator ctor_c1(3.6f*0.5, 3.6f, WIPMaterialType::E_TRANSLUCENT);
		ctor_c1.texture = tex2d_c2;
		ctor_c1.world_render = world_renderer;
		ctor_c1.body_tp = WIPCollider::_CollisionTypes::E_STATIC_RIGIDBODY;
		ctor_c1.collider_sx = 0.5f;
		ctor_c1.collider_sy = 0.2f;
		auto* man_c1 = WIPSpriteFactory::create_sprite(ctor_c1);
		huyao = man_c1;
		man_c1->_animation->add_clip(clip_down, clip_down->name);
		man_c1->_animation->add_clip(clip_left, clip_left->name);
		man_c1->_animation->add_clip(clip_right, clip_right->name);
		man_c1->_animation->add_clip(clip_up, clip_up->name);
		man_c1->_animation->add_clip(clip_s_down, clip_s_down->name);
		man_c1->_animation->add_clip(clip_s_left, clip_s_left->name);
		man_c1->_animation->add_clip(clip_s_right, clip_s_right->name);
		man_c1->_animation->add_clip(clip_s_up, clip_s_up->name);
		man_c1->_animation->play(clip_s_down);
		man_c1->set_anchor(0.5f, 0.05f);
		man_c1->set_tag("npc_huyao");
		man_c1->set_type_tag("character");
		scene->load_sprite(man_c1);
		man_c1->translate_to(-18.6f, 12.4f);
		man_c1->set_z_order(0.4f);
	}

	//石碑文字
	{
		WIPSpriteCreator ctor_c1(1, 1, WIPMaterialType::E_OTHER);
		ctor_c1.texture = 0;
		ctor_c1.world_render = 0;
		ctor_c1.body_tp = WIPCollider::_CollisionTypes::E_STATIC_RIGIDBODY;
		ctor_c1.collider_sx = 1;
		ctor_c1.collider_sy = 1;
		auto* man_c1 = WIPSpriteFactory::create_sprite(ctor_c1);
		man_c1->set_tag("event");
		man_c1->set_type_tag("trigger");
		scene->load_sprite(man_c1);
		man_c1->translate_to(-13.2, 5.5);
		man_c1->set_z_order(0.4f);


		TransformComponent* tc1 = (TransformComponent*)WIPObject::create_tick_component("TransformComponent", man_c1);





		tc1->func_end = [](void* data, const WIPSprite* s, TransformComponent* t)->void
		{
			t->send_event(get_string_hash("player"));
		};
		auto* data = new NPCTalkParam();
		auto* npcdata = new NPCDisplayData();
		npcdata->word_tp = NPCDisplayData::E_TALK;
		npcdata->npc_size = RBVector3(-17.f, 8.6f, 0);

		ActionSet* as = new ActionSet();

		Actions* evt = new Actions();
		evt->loop = true;
		{
			auto* ta1 = new WaitTriggerPushKey();
			ta1->loop = true;
			evt->put_action(ta1);
		}
		{
			auto* ta1 = new TalkAc(L"一块泡在水里的墓碑...", npcdata, mc, tc1);
			ta1->loop = true;
			evt->put_action(ta1);
		}
		{
			auto* ta1 = new TalkAc(L"上书：【光绪三十年...】", npcdata, mc, tc1);
			ta1->loop = true;
			evt->put_action(ta1);
		}
		{
			auto* ta1 = new TalkAc(L"【...人之墓】", npcdata, mc, tc1);
			ta1->loop = true;
			evt->put_action(ta1);
		}
		{
			auto* ta1 = new TalkAc(L"剩下的字都看不清了...", npcdata, mc, tc1);
			ta1->loop = true;
			evt->put_action(ta1);
		}
		{
			auto* ta1 = new ChangeGameState(mc, GameState::E_PLAYER_CONTROLL);
			evt->put_action(ta1);
		}

		Actions* evt1 = new Actions();
		{
			auto* ta1 = new WaitTriggerPushKey();
			evt1->put_action(ta1);
		}
		{
			auto* ta1 = new WaitCameraStay(cam);
			evt1->put_action(ta1);
		}
		{
			auto* ta1 = new ChangeGameState(mc, GameState::E_ACTION);
			evt1->put_action(ta1);
		}
		float zoomr = cam->_zoom;
		{
			auto* ta1 = new CameraZoom(0.5f, cam, 1);
			evt1->put_action(ta1);
		}
		{
			auto* ta1 = new TalkAc(L"一块泡在水里的墓碑...", npcdata, mc, tc1);
			evt1->put_action(ta1);
		}
		{
			auto* ta1 = new TalkAc(L"上书：【光绪三十年...】", npcdata, mc, tc1);
			evt1->put_action(ta1);
		}
		
		{
			auto* ta1 = new TalkAc(L"【...人之墓】", npcdata, mc, tc1);
			evt1->put_action(ta1);
		}
		{
			auto* ta1 = new TalkAc(L"剩下的字都看不清了...", npcdata, mc, tc1);
			evt1->put_action(ta1);
		}
		{
			//说完话必须change回action模式，否则对话不会消失！
			auto* ta1 = new ChangeGameState(mc, GameState::E_ACTION);
			evt1->put_action(ta1);
		}
		{
			auto* ta1 = new Wait(2.f);
			evt1->put_action(ta1);
		}
		{
			auto* ta1 = new TalkAc(L"小哥在抓鱼吗~~ 奴家也好饿啊~", npcdata, mc, tc1);
			evt1->put_action(ta1);
		}
		{
			auto* ta1 = new ChangeGameState(mc, GameState::E_ACTION);
			evt1->put_action(ta1);
		}
		{
			auto* ta1 = new CameraMove(RBVector2(-14.25f, 10.28f), cam, 0.4f);
			evt1->put_action(ta1);
		}
		{
			auto* ta1 = new Wait(2.f);
			evt1->put_action(ta1);
		}
		{
			auto* ta1 = new TalkAc(L"小哥，奴家也好想吃鱼，帮我抓好不好？嘻嘻~", npcdata, mc, tc1);
			evt1->put_action(ta1);
		}
		{
			auto* ta1 = new ChangeGameState(mc, GameState::E_ACTION);
			evt1->put_action(ta1);
		}
		{
			auto* ta1 = new CameraZoom(zoomr, cam, 0.5f);
			evt1->put_action(ta1);
		}

		{
			auto* ta1 = new SetGameVaribleInt("event_huyao_meet", 1);
			evt1->put_action(ta1);
		}
		{
			auto* ta1 = new ChangeGameState(mc, GameState::E_PLAYER_CONTROLL);
			evt1->put_action(ta1);
		}

		as->acss.push_back(evt);
		as->acss.push_back(evt1);

		tc1->call_data[BEGIN_EVENT] = as;
		tc1->func_begin = [](void* da, const WIPSprite* s, TransformComponent* t)
		{
			ActionSet* data = (ActionSet*)da;
			if (g_game_data->game_varible["event_huyao_meet"].number.integer == 0)
			{
				g_action_runner->ready_run_action(data->acss[1]);
			}
			else
			{
				g_action_runner->ready_run_action(data->acss[0]);
			}
		};

		tc1->call_data[CONTACT_EVENT] = as;
		tc1->func_contact = [](void* data1, const WIPSprite* s, float dt, TransformComponent* t)->void
		{
			ActionSet* data = (ActionSet*)data1;
			MapComponent* map_component = t->map_component;
			{
				bool r;
				if (g_game_data->game_varible["event_huyao_meet"].number.integer == 0)
				{
					g_action_runner->run_action(data->acss[1],dt);
				}
				else
				{
					g_action_runner->run_action(data->acss[0],dt);
				}

			}
			g_input_manager->restore_eat();
		};

		tc1->func_end = [](void* da, const WIPSprite* s, TransformComponent* t)
		{
			g_action_runner->end_run_action();
		};

		man_c1->add_tick_component(tc1);

		mc->subscribe_event(tc1, get_string_hash("npc talk"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_talk, mc));
		mc->subscribe_event(tc1, get_string_hash("player"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_player, mc));
	}

	WIPSpriteCreator ctor_trs1(3.6f, 3.6f, WIPMaterialType::E_TRANSLUCENT);
	ctor_trs1.texture = tex2d_c3;
	ctor_trs1.world_render = world_renderer;
	ctor_trs1.body_tp = WIPCollider::_CollisionTypes::E_STATIC_RIGIDBODY;
	ctor_trs1.collider_sx = 0.5f;
	ctor_trs1.collider_sy = 0.2f;
	auto* man_trans1 = WIPSpriteFactory::create_sprite(ctor_trs1);
	man_trans1->_animation->add_clip(clip_down, clip_s_down->name);
	man_trans1->_animation->play_name(clip_s_down->name, true);
	man_trans1->set_anchor(0.5f, 0.05f);
	man_trans1->set_tag("trans1");
	man_trans1->set_type_tag("character");
	TransformComponent* tc1 = (TransformComponent*)WIPObject::create_tick_component("TransformComponent", man_trans1);
	//tc1->id = 1;
	//tc1->pos = RBVector2(-3, 6.5);
	tc1->call_data[2] = new MoveParam(1, RBVector2(-3.4, 12.5));
	tc1->func_contact = transform_event;
	man_trans1->add_tick_component(tc1);
	scene->load_sprite(man_trans1);
	man_trans1->translate_to(9.6, -16.6);
	man_trans1->set_z_order(0.4f);


	{
		WIPSpriteCreator ctor_trs1(3.6f, 3.6f, WIPMaterialType::E_TRANSLUCENT);
		ctor_trs1.texture = tex2d_c3;
		ctor_trs1.world_render = world_renderer;
		ctor_trs1.body_tp = WIPCollider::_CollisionTypes::E_STATIC_RIGIDBODY;
		ctor_trs1.collider_sx = 0.5f;
		ctor_trs1.collider_sy = 0.2f;
		auto* man_trans1 = WIPSpriteFactory::create_sprite(ctor_trs1);
		man_trans1->_animation->add_clip(clip_down, clip_s_down->name);
		man_trans1->_animation->play_name(clip_s_down->name, true);
		man_trans1->set_anchor(0.5f, 0.05f);
		man_trans1->set_tag("trans2");
		man_trans1->set_type_tag("character");
		TransformComponent* tc1 = (TransformComponent*)WIPObject::create_tick_component("TransformComponent", man_trans1);
		//tc1->id = 3;
		//tc1->pos = RBVector2(7.9, -14.5);
		tc1->call_data[2] = new MoveParam(3, RBVector2(7.9, -14.5));
		tc1->func_contact = transform_event;
		man_trans1->add_tick_component(tc1);
		scene->load_sprite(man_trans1);
		man_trans1->translate_to(3, 15);
		man_trans1->set_z_order(0.4f);
	}

	{


		WIPSpriteCreator ctor_trs1(3.6f, 3.6f, WIPMaterialType::E_OTHER);
		ctor_trs1.texture = 0;
		ctor_trs1.world_render = 0;
		ctor_trs1.body_tp = WIPCollider::_CollisionTypes::E_GHOST;
		ctor_trs1.collider_sx = 0.5f;
		ctor_trs1.collider_sy = 0.2f;
		auto* man_trans1 = WIPSpriteFactory::create_sprite(ctor_trs1);
		man_trans1->_animation->add_clip(clip_down, clip_s_down->name);
		man_trans1->_animation->play_name(clip_s_down->name, true);
		man_trans1->set_anchor(0.5f, 0.05f);
		man_trans1->set_tag("over_event");
		man_trans1->set_type_tag("event");
		man_trans1->_render->is_visible = false;
		EventComponent* tc1 = (EventComponent*)WIPObject::create_tick_component("EventComponent", man_trans1);

		Actions* actions = new Actions();
		actions->put_action(new ChangeObjectCallbackState(woman, CALLBACKTYPE::PLAY_UPDATE, false));
		actions->put_action(new ChangeCharracterAIControllState(woman, false));
		actions->put_action(new ChangeGameState(mc, GameState::E_ACTION));
		actions->put_action(new CombineAc2(new Moveto(man, "walk_down", 1.f, RBVector2(3.3f, 8.2f)), new MovetoPlayer(woman, "walk_up", 1.f)));

		actions->put_action(new TurnoffBGM("event:/bgm1"));
		actions->put_action(new PlayBGM("event:/grass_bgm"));
		actions->put_action(new Moveto(man, "walk_down", 1.5f, RBVector2(3.3f, 11.2f)));
		actions->put_action(new PlayBGM("event:/fly_cry"));
		actions->put_action(new Moveto(woman, "stand_up", 0.5f, RBVector2(5.f, 4.3f)));
		actions->put_action(new PlayBGM("event:/last_cry"));
		actions->put_action(new CombineAc2(new MovetoPlayer(woman, "walk_up", 8.f), new CameraZoom(cam->_zoom - 0.7f, cam, 8.5f)));
		actions->put_action(new ShowTexture(mc));
		actions->put_action(new ChangeCharracterAIControllState(woman, true));
		actions->put_action(new ChangeObjectCallbackState(woman, CALLBACKTYPE::PLAY_UPDATE, true));
		actions->put_action( new ChangeGameState(mc, GameState::E_PLAYER_CONTROLL));
		
		tc1->call_data[LEVEL_START] = actions;
		tc1->func_level_start = [](void* da, TransformComponent* t)->void
		{
			Actions* data = (Actions*)da;
			if (t->map_component->game_state == GameState::E_ACTION) return;
			if (g_game_data->game_varible["already pass"].number.integer == 1)
			{
				g_action_runner->ready_run_action(data);
			}
		};

		tc1->call_data[UPDATE_EVENT] = actions;
		tc1->func_update = [](void* data1, float dt, TransformComponent* t)->void
		{
			Actions* data = (Actions*)data1;
			MapComponent* map_component = t->map_component;
			{
				if (g_game_data->game_varible["already pass"].number.integer == 1)
				{
					if (g_action_runner->run_action(data, dt))
					{

						//dangerous op!
						t->map_component->game_state = GameState::E_END;
					}
				}

			}
			g_input_manager->restore_eat();
		};

		man_trans1->add_tick_component(tc1);
		scene->load_sprite(man_trans1);
		man_trans1->translate_to(0, 0.32);
		man_trans1->set_z_order(0.4f);
	}
}
void FDLevelLoader::load_mudi(const RBVector2& postion)
{
	scene->set_level_unload();
	scene->set_level_load();
	WIPCamera* cam = WIPScene::create_camera(20.f, 20.f, 0,0,g_app->window_w, g_app->window_h, g_app->window_w, g_app->window_h);
	cam->set_name("MainCam");
	cam->move_to(postion.x - 0.3f, postion.y - 0.3f);
	g_temp_uisys->change_camera(cam);
	g_physics_manager->set_debug_camera(cam);
	scene->load_camera(cam);
	WorldRender* world_renderer = game->world_renderer;
	auto *clip_down = WIPAnimationClip::create_with_atlas("walk_down", "./pic/fd/fd_clip_0.clip");
	auto *clip_left = WIPAnimationClip::create_with_atlas("walk_left", "./pic/fd/fd_clip_1.clip");
	auto *clip_right = WIPAnimationClip::create_with_atlas("walk_right", "./pic/fd/fd_clip_2.clip");
	auto *clip_up = WIPAnimationClip::create_with_atlas("walk_up", "./pic/fd/fd_clip_3.clip");
	auto *clip_s_down = WIPAnimationClip::create_with_atlas("stand_down", "./pic/fd/fd_clip_0_s.clip");
	auto *clip_s_left = WIPAnimationClip::create_with_atlas("stand_left", "./pic/fd/fd_clip_1_s.clip");
	auto *clip_s_right = WIPAnimationClip::create_with_atlas("stand_right", "./pic/fd/fd_clip_2_s.clip");
	auto *clip_s_up = WIPAnimationClip::create_with_atlas("stand_up", "./pic/fd/fd_clip_3_s.clip");

	auto res_handle_background = g_res_manager->load_resource("./pic/fd/mudian.jpg", WIPResourceType::TEXTURE);
	int bg_w = ((TextureData *)(res_handle_background->extra))->width;
	int bg_h = ((TextureData *)(res_handle_background->extra))->height;


	auto res_handle_c1 = g_res_manager->load_resource("./pic/fd/c1.png", WIPResourceType::TEXTURE);
	int c1_w = ((TextureData *)(res_handle_c1->extra))->width;
	int c1_h = ((TextureData *)(res_handle_c1->extra))->height;

	auto res_handle_c2 = g_res_manager->load_resource("./pic/fd/c2.png", WIPResourceType::TEXTURE);
	int c2_w = ((TextureData *)(res_handle_c2->extra))->width;
	int c2_h = ((TextureData *)(res_handle_c2->extra))->height;

	auto res_handle_fls = g_res_manager->load_resource("./pic/fd/flash2.png", WIPResourceType::TEXTURE);
	int fls_w = ((TextureData *)(res_handle_fls->extra))->width;
	int fls_h = ((TextureData *)(res_handle_fls->extra))->height;

	auto *tex2d_bg = g_rhi->RHICreateTexture2D(bg_w, bg_h, res_handle_background->ptr);
	auto *tex2d_c1 = g_rhi->RHICreateTexture2D(c1_w, c1_h, res_handle_c1->ptr, 0, 0, 0, 1);
	auto *tex2d_c2 = g_rhi->RHICreateTexture2D(c2_w, c2_h, res_handle_c2->ptr);
	auto *tex2d_c3 = g_rhi->RHICreateTexture2D(fls_w, fls_h, res_handle_fls->ptr);


	//avator
	WIPSpriteCreator ctor_c1(3.6f*0.5, 3.6f, WIPMaterialType::E_TRANSLUCENT);
	ctor_c1.texture = tex2d_c1;
	ctor_c1.world_render = world_renderer;
	ctor_c1.body_tp = WIPCollider::_CollisionTypes::E_RIGIDBODY;
	ctor_c1.collider_sx = 0.5f;
	ctor_c1.collider_sy = 0.2f;
	auto* man_c1 = WIPSpriteFactory::create_sprite(ctor_c1);
	man_c1->_animation->add_clip(clip_down, clip_down->name);
	man_c1->_animation->add_clip(clip_left, clip_left->name);
	man_c1->_animation->add_clip(clip_right, clip_right->name);
	man_c1->_animation->add_clip(clip_up, clip_up->name);
	man_c1->_animation->add_clip(clip_s_down, clip_s_down->name);
	man_c1->_animation->add_clip(clip_s_left, clip_s_left->name);
	man_c1->_animation->add_clip(clip_s_right, clip_s_right->name);
	man_c1->_animation->add_clip(clip_s_up, clip_s_up->name);
	man_c1->_animation->play(clip_s_down);
	man_c1->set_anchor(0.5f, 0.05f);
	man_c1->set_tag("man");
	man_c1->set_type_tag("character");
	scene->load_sprite(man_c1);
	man_c1->translate_to(postion.x, postion.y);
	man_c1->set_z_order(0.4f);
	man_c1->add_tick_component(
		(CharacterPlayerControll*)WIPObject::create_tick_component("CharacterPlayerControll", man_c1)
	);


	WIPSpriteCreator ctor_bg(40.f, 40.f*((float)bg_h / bg_w), WIPMaterialType::E_TRANSLUCENT);
	ctor_bg.texture = tex2d_bg;
	ctor_bg.world_render = world_renderer;
	ctor_bg.body_tp = WIPCollider::_CollisionTypes::E_NO_PHYSICS;
	auto* bg = WIPSpriteFactory::create_sprite(ctor_bg);
	MapComponent* mc = (MapComponent*)WIPObject::create_tick_component("MapComponent", bg);
	mc->mask_path = "./mudian.mask";
	bg->add_tick_component(mc);
	bg->set_tag("bg");
	bg->translate_to(0.f, 0.f);
	bg->set_z_order(0.9f);
	scene->load_sprite(bg);

	auto res_handle1fog = g_res_manager->load_resource("./pic/fog.png", WIPResourceType::TEXTURE);
	int ww1fog = ((TextureData *)(res_handle1fog->extra))->width;
	int hh1fog = ((TextureData *)(res_handle1fog->extra))->height;
	auto *tex2d_fog = g_rhi->RHICreateTexture2D(ww1fog, hh1fog, res_handle1fog->ptr);
	WIPSpriteCreator ctor_fog(20.f, 20.f, WIPMaterialType::E_TRANSLUCENT);
	ctor_fog.texture = tex2d_fog;
	ctor_fog.world_render = world_renderer;
	ctor_fog.body_tp = WIPCollider::_CollisionTypes::E_NO_PHYSICS;
	auto* fogs = WIPSpriteFactory::create_sprite(ctor_fog);
	fogs->set_tag("fog");
	scene->load_sprite(fogs);
	fogs->set_type_tag("scene");
	fogs->translate_to(RBMath::get_rand_range_f(scene->world_size_x, scene->world_size_y), RBMath::get_rand_range_f(scene->world_size_x, scene->world_size_y));
	fogs->set_z_order(0.05f);

	{
		WIPSpriteCreator ctor_trs1(3.6f, 3.6f, WIPMaterialType::E_TRANSLUCENT);
		ctor_trs1.texture = tex2d_c3;
		ctor_trs1.world_render = world_renderer;
		ctor_trs1.body_tp = WIPCollider::_CollisionTypes::E_RIGIDBODY;
		ctor_trs1.collider_sx = 0.5f;
		ctor_trs1.collider_sy = 0.2f;
		auto* man_trans1 = WIPSpriteFactory::create_sprite(ctor_trs1);
		man_trans1->_animation->add_clip(clip_down, clip_s_down->name);
		man_trans1->_animation->play_name(clip_s_down->name, true);
		man_trans1->set_anchor(0.5f, 0.05f);
		man_trans1->set_tag("trans2");
		man_trans1->set_type_tag("character");
		TransformComponent* tc1 = (TransformComponent*)WIPObject::create_tick_component("TransformComponent", man_trans1);
		//tc1->id = 2;
		//tc1->pos = RBVector2(2.9, 13.3);
		tc1->call_data[2] = new MoveParam(2, RBVector2(2.9, 13.3));
		tc1->func_contact = transform_event;
		man_trans1->add_tick_component(tc1);
		scene->load_sprite(man_trans1);
		man_trans1->translate_to(10, -16);
		man_trans1->set_z_order(0.4f);
	}

	{
		WIPSpriteCreator ctor_trs1(3.6f, 3.6f, WIPMaterialType::E_TRANSLUCENT);
		ctor_trs1.texture = tex2d_c3;
		ctor_trs1.world_render = world_renderer;
		ctor_trs1.body_tp = WIPCollider::_CollisionTypes::E_STATIC_RIGIDBODY;
		ctor_trs1.collider_sx = 0.5f;
		ctor_trs1.collider_sy = 0.2f;
		auto* man_trans1 = WIPSpriteFactory::create_sprite(ctor_trs1);
		man_trans1->_animation->add_clip(clip_down, clip_s_down->name);
		man_trans1->_animation->play_name(clip_s_down->name, true);
		man_trans1->set_anchor(0.5f, 0.05f);
		man_trans1->set_tag("pass_event");
		man_trans1->set_type_tag("character");
		TransformComponent* tc1 = (TransformComponent*)WIPObject::create_tick_component("TransformComponent", man_trans1);
		tc1->func_contact = [](void* data, const WIPSprite* s, float dt, TransformComponent* t)->void
		{
			if (Input::get_sys_key_up(WIP_SPACE))
				g_game_data->game_varible["already pass"] = Game_Varible(1);
		};
		man_trans1->add_tick_component(tc1);
		scene->load_sprite(man_trans1);
		man_trans1->translate_to(4, 9.32);
		man_trans1->set_z_order(0.4f);
		NPCComponent* npcc = (NPCComponent*)WIPObject::create_tick_component("NPCComponent", man_trans1);
		npcc->words[0].push(L"【闻犬而终，包藏祸心】......");
		npcc->words[0].push(L"......");
		npcc->words[0].push(L"这写的都是什么东西...");
		npcc->words[0].push(L"我怎么走到这个地方来了...");
		npcc->words[0].push(L"还是赶紧离开吧...");


		man_trans1->add_tick_component(npcc);

		mc->subscribe_event(npcc, get_string_hash("npc talk"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_talk, mc));
		mc->subscribe_event(npcc, get_string_hash("player"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_player, mc));
	}
}

#include "GameComponent.h"

void FDLevelLoader::init_game()
{
	g_game_data->game_varible["already pass"] = Game_Varible(0);
	g_game_data->game_varible["title"] = Game_Varible(1);
	g_game_data->game_varible["know cannot pass"] = Game_Varible(0);
	g_game_data->game_varible["step_in"] = Game_Varible(0);
	g_game_data->game_varible["event_huyao_meet"] = Game_Varible(0);

}

