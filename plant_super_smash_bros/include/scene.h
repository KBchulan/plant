//��ͷ�ļ�Ϊ����ĸ��

#ifndef _SCENE_H_
#define _SCENE_H_

#include<easyx.h>
#include"camera.h"

class Scene {
public:
	//�����ù������������Ҫ����Ϊ������(������������)�����Һ���д��cuda�����ټ�༸��
	Scene() = default;
	~Scene() = default;


	//����ĳ�ʼ���߼�
	virtual void on_enter(){ }

	//��������
	virtual void on_update(int delta){ }

	//��Ⱦʵ��
	virtual void on_draw(const Camera& camera){ }

	//�����������
	virtual void on_input(const ExMessage& msg){ }

	//�˳��ĳ�ʼ���߼�
	virtual void on_exit(){ }


private:


};


#endif // !_SCENE_H_

