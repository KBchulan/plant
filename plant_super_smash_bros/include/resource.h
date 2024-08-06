#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include<easyx.h>
#include"atlas.h"
#include"util.h"
#pragma comment(lib,"Winmm.lib")

IMAGE img_menu_background;                      // 主菜单背景图片
	
IMAGE img_VS;                                   // VS 艺术字图片
IMAGE img_1P;                                   // 1P 文本图片
IMAGE img_2P;                                   // 2P 文本图片

IMAGE img_1P_desc;                              // 1P 键位描述图片
IMAGE img_2P_desc;                              // 2P 键位描述图片

IMAGE img_gravestone_left;                      // 朝向左的墓碑图片
IMAGE img_gravestone_right;                     // 朝向右的墓碑图片

IMAGE img_selector_tip;                         // 选角界面提示文本图片
IMAGE img_selector_background;                  // 选角界面背景图片

IMAGE img_1P_selector_btn_idle_left;            // 1P 向左选择按钮默认状态图片
IMAGE img_1P_selector_btn_idle_right;           // 1P 向右选择按钮默认状态图片
IMAGE img_1P_selector_btn_down_left;            // 1P 向左选择按钮按下状态图片
IMAGE img_1P_selector_btn_down_right;           // 1P 向右选择按钮按下状态图片

IMAGE img_2P_selector_btn_idle_left;            // 2P 向左选择按钮默认状态图片
IMAGE img_2P_selector_btn_idle_right;           // 2P 向右选择按钮默认状态图片
IMAGE img_2P_selector_btn_down_left;            // 2P 向左选择按钮按下状态图片
IMAGE img_2P_selector_btn_down_right;           // 2P 向右选择按钮按下状态图片

IMAGE img_peashooter_selector_background_left;  // 选角界面朝向左的婉逗射手背景图片
IMAGE img_peashooter_selector_background_right; // 选角界面朝向右的婉逗射手背景图片

IMAGE img_sunflower_selector_background_left;   // 选角界面朝向左的龙日葵背景图片
IMAGE img_sunflower_selector_background_right;  // 选角界面朝向右的龙日葵背景图片

IMAGE img_sky;                                  // 天空图片
IMAGE img_hills;                                // 山脉图片
IMAGE img_platform_large;                       //大型平台图片
IMAGE img_platform_small;                       //小型平台图片

IMAGE img_1P_cursor;                            // 1P 指示光标图片
IMAGE img_2P_cursor;                            // 2P 指示光标图片

Atlas atlas_peashooter_idle_left;               // 婉逗射手朝向左的默认动画图集
Atlas atlas_peashooter_idle_right;              // 婉逗射手朝向右的默认动画图集
Atlas atlas_peashooter_run_left;                // 婉逗射手朝向左的跑步动画图集
Atlas atlas_peashooter_run_right;               // 婉逗射手朝向右的跑步动画图集
Atlas atlas_peashooter_attack_ex_left;          // 婉逗射手朝向左的攻击动画图集
Atlas atlas_peashooter_attack_ex_right;         // 婉逗射手朝向右的攻击动画图集
Atlas atlas_peashooter_die_left;                // 婉逗射手朝向左的死亡动画图集
Atlas atlas_peashooter_die_right;               // 婉逗射手朝向右的死亡动画图集

Atlas atlas_sunflower_idle_right;               // 龙日葵朝向右的默认动画图集
Atlas atlas_sunflower_idle_left;               // 龙日葵朝向左的默认动画图集
Atlas atlas_sunflower_run_left;                 // 龙日葵朝向左的跑步动画图集
Atlas atlas_sunflower_run_right;                // 龙日葵朝向右的跑步动画图集
Atlas atlas_sunflower_attack_ex_left;              // 龙日葵朝向左的攻击动画图集
Atlas atlas_sunflower_attack_ex_right;             // 龙日葵朝向右的攻击动画图集
Atlas atlas_sunflower_die_left;                 // 龙日葵朝向左的死亡动画图集
Atlas atlas_sunflower_die_right;                // 龙日葵朝向右的死亡动画图集

IMAGE img_pea;                                  // 豌豆图片

Atlas atlas_pea_break;                          // 豌豆破碎动画图集
Atlas atlas_sun;                                // 日光动画图集
Atlas atlas_sun_explode;                        // 日光爆炸动画图集
Atlas atlas_sun_ex;                             // 特殊日光动画图集
Atlas atlas_sun_ex_explode;                     // 特殊日光爆炸动画图集
Atlas atlas_sun_text;                           // “日” 文本动画图集

Atlas atlas_run_effect;                         // 奔跑特效动画图集
Atlas atlas_jump_effect;                        // 跳跃特效动画图集
Atlas atlas_land_effect;                        // 落地特效动画图集

IMAGE img_1P_winner;                            // 1P 获胜文本图片
IMAGE img_2P_winner;                            // 2P 获胜文本图片
IMAGE img_winner_bar;                           // 获胜玩家背景文本图片

IMAGE img_avatar_peashooter;                    // 婉逗射手头像图片
IMAGE img_avatar_sunflower;                     // 龙日葵头像图片

void flip_atlas(Atlas& src, Atlas& dst) {
	dst.clear();
	for (int i = 0; i < src.get_size(); i++) {
		IMAGE img_flpipped;
		flip_image(src.get_image(i), &img_flpipped);
		dst.add_image(img_flpipped);
	}
}


