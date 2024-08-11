#include<easyx.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>

#include"util.h"
#include"player.h"
#include"atlas.h"
#include"resource.h"
#include"scene.h"
#include"platform.h"
#include"scene_manager.h"
#include"menu_scene.h"
#include"game_scene.h"
#include"selector_scene.h"
#include"animation.h"
#include"camera.h"
#include"bullet.h"

bool running = true;
bool is_debug = false;

SceneManager scene_manager;
Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;
Scene* selector_scene = nullptr;
Camera main_camera;

std::vector<Bullet*> bullet_list;
std::vector<Platform> platform_list;

Player* player1 = nullptr;
Player* player2 = nullptr;

IMAGE* img_player1_avatar = nullptr;
IMAGE* img_player2_avatar = nullptr;

int main() {
	srand(time(NULL));
	ExMessage msg;
	const int FPS = 165;

	load_game_resources();

	initgraph(1280, 720, EX_SHOWCONSOLE);

	settextstyle(28, 0, _T(""));
	setbkmode(TRANSPARENT);

	//双缓冲
	BeginBatchDraw();

	//初始化场景
	menu_scene = new MenuScene();
	game_scene = new GameScene();
	selector_scene = new SelectorScene();

	//标定初始场景作为菜单
	scene_manager.set_current_scene(menu_scene);

	while (running) {
		//动态循环
		DWORD start_time = GetTickCount();

		//处理信息部分
		while (peekmessage(&msg)) {
			scene_manager.on_input(msg);
		}

		//更新数据
		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta = current_tick_time - last_tick_time;
		scene_manager.on_update(delta);
		last_tick_time = current_tick_time;

		cleardevice();
		//绘图
		scene_manager.on_draw(main_camera);

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / FPS) {
			Sleep(1000 / FPS - delta_time);
		}

	}

	EndBatchDraw();
	return 0;
}