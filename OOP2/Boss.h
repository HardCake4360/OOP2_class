#pragma once
#include "Enemy.h"
class Boss :
    public Enemy
{
	int current_pattern;
	int n_remaining_frames_for_current_pattern;

	void move_toward_player();

public:
	Boss(const char* shape_in_normal, const char* shape_on_hit, int max_frames_crying_on_hit, int pos) :
		Enemy(shape_in_normal, shape_on_hit, max_frames_crying_on_hit, pos),
		current_pattern(),
		n_remaining_frames_for_current_pattern(0)
	{
		set_hp(51.0f);
	}

	~Boss() {}

	void	update(const Screen* screen) override;


};

