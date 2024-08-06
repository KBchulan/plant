#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"vector2.h"
#include"camera.h"
#include"platform.h"
#include"player_id.h"
#include"animation.h"
#include"particle.h"
#include"bullet.h"

#include<easyx.h>
#include<vector>

extern bool is_debug;

extern std::vector<Bullet*> bullet_list;
extern std::vector<Platform> platform_list;

extern Atlas atlas_run_effect;
extern Atlas atlas_jump_effect;
extern Atlas atlas_land_effect;

class Player {
public:
	Player() {
		current_animation = &animation_idle_right;

		timer_attack_cd.set_wait_time(attack_cd);
		timer_attack_cd.set_one_shot(true);
		timer_attack_cd.set_callback([&]() {
			can_attack = true;
			});

		timer_invulnerable.set_wait_time(750);
		timer_invulnerable.set_one_shot(true);
		timer_invulnerable.set_callback([&]() {
			is_invulnerable = false;
			});

		timer_invulnerable_blink.set_wait_time(75);
		timer_invulnerable_blink.set_callback([&]() {
			is_showing_sketch_frame = !is_showing_sketch_frame;
			});

		timer_run_effect_generation.set_wait_time(75);
		timer_run_effect_generation.set_callback([&]() {
			Vector2 particle_position;
			IMAGE* frame = atlas_run_effect.get_image(0);
			particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
			particle_position.y = position.y + size.y - frame->getheight();
			particle_list.emplace_back(particle_position, &atlas_run_effect, 45);
			});
		
		timer_die_effect_generation.set_wait_time(35);
		timer_die_effect_generation.set_callback([&]() {
			Vector2 particle_position;
			IMAGE* frame = atlas_run_effect.get_image(0);
			particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
			particle_position.y = position.y + size.y - frame->getheight();
			particle_list.emplace_back(particle_position, &atlas_run_effect, 150);
			});

		animation_jump_effect.set_atlas(&atlas_jump_effect);
		animation_jump_effect.set_interval(25);
		animation_jump_effect.set_loop(false);
		animation_jump_effect.set_callback([&]() {
			is_jump_effect_visible = false;
			});
		
		animation_land_effect.set_atlas(&atlas_land_effect);
		animation_land_effect.set_interval(50);
		animation_land_effect.set_loop(false);
		animation_land_effect.set_callback([&]() {
			is_land_effect_visible = false;
			});

	}
	~Player() = default;

	const Vector2& get_position()const {
		return position;
	}

	const Vector2& get_size() const {
		return size;
	}

	void set_hp(int x) {
		hp = x;
	}

	int get_hp()const{
		return hp;
	}
	
	int get_mp()const{
		return mp;
	}

	virtual void on_update(int delta){
		int direction = is_right_key_down - is_left_key_down;

		if (direction) {
			if(!is_attacking_ex)
				is_facing_right = direction > 0;
			current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
			float distance = direction * run_velocity * delta;
			on_run(distance);
		
		}
		else {
			current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
			timer_run_effect_generation.pause();
		}

		if (is_attacking_ex)
			current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;

		current_animation->on_update(delta);
		animation_jump_effect.on_update(delta);
		animation_land_effect.on_update(delta);

		timer_attack_cd.on_update(delta);
		timer_invulnerable.on_update(delta);
		timer_invulnerable_blink.on_update(delta);
		timer_run_effect_generation.on_update(delta);

		if (hp <= 0)
			timer_die_effect_generation.on_update(delta);

		particle_list.erase(std::remove_if(
			particle_list.begin(), particle_list.end(),
			[](const Particle& particle) {
				return !particle.check_valid();
			}),
			particle_list.end());

		for (Particle& particle : particle_list)
			particle.on_update(delta);

		if (is_showing_sketch_frame)
			sketch_image(current_animation->get_frame(), &img_sketch);

		move_and_collide(delta);
	}

	virtual void on_run(float distance) {
		if (is_attacking_ex)
			return;

		position.x += distance;
		timer_run_effect_generation.resume();
	}

	virtual void on_jump() {
		//设计多段连跳
		/*jump_num++;
		if (jump_num == 1)
			velocity.y += jump_velocity;
		else if (jump_num == 2) {
			velocity.y += 0.9 * jump_velocity;
		}*/

		if (velocity.y || is_attacking_ex)
			return;
		velocity.y += jump_velocity;
		is_jump_effect_visible = true;
		animation_jump_effect.reset();
		IMAGE* effect_frame = animation_jump_effect.get_frame();
		position_jump_effect.x = position.x + (size.x - effect_frame->getwidth()) / 2;
		position_jump_effect.y = position.y + size.y - effect_frame->getheight();
	}

	virtual void on_land() {
		is_land_effect_visible = true;
		animation_land_effect.reset();
		IMAGE* effect_frame = animation_land_effect.get_frame();
		position_land_effect.x = position.x + (size.x - effect_frame->getwidth()) / 2;
		position_land_effect.y = position.y + size.y - effect_frame->getheight();
	}

	virtual void on_draw(const Camera& camera){
		if (is_jump_effect_visible)
			animation_jump_effect.on_draw(camera, (int)position_jump_effect.x, (int)position_jump_effect.y);
		
		if (is_land_effect_visible)
			animation_land_effect.on_draw(camera, (int)position_land_effect.x, (int)position_land_effect.y);
		
		for (const Particle& particle : particle_list)
			particle.on_draw(camera);

		if (hp > 0 && is_invulnerable && is_showing_sketch_frame)
			putimage_alpha(camera, (int)position.x, (int)position.y, &img_sketch);
		else
			current_animation->on_draw(camera, (int)position.x, (int)position.y);
		
		if (is_debug) {
			setlinecolor(RGB(0, 125, 125));
			rectangle((int)position.x, (int)position.y, (int)(position.x + size.x), (int)(position.y + size.y));
		}
	}

