#include "LevelLoader.h"
#include "PhysicsManager.h"
#include "FDGameComponent.h"
#include "GameApp.h"
#include "Input.h"
#include "InputManager.h"
#include "GameAction.h"

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
	WIPCamera* cam = WIPScene::create_camera(20.f, 20.f, game->window_w, game->window_h, game->window_w, game->window_h);
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
	WIPCamera* cam = WIPScene::create_camera(20.f, 20.f, game->window_w, game->window_h, game->window_w, game->window_h);
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
		evt->put_action(new WaitTrigger());

		evt->put_action(new TalkAc(L"老夫光绪三十年来此，年生不好啊...", npcdata, mc, tc1));
		evt->put_action(new TalkAc(L"什么东西都卖不出去，回去的路也找不到了......", npcdata, mc, tc1));
		evt->put_action(new TalkAc(L"今天来一个人吃了一天了...", npcdata, mc, tc1));
		evt->put_action(new TalkAc(L"......", npcdata, mc, tc1));
		evt->put_action(new TalkAc(L"年轻人你这么匆忙，要去哪儿呀？", npcdata, mc, tc1));
		evt->put_action(new ChangeGameState(mc,GameState::E_PLAYER_CONTROLL));
		Actions* evt1 = new Actions();
		evt1->loop = true;
		evt1->put_action(new WaitTrigger());

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
		evt->put_action(new WaitTrigger());
		evt->put_action(new TalkAc(L"年轻人，你是不是一直在这里走不出去?", npcdata, mc, tc1));
		evt->put_action(new TalkAc(L"你是不是会莫名其妙地被挡住去路？", npcdata, mc, tc1));
		evt->put_action(new TalkAc(L"你怕是碰见鬼打墙了...", npcdata, mc, tc1));
		evt->put_action(new ChangeGameState(mc,GameState::E_PLAYER_CONTROLL));

		Actions* evt1 = new Actions();
		evt1->loop = true;
		evt1->put_action(new WaitTrigger());
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
		tc1->func_contact_1 = [as](void* data1, const WIPSprite* s, float dt, TransformComponent* t)->void
		{
			ActionSet* data = as;
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
	WIPCamera* cam = WIPScene::create_camera(20.f, 20.f, g_app->window_w, g_app->window_h, g_app->window_w, g_app->window_h);
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

		EventComponent* tc1 = (EventComponent*)WIPObject::create_tick_component("EventComponent", man_c1);

		auto* data = new NPCTalkParam();
		auto* npcdata = new NPCDisplayData();

		ActionSet* as = new ActionSet();
		Actions* evt = new Actions();
		evt->loop = true;
		evt->put_action(new WaitTrigger());
		evt->put_action(new TalkAc(L"年轻人，你是不是一直在这里走不出去?", npcdata, mc, tc1));
		evt->put_action(new TalkAc(L"你是不是会莫名其妙地被挡住去路？", npcdata, mc, tc1));
		evt->put_action(new TalkAc(L"你怕是碰见鬼打墙了...", npcdata, mc, tc1));
		evt->put_action(new ChangeGameState(mc, GameState::E_PLAYER_CONTROLL));
		as->acss.push_back(evt);

		tc1->add_event_varible("t", Game_Varible(0.f));
		tc1->add_event_varible("dx", Game_Varible(1.f));
		tc1->add_event_varible("dy", Game_Varible(0.f));



		tc1->call_data[BEGIN_EVENT] = as;
		tc1->func_begin = [](void* da, const WIPSprite* s, TransformComponent* t)
		{
			ActionSet* data = (ActionSet*)da;
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
				{
					g_action_runner->run_action(data->acss[0], dt);
				}

			}
			g_input_manager->restore_eat();
		};

		tc1->func_update = [](void* da, float dt, TransformComponent* t)
		{
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
			auto* ta1 = new WaitTrigger();
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
			auto* ta1 = new WaitTrigger();
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
		TransformComponent* tc1 = (TransformComponent*)WIPObject::create_tick_component("TransformComponent", man_trans1);

		Actions* actions = new Actions();

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
	WIPCamera* cam = WIPScene::create_camera(20.f, 20.f, g_app->window_w, g_app->window_h, g_app->window_w, g_app->window_h);
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

void FDLevelLoader::test_load_level()
{
	//scene->reset_level_load_state();
	scene->set_level_load();
	WIPCamera* cam = WIPScene::create_camera(20.f, 20.f, g_app->window_w, g_app->window_h, g_app->window_w, g_app->window_h);
	cam->set_name("MainCam");
	cam->move_to(5.f, 5.f);
	g_temp_uisys->change_camera(cam);
	g_physics_manager->set_debug_camera(cam);
	scene->load_camera(cam);
	WorldRender* world_renderer = game->world_renderer;

	//load resource
	auto *clip = WIPAnimationClip::create_with_atlas("walk_down", "./clips/1.clip");
	auto *clip1 = WIPAnimationClip::create_with_atlas("walk_left", "./clips/2.clip");
	auto *clip2 = WIPAnimationClip::create_with_atlas("walk_right", "./clips/3.clip");
	auto *clip3 = WIPAnimationClip::create_with_atlas("walk_up", "./clips/4.clip");
	auto *clip_s = WIPAnimationClip::create_with_atlas("stand_down", "./clips/1s.clip");
	auto *clip1_s = WIPAnimationClip::create_with_atlas("stand_left", "./clips/2s.clip");
	auto *clip2_s = WIPAnimationClip::create_with_atlas("stand_right", "./clips/3s.clip");
	auto *clip3_s = WIPAnimationClip::create_with_atlas("stand_up", "./clips/4s.clip");

	auto res_handle1 = g_res_manager->load_resource("./pic/zhaolinger_1_8.png", WIPResourceType::TEXTURE);
	int ww = ((TextureData *)(res_handle1->extra))->width;
	int hh = ((TextureData *)(res_handle1->extra))->height;
	auto res_handle2 = g_res_manager->load_resource("./pic/xianling_6.jpg", WIPResourceType::TEXTURE);
	int ww1 = ((TextureData *)(res_handle2->extra))->width;
	int hh1 = ((TextureData *)(res_handle2->extra))->height;
	auto res_handle1mask = g_res_manager->load_resource("./pic/xianling_6_2.png", WIPResourceType::TEXTURE);
	int ww1mask = ((TextureData *)(res_handle1mask->extra))->width;
	int hh1mask = ((TextureData *)(res_handle1mask->extra))->height;
	auto res_handle1fog = g_res_manager->load_resource("./pic/fog.png", WIPResourceType::TEXTURE);
	int ww1fog = ((TextureData *)(res_handle1fog->extra))->width;
	int hh1fog = ((TextureData *)(res_handle1fog->extra))->height;

	float rot = ww / (float)hh;



	auto res_lixiaoyao = g_res_manager->load_resource("./pic/lixiaoyao_orijan.png", WIPResourceType::TEXTURE);
	int wli = ((TextureData *)(res_lixiaoyao->extra))->width;
	int hli = ((TextureData *)(res_lixiaoyao->extra))->height;
	auto res_zaji1 = g_res_manager->load_resource("./pic/suzhou_people.png", WIPResourceType::TEXTURE);
	int wzaji1 = ((TextureData *)(res_zaji1->extra))->width;
	int hzaji1 = ((TextureData *)(res_zaji1->extra))->height;
	auto res_zaji2 = g_res_manager->load_resource("./pic/suzhou_people2.png", WIPResourceType::TEXTURE);
	int wzaji2 = ((TextureData *)(res_zaji2->extra))->width;
	int hzaji2 = ((TextureData *)(res_zaji2->extra))->height;
	auto res_crowd = g_res_manager->load_resource("./pic/crowd.png", WIPResourceType::TEXTURE);
	int wcrow = ((TextureData *)(res_crowd->extra))->width;
	int hcrow = ((TextureData *)(res_crowd->extra))->height;

	float rotli = wli / (float)hli;

	auto *tex2d = g_rhi->RHICreateTexture2D(ww, hh, res_handle1->ptr);
	auto *tex2d1 = g_rhi->RHICreateTexture2D(ww1, hh1, res_handle2->ptr);
	//issue:texture boarder
	auto *tex2d1mask = g_rhi->RHICreateTexture2D(ww1, hh1, res_handle1mask->ptr, 0, 0, 0, 1);

	auto *tex2d_fog = g_rhi->RHICreateTexture2D(ww1fog, hh1fog, res_handle1fog->ptr);

	auto *tex2d_lixiaoyao = g_rhi->RHICreateTexture2D(wli, hli, res_lixiaoyao->ptr);
	auto *tex2d_zaji1 = g_rhi->RHICreateTexture2D(wzaji1, hzaji1, res_zaji1->ptr);
	auto *tex2d_zaji2 = g_rhi->RHICreateTexture2D(wzaji2, hzaji2, res_zaji2->ptr);
	auto *tex2d_crowd = g_rhi->RHICreateTexture2D(wcrow, hcrow, res_crowd->ptr);

	auto res_face = g_res_manager->load_resource("./pic/face.png", WIPResourceType::TEXTURE);
	int fw = ((TextureData *)(res_face->extra))->width;
	int fh = ((TextureData *)(res_face->extra))->height;
	auto *face = g_rhi->RHICreateTexture2D(fw, fh, res_face->ptr);

	auto res_face_miaoren = g_res_manager->load_resource("./pic/miaoren.png", WIPResourceType::TEXTURE);
	fw = ((TextureData *)(res_face_miaoren->extra))->width;
	fh = ((TextureData *)(res_face_miaoren->extra))->height;
	WIPTexture2D* face_miaoren = g_rhi->RHICreateTexture2D(fw, fh, res_face_miaoren->ptr);

	auto res_face_251 = g_res_manager->load_resource("./pic/25-1.png", WIPResourceType::TEXTURE);
	fw = ((TextureData *)(res_face_251->extra))->width;
	fh = ((TextureData *)(res_face_251->extra))->height;
	WIPTexture2D* face_25_1 = g_rhi->RHICreateTexture2D(fw, fh, res_face_251->ptr);


	//create objects
	WIPSpriteCreator ctor_man(3.6f*0.5, 3.6f, WIPMaterialType::E_TRANSLUCENT);
	ctor_man.texture = tex2d;
	ctor_man.world_render = world_renderer;
	ctor_man.body_tp = WIPCollider::_CollisionTypes::E_RIGIDBODY;
	ctor_man.collider_sx = 0.5f;
	ctor_man.collider_sy = 0.2f;

	WIPSpriteCreator ctor_mask(40.f, 30.f, WIPMaterialType::E_TRANSLUCENT);
	ctor_mask.texture = tex2d1mask;
	ctor_mask.world_render = world_renderer;
	ctor_mask.body_tp = WIPCollider::_CollisionTypes::E_NO_PHYSICS;

	WIPSpriteCreator ctor_bg(40.f, 30.f, WIPMaterialType::E_TRANSLUCENT);
	ctor_bg.texture = tex2d1;
	ctor_bg.world_render = world_renderer;
	ctor_bg.body_tp = WIPCollider::_CollisionTypes::E_NO_PHYSICS;


	WIPSpriteCreator ctor_fog(20.f, 20.f, WIPMaterialType::E_TRANSLUCENT);
	ctor_fog.texture = tex2d_fog;
	ctor_fog.world_render = world_renderer;
	ctor_fog.body_tp = WIPCollider::_CollisionTypes::E_NO_PHYSICS;


	WIPSpriteCreator ctor_li(3.f*rotli, 3.5f, WIPMaterialType::E_TRANSLUCENT);
	ctor_li.texture = tex2d_lixiaoyao;
	ctor_li.world_render = world_renderer;
	//ctor_li.body_tp = WIPCollider::_CollisionTypes::E_GHOST;
	ctor_li.collider_sx = 0.5f;
	ctor_li.collider_sy = 0.2f;

	WIPSpriteCreator ctor_zaji1(1.2f*2.5f*1.2f, 3.6f*1.2f, WIPMaterialType::E_TRANSLUCENT);
	ctor_zaji1.texture = tex2d_zaji1;
	ctor_zaji1.world_render = world_renderer;
	ctor_zaji1.collider_sx = 0.5f;
	ctor_zaji1.collider_sy = 0.2f;

	WIPSpriteCreator ctor_zaji2(1.8f*1.2f, 3.4f, WIPMaterialType::E_TRANSLUCENT);
	ctor_zaji2.texture = tex2d_zaji2;
	ctor_zaji2.world_render = world_renderer;
	ctor_zaji2.collider_sx = 0.5f;
	ctor_zaji2.collider_sy = 0.2f;

	WIPSpriteCreator ctor_crowd(6 * 1.2f, 8.f, WIPMaterialType::E_TRANSLUCENT);
	ctor_crowd.texture = tex2d_crowd;
	ctor_crowd.world_render = world_renderer;
	ctor_crowd.collider_sx = 0.85f;
	ctor_crowd.collider_sy = 0.4f;



	auto *man_lixiaoyao = WIPSpriteFactory::create_sprite(ctor_li);
	man_lixiaoyao->_animation->add_clip(clip, clip->name);
	man_lixiaoyao->_animation->add_clip(clip1, clip1->name);
	man_lixiaoyao->_animation->add_clip(clip2, clip2->name);
	man_lixiaoyao->_animation->add_clip(clip3, clip3->name);
	man_lixiaoyao->_animation->add_clip(clip_s, clip_s->name);
	man_lixiaoyao->_animation->add_clip(clip1_s, clip1_s->name);
	man_lixiaoyao->_animation->add_clip(clip2_s, clip2_s->name);
	man_lixiaoyao->_animation->add_clip(clip3_s, clip3_s->name);
	man_lixiaoyao->_animation->play(clip1_s);
	man_lixiaoyao->set_anchor(0.5f, 0);

	//temp
	//for load correctly, we must add some function of sealarization.
	NPCComponent* npcc = (NPCComponent*)WIPObject::create_tick_component("NPCComponent", man_lixiaoyao);
	npcc->words[0].push(L"......");
	npcc->add_faces("dft", face_miaoren);
	man_lixiaoyao->add_tick_component(npcc);

	auto *zaji1 = WIPSpriteFactory::create_sprite(ctor_zaji1);
	zaji1->_animation->add_clip(clip, clip->name);
	zaji1->_animation->set_clip_instance_speed(clip->name
		, 0.2f);
	zaji1->_animation->play(clip, true);
	zaji1->set_anchor(0.5f, 0);
	NPCComponent* npcc1 = (NPCComponent*)WIPObject::create_tick_component("NPCComponent", zaji1);
	npcc1->words[0].push(L"还是不要去打扰他们了...");
	npcc1->add_faces("dft", face);
	zaji1->add_tick_component(npcc1);

	auto *zaji2 = WIPSpriteFactory::create_sprite(ctor_zaji2);
	zaji2->_animation->add_clip(clip1_s, clip1_s->name);
	zaji2->_animation->play(clip1_s, true);
	zaji2->set_anchor(0.5f, 0);
	NPCComponent* npcc2 = (NPCComponent*)WIPObject::create_tick_component("NPCComponent", zaji2);
	npcc2->add_faces("dft", face_25_1);
	npcc2->words[0].push(L"真是可怜的孩子...");
	npcc2->words[0].push(L"想当年，南诏国大水，灵儿她娘也是这么死的...");
	npcc2->words[0].push(L"如今，想不到这种事情也会发生在灵儿身上...");
	zaji2->add_tick_component(npcc2);


	auto *crowd = WIPSpriteFactory::create_sprite(ctor_crowd);
	crowd->_animation->add_clip(clip_s, clip_s->name);
	crowd->_animation->play(clip_s);
	crowd->set_anchor(0.4f, 0.2f);
	NPCComponent* npcc3 = (NPCComponent*)WIPObject::create_tick_component("NPCComponent", crowd);
	npcc3->words[0].push(L"尔等凡人，速速退散！");
	crowd->add_tick_component(npcc3);

	auto* bg = WIPSpriteFactory::create_sprite(ctor_bg);
	MapComponent* mc = (MapComponent*)WIPObject::create_tick_component("MapComponent", bg);
	bg->add_tick_component(mc);

	auto* bg_mask = WIPSpriteFactory::create_sprite(ctor_mask);

	auto* man = WIPSpriteFactory::create_sprite(ctor_man);
	man->_animation->add_clip(clip, clip->name);
	man->_animation->add_clip(clip1, clip1->name);
	man->_animation->add_clip(clip2, clip2->name);
	man->_animation->add_clip(clip3, clip3->name);
	man->_animation->add_clip(clip_s, clip_s->name);
	man->_animation->add_clip(clip1_s, clip1_s->name);
	man->_animation->add_clip(clip2_s, clip2_s->name);
	man->_animation->add_clip(clip3_s, clip3_s->name);
	man->_animation->play(clip_s);
	man->set_anchor(0.5f, 0);

	mc->subscribe_event(npcc, get_string_hash("npc talk"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_talk, mc));
	mc->subscribe_event(npcc, get_string_hash("player"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_player, mc));
	mc->subscribe_event(npcc1, get_string_hash("npc talk"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_talk, mc));
	mc->subscribe_event(npcc1, get_string_hash("player"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_player, mc));
	mc->subscribe_event(npcc2, get_string_hash("npc talk"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_talk, mc));
	mc->subscribe_event(npcc2, get_string_hash("player"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_player, mc));
	mc->subscribe_event(npcc3, get_string_hash("npc talk"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_talk, mc));
	mc->subscribe_event(npcc3, get_string_hash("player"), WIP_EVENT_HANDLER_OUT(MapComponent, change_to_player, mc));


	bg->set_tag("bg");
	bg_mask->set_tag("mask");
	man->set_tag("man");
	man_lixiaoyao->set_tag("lixiaoyao");
	zaji1->set_tag("zaji1");
	zaji2->set_tag("zaji2");
	crowd->set_tag("crowd");


	bg->set_type_tag("scene");
	bg_mask->set_type_tag("scene");

	man->set_type_tag("character");
	man_lixiaoyao->set_type_tag("character");
	zaji1->set_type_tag("character");
	zaji2->set_type_tag("character");
	crowd->set_type_tag("character");

	scene->load_sprite(bg);
	scene->load_sprite(bg_mask);
	scene->load_sprite(man);
	scene->load_sprite(man_lixiaoyao);
	scene->load_sprite(zaji1);
	scene->load_sprite(zaji2);
	scene->load_sprite(crowd);

	man_lixiaoyao->set_z_order(0.4f);
	zaji1->set_z_order(0.4f);
	zaji2->set_z_order(0.4f);
	crowd->set_z_order(0.4f);
	std::vector<const WIPSprite* > sp;
	scene->quad_tree->get_all_nodes(sp);
	sp.clear();

	man_lixiaoyao->translate_to(-3, 1);
	scene->quad_tree->get_all_nodes(sp);
	sp.clear();
	zaji1->translate_to(-5, 0);
	scene->quad_tree->get_all_nodes(sp);
	sp.clear();
	zaji2->translate_to(-4, -2);
	scene->quad_tree->get_all_nodes(sp);
	sp.clear();
	crowd->translate_to(-8, 3);
	scene->quad_tree->get_all_nodes(sp);
	sp.clear();




	auto* fogs = WIPSpriteFactory::create_sprite(ctor_fog);
	fogs->set_tag("fog");
	scene->load_sprite(fogs);
	fogs->set_type_tag("scene");
	fogs->translate_to(0.f, 0.f);
	fogs->set_z_order(0.05f);



	bg->translate_to(0.f, 0.f);
	bg_mask->translate_to(0.f, 0.f);
	man->translate_to(8.f, 1.f);
	bg->set_z_order(0.9f);
	man->set_z_order(0.4f);
	bg_mask->set_z_order(0.1f);

}