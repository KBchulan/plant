//此头文件为场景母版

#ifndef _SCENE_H_
#define _SCENE_H_

#include<easyx.h>
#include"camera.h"

class Scene {
public:
	//不适用构造和析构，主要还是为了性能(生命周期问题)，等我后续写完cuda，能再简洁几倍
	Scene() = default;
	~Scene() = default;


	//进入的初始化逻辑
	virtual void on_enter(){ }

	//处理数据
	virtual void on_update(int delta){ }

	//渲染实现
	virtual void on_draw(const Camera& camera){ }

	//处理玩家输入
	virtual void on_input(const ExMessage& msg){ }

	//退出的初始化逻辑
	virtual void on_exit(){ }


private:


};


#endif // !_SCENE_H_