	void make_invulnerable() {
		is_invulnerable = true;
		timer_invulnerable.restart();
	}

	virtual void on_input(const ExMessage& msg){ 
		switch (msg.message)
		{
		case WM_KEYDOWN:
			switch (id)
			{
			case PlayerID::P1:
				switch (msg.vkcode)
				{
				//A
				case 0x41:
					is_left_key_down = true;
					break;
				//D
				case 0x44:
					is_right_key_down = true;
					break;
				//W
				case 0x57:
					/*if (jump_num < 2)
						on_jump();
					else if (velocity.y == 0) {
						jump_num = 0;
					}*/
					on_jump();
					break;
				//J
				case 0x4A:
					if (can_attack) {
						on_attack();
						can_attack = false;
						timer_attack_cd.restart();
					}
					break;
				//K
				case 0x4B:
					if (mp >= 100) {
						on_attack_ex();
						mp = 0;
					}
					break;
				}
				break;
			case PlayerID::P2:
				switch (msg.vkcode)
				{
				case VK_LEFT:
					is_left_key_down = true;
					break;
				case VK_RIGHT:
					is_right_key_down = true;
					break;
				case VK_UP:
					on_jump();
					break;
				case 0x61:
					if (can_attack) {
						on_attack();
						can_attack = false;
						timer_attack_cd.restart();
					}
					break;
				case 0x62:
					if (mp >= 100) {
						on_attack_ex();
						mp = 0;
					}
					break;
				}
				break;
			}
			break;
		case WM_KEYUP:
			switch (id)
			{
			case PlayerID::P1:
				switch (msg.vkcode)
				{
				case 0x41:
					is_left_key_down = false;
					break;
				case 0x44:
					is_right_key_down = false;
					break;
				}
				break;
			case PlayerID::P2:
				switch (msg.vkcode)
				{
				case VK_LEFT:
					is_left_key_down = false;
					break;
				case VK_RIGHT:
					is_right_key_down = false;
					break;
				}
				break;
			}
			break;
		}
	}

	void set_id(PlayerID id) {
		this->id = id;
	}

	void set_position(float x, float y) {
		position.x = x;
		position.y = y;
	}

	virtual void on_attack() { }

	virtual void on_attack_ex() { }

protected:
	void move_and_collide(int delta) {
		float last_velocity_y = velocity.y;

		velocity.y += gravity * delta;
		position += velocity * (float)delta;

		//平台单向性
		if (velocity.y > 0) {
			for (const Platform& platform : platform_list) {
				const Platform::CollisionShape& shape = platform.shape;
				bool is_collide_x = (max(position.x + size.x, shape.right) - min(position.x, shape.left) 
					<= size.x + (shape.right - shape.left));
				bool is_collide_y = (shape.y >= position.y && shape.y <= position.y + size.y);

				if (is_collide_x && is_collide_y) {
					float delta_pos_y = velocity.y * delta;
					float last_tick_foot_pos_y = position.y + size.y - delta_pos_y;
					if (last_tick_foot_pos_y <= shape.y) {
						position.y = shape.y - size.y;
						velocity.y = 0;

						if (last_velocity_y)
							on_land();

						break;
					}
				}
			}
		}

		if (position.x <= 0)
			position.x = 0;
		//if (position.y <= 0)
		//	position.y = 0;
		if (position.x >= 1280 - size.x) 
			position.x = 1280 - size.x;
		//if (position.y >= 720 - size.y)
		//	position.y = 720 - size.y;

		if (!is_invulnerable) {
			for (Bullet* bullet : bullet_list) {
				if (!bullet->get_valid() || bullet->get_collide_target() != id) {
					continue;
				}
				if (bullet->check_collision(position, size)) {
					make_invulnerable();
					bullet->on_collide();
					bullet->set_valid(false);
					hp -= bullet->get_damage();
				}
			}
		}


	}

protected:
	const float run_velocity = 0.55f;  //速度 
	const float gravity = 1.6e-3f;     //模拟重力
	const float jump_velocity = -0.85f;//跳跃速度

protected:
	int mp = 0;
	int hp = 100;

	Vector2 size;					   //玩家尺寸，即碰撞外形
	Vector2 position;
	Vector2 velocity;				   //速度量模拟
	Animation animation_idle_left;
	Animation animation_idle_right;
	Animation animation_run_left;
	Animation animation_run_right;

	Animation animation_attack_ex_left;
	Animation animation_attack_ex_right;
	Animation animation_jump_effect;
	Animation animation_land_effect;

	bool is_jump_effect_visible = false;
	bool is_land_effect_visible = false;

	Vector2 position_jump_effect;
	Vector2 position_land_effect;

	Animation* current_animation = nullptr;

	PlayerID id = PlayerID::P1;

	bool is_left_key_down = false;
	bool is_right_key_down = false;

	bool is_facing_right = true;

	bool can_attack = true;				//是否可以释放普通攻击
	Timer timer_attack_cd;				//普通攻击的定时器
	int attack_cd = 500;

	bool is_attacking_ex = false;		//是否释放特殊攻击

	IMAGE img_sketch;
	bool is_invulnerable = false;
	bool is_showing_sketch_frame = false;  //无敌帧的视觉提示
	Timer timer_invulnerable;
	Timer timer_invulnerable_blink;

	std::vector<Particle> particle_list;

	Timer timer_run_effect_generation;
	Timer timer_die_effect_generation;

	int jump_num = 0;
};

#endif // !_PLAYER_H_
