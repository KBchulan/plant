#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include<iostream>
#include"scene.h"
#include"scene_manager.h"
#pragma comment(lib,"Winmm.lib")

extern SceneManager scene_manager;
extern IMAGE img_menu_background;

class MenuScene :public Scene {
public:

	MenuScene() = default;
	~MenuScene() = default;

	void on_enter() {
		mciSendString(_T("play bgm1 repeat from 0"), NULL, 0, NULL);
	}

	void on_update(int delta) {
		//......
	}

	void on_draw(const Camera& camera) {
		putimage(0, 0, &img_menu_background);
	}

	void on_input(const ExMessage& msg) {
		if (msg.message == WM_KEYUP) {
			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			scene_manager.switch_to(SceneManager::SceneType::Selector);
		}
	}

	void on_exit() {
		//......
	}

private:
	
};


#endif // !_MENU_SCENE_H_