void load_game_resources(){

	AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);
	loadimage(&img_menu_background, _T("resources/menu_background.png"));
	loadimage(&img_VS, _T("resources/VS.png"));
	loadimage(&img_1P, _T("resources/1P.png"));
	loadimage(&img_2P, _T("resources/2P.png"));
	loadimage(&img_1P_desc, _T("resources/1P_desc.png"));
	loadimage(&img_2P_desc, _T("resources/2P_desc.png"));
	loadimage(&img_gravestone_right, _T("resources/gravestone.png"));
	flip_image(&img_gravestone_right, &img_gravestone_left);
	loadimage(&img_selector_tip, _T("resources/selector_tip.png"));
	loadimage(&img_selector_background, _T("resources/selector_background.png"));
	loadimage(&img_1P_selector_btn_idle_right, _T("resources/1P_selector_btn_idle.png"));
	flip_image(&img_1P_selector_btn_idle_right, &img_1P_selector_btn_idle_left);
	loadimage(&img_1P_selector_btn_down_right, _T("resources/1P_selector_btn_down.png"));
	flip_image(&img_1P_selector_btn_down_right, &img_1P_selector_btn_down_left);
	loadimage(&img_2P_selector_btn_idle_right, _T("resources/2P_selector_btn_idle.png"));
	flip_image(&img_2P_selector_btn_idle_right, &img_2P_selector_btn_idle_left);
	loadimage(&img_2P_selector_btn_down_right, _T("resources/2P_selector_btn_down.png"));
	flip_image(&img_2P_selector_btn_down_right, &img_2P_selector_btn_down_left);
	loadimage(&img_peashooter_selector_background_right, _T("resources/peashooter_selector_background.png"));
	flip_image(&img_peashooter_selector_background_right, &img_peashooter_selector_background_left);
	loadimage(&img_sunflower_selector_background_right, _T("resources/sunflower_selector_background.png"));
	flip_image(&img_sunflower_selector_background_right, &img_sunflower_selector_background_left);

	loadimage(&img_sky, _T("resources/sky.png"));
	loadimage(&img_hills, _T("resources/hills.png"));
	loadimage(&img_platform_large, _T("resources/platform_large.png"));
	loadimage(&img_platform_small, _T("resources/platform_small.png"));
	loadimage(&img_1P_cursor, _T("resources/1P_cursor.png"));
	loadimage(&img_2P_cursor, _T("resources/2P_cursor.png"));


	atlas_peashooter_idle_right.load_from_file(_T("resources/peashooter_idle_%d.png"), 9);
	flip_atlas(atlas_peashooter_idle_right, atlas_peashooter_idle_left);
	atlas_peashooter_run_right.load_from_file(_T("resources/peashooter_run_%d.png"), 5);
	flip_atlas(atlas_peashooter_run_right, atlas_peashooter_run_left);
	atlas_peashooter_attack_ex_right.load_from_file(_T("resources/peashooter_attack_ex_%d.png"), 3);
	flip_atlas(atlas_peashooter_attack_ex_right, atlas_peashooter_attack_ex_left);
	atlas_peashooter_die_right.load_from_file(_T("resources/peashooter_die_%d.png"), 4);
	flip_atlas(atlas_peashooter_die_right, atlas_peashooter_die_left);
	atlas_sunflower_idle_right.load_from_file(_T("resources/sunflower_idle_%d.png"), 8);
	flip_atlas(atlas_sunflower_idle_right, atlas_sunflower_idle_left);
	atlas_sunflower_run_right.load_from_file(_T("resources/sunflower_run_%d.png"), 5);
	flip_atlas(atlas_sunflower_run_right, atlas_sunflower_run_left);
	atlas_sunflower_attack_ex_right.load_from_file(_T("resources/sunflower_attack_ex_%d.png"), 9);
	flip_atlas(atlas_sunflower_attack_ex_right, atlas_sunflower_attack_ex_left);
	atlas_sunflower_die_right.load_from_file(_T("resources/sunflower_die_%d.png"), 2);
	flip_atlas(atlas_sunflower_die_right, atlas_sunflower_die_left);

	loadimage(&img_pea, _T("resources/pea.png"));
	atlas_pea_break.load_from_file(_T("resources/pea_break_%d.png"), 3);
	atlas_sun.load_from_file(_T("resources/sun_%d.png"), 5);
	atlas_sun_explode.load_from_file(_T("resources/sun_explode_%d.png"), 5);
	atlas_sun_ex.load_from_file(_T("resources/sun_ex_%d.png"), 5);
	atlas_sun_ex_explode.load_from_file(_T("resources/sun_ex_explode_%d.png"), 5);
	atlas_sun_text.load_from_file(_T("resources/sun_text_%d.png"), 6);
	atlas_run_effect.load_from_file(_T("resources/run_effect_%d.png"), 4);
	atlas_jump_effect.load_from_file(_T("resources/jump_effect_%d.png"), 5);
	atlas_land_effect.load_from_file(_T("resources/land_effect_%d.png"), 2);

	loadimage(&img_1P_winner, _T("resources/1p_winner.png"));
	loadimage(&img_2P_winner, _T("resources/2p_winner.png"));
	loadimage(&img_winner_bar, _T("resources/winner_bar.png"));
	loadimage(&img_avatar_peashooter, _T("resources/avatar_peashooter.png"));
	loadimage(&img_avatar_sunflower, _T("resources/avatar_sunflower.png"));

	mciSendString(_T("open resources/bgm_game.mp3 alias bgm_game"), NULL, 0, NULL);
	mciSendString(_T("open resources/bgm1.mp3 alias bgm1"), NULL, 0, NULL);
	mciSendString(_T("open resources/bgm_menu.mp3 alias bgm_menu"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_1.mp3 alias pea_break_1"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_2.mp3 alias pea_break_2"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_3.mp3 alias pea_break_3"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_1.mp3 alias pea_shoot_1"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_2.mp3 alias pea_shoot_2"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_ex.mp3 alias pea_shoot_ex"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_explode.mp3 alias sun_explode"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_explode_ex.mp3 alias sun_explode_ex"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_text.mp3 alias sun_text"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_confirm.wav alias ui_confirm"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_switch.wav alias ui_switch"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_win.wav alias ui_win"), NULL, 0, NULL);

}

#endif // !_RESOURCE_H_
