#include "LevelLoader.h"
#include "PhysicsManager.h"
#include "FDGameComponent.h"
#include "GameApp.h"
#include "Input.h"
#include "InputManager.h"
#include "GameAction.h"
#include "CharacterComponents.h"


static WIPAnimationClip* clips[8] = { nullptr };

static void load_main_camera()
{
	int screen_padding = (g_app->window_h - g_app->window_w*9.f / 16)*0.5f;
	f32 cam_scale = 0.8f;
	WIPCamera* cam = WIPScene::create_camera(27.f*cam_scale, 18.f*cam_scale,0, screen_padding, g_app->window_w, g_app->window_h- screen_padding*2, g_app->window_w, g_app->window_h);
	cam->set_name("MainCam");
	cam->move_to(5.f, 5.f);
	g_temp_uisys->change_camera(cam);
	g_physics_manager->set_debug_camera(cam);
	g_scene->load_camera(cam);
	
}

static void load_base_clip()
{
	auto *clip = WIPAnimationClip::create_with_atlas("walk_down", "./clips/1.clip");
	auto *clip1 = WIPAnimationClip::create_with_atlas("walk_left", "./clips/2.clip");
	auto *clip2 = WIPAnimationClip::create_with_atlas("walk_right", "./clips/3.clip");
	auto *clip3 = WIPAnimationClip::create_with_atlas("walk_up", "./clips/4.clip");
	auto *clip_s = WIPAnimationClip::create_with_atlas("stand_down", "./clips/1s.clip");
	auto *clip1_s = WIPAnimationClip::create_with_atlas("stand_left", "./clips/2s.clip");
	auto *clip2_s = WIPAnimationClip::create_with_atlas("stand_right", "./clips/3s.clip");
	auto *clip3_s = WIPAnimationClip::create_with_atlas("stand_up", "./clips/4s.clip");
	clips[0] = clip;
	clips[1] = clip1;
	clips[2] = clip2;
	clips[3] = clip3;
	clips[4] = clip_s;
	clips[5] = clip1_s;
	clips[6] = clip2_s;
	clips[7] = clip3_s;

}

static WIPSprite* load_player()
{

}

static WIPSprite* load_npc_base()
{

}

static WIPSprite* load_map(WorldRender* world_renderer)
{
	auto res_handle2 = g_res_manager->load_resource("./pic/xianling_6.jpg", WIPResourceType::TEXTURE);
	int ww1 = ((TextureData *)(res_handle2->extra))->width;
	int hh1 = ((TextureData *)(res_handle2->extra))->height;
	auto res_handle1mask = g_res_manager->load_resource("./pic/xianling_6_2.png", WIPResourceType::TEXTURE);
	int ww1mask = ((TextureData *)(res_handle1mask->extra))->width;
	int hh1mask = ((TextureData *)(res_handle1mask->extra))->height;
	auto res_handle1fog = g_res_manager->load_resource("./pic/fog.png", WIPResourceType::TEXTURE);
	int ww1fog = ((TextureData *)(res_handle1fog->extra))->width;
	int hh1fog = ((TextureData *)(res_handle1fog->extra))->height;
	auto *tex2d1 = g_rhi->RHICreateTexture2D(ww1, hh1, res_handle2->ptr);
	auto *tex2d1mask = g_rhi->RHICreateTexture2D(ww1, hh1, res_handle1mask->ptr, 0, 0, 0, 1);
	auto *tex2d_fog = g_rhi->RHICreateTexture2D(ww1fog, hh1fog, res_handle1fog->ptr);
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

	auto* bg = WIPSpriteFactory::create_sprite(ctor_bg);
	auto* bg_mask = WIPSpriteFactory::create_sprite(ctor_mask);
	bg->set_tag("bg");
	bg_mask->set_tag("mask");
	bg->set_type_tag("scene");
	bg_mask->set_type_tag("scene");
	g_scene->load_sprite(bg);
	g_scene->load_sprite(bg_mask);

	auto* fogs = WIPSpriteFactory::create_sprite(ctor_fog);
	fogs->set_tag("fog");
	g_scene->load_sprite(fogs);
	fogs->set_type_tag("scene");
	fogs->translate_to(0.f, 0.f);
	fogs->set_z_order(0.05f);

	bg->translate_to(0.f, 0.f);
	bg_mask->translate_to(0.f, 0.f);
	bg->set_z_order(0.9f);
	bg_mask->set_z_order(0.1f);

	MapComponent* mc = (MapComponent*)WIPObject::create_tick_component("MapComponent", bg);
	//bg->add_tick_component(mc);

	return bg;
}

static void load_flyui()
{

}

void FDLevelLoader::test_load_level()
{
	//scene->reset_level_load_state();
	scene->set_level_load();
	load_main_camera();
	WorldRender* world_renderer = game->world_renderer;
	//load resource
	load_base_clip();

	auto* map_sprite = load_map(world_renderer);


#if 0
	auto res_handle1 = g_res_manager->load_resource("./pic/zhaolinger_1_8.png", WIPResourceType::TEXTURE);
	int ww = ((TextureData *)(res_handle1->extra))->width;
	int hh = ((TextureData *)(res_handle1->extra))->height;
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
	auto *tex2d_lixiaoyao = g_rhi->RHICreateTexture2D(wli, hli, res_lixiaoyao->ptr);
	auto *tex2d_zaji1 = g_rhi->RHICreateTexture2D(wzaji1, hzaji1, res_zaji1->ptr);
	auto *tex2d_zaji2 = g_rhi->RHICreateTexture2D(wzaji2, hzaji2, res_zaji2->ptr);
	auto *tex2d_crowd = g_rhi->RHICreateTexture2D(wcrow, hcrow, res_crowd->ptr);


	//create objects
	WIPSpriteCreator ctor_man(3.6f*0.5, 3.6f, WIPMaterialType::E_TRANSLUCENT);
	ctor_man.texture = tex2d;
	ctor_man.world_render = world_renderer;
	ctor_man.body_tp = WIPCollider::_CollisionTypes::E_RIGIDBODY;
	ctor_man.collider_sx = 0.5f;
	ctor_man.collider_sy = 0.2f;

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


	
	man->set_tag("man");
	man_lixiaoyao->set_tag("lixiaoyao");
	zaji1->set_tag("zaji1");
	zaji2->set_tag("zaji2");
	crowd->set_tag("crowd");

	

	man->set_type_tag("character");
	man_lixiaoyao->set_type_tag("character");
	zaji1->set_type_tag("character");
	zaji2->set_type_tag("character");
	crowd->set_type_tag("character");

	
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




	

	man->translate_to(8.f, 1.f);
	man->set_z_order(0.4f);
#endif

}