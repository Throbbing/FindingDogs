#pragma once
#include "Object.h"


class WIPSprite;
class WIPCamera;



class EditorResource
{

};

class EditorObjectBase : public WIPObject
{
public:
	WIPOBJECT(EditorObjectBase, WIPObject);
private:

};

class EditorWrapObject:public EditorObjectBase
{
public:
	WIPOBJECT(EditorWrapObject, EditorObjectBase);
	virtual void update(f32 dt);
	virtual void update_ui(f32 dt);
	virtual void on_output();
private:

};

class CameraWrapObject :public EditorWrapObject
{
public:
	WIPOBJECT(CameraWrapObject, EditorWrapObject);

	WIPCamera* ref;
};

class SpriteWrapObject : public EditorWrapObject
{
public:
	WIPOBJECT(SpriteWrapObject, EditorWrapObject);

	WIPSprite* ref;
};

class EditorUI:public EditorObjectBase
{
public:
	WIPOBJECT(EditorUI, EditorObjectBase);
private:

};

#include <vector>

class EditorScene
{
public:
	std::vector<EditorObjectBase*> objects;
};