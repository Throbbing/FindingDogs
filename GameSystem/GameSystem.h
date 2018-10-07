class BaseGame
{
public:
	virtual void init() = 0;
	virtual void register_game_event(){}
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void input_proc() = 0;

};

class FindingDogGame
{
public:
	virtual void init() = 0;
	virtual void register_game_event() {}
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void input_proc() = 0;
};


class GameSystem
{
public:
	virtual void init() {}
	virtual void release() {}
	virtual void update() {}
};