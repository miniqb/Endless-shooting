#ifndef _SCENE_H_
#define _SCENE_H_
#include "Camera.h"
class Scene:public Node
{
public:
	Scene();
	~Scene();
public:
	virtual const Vec2& getPosition() override;
	virtual void init();
	virtual void handleInput(UINT32 KeyChar, int ActionType);//�����¼�
	virtual void handleInput(int x, int y, int ActionType);//����¼�
	void addSurfaceNode(Node* node);
	virtual void updateCamera() {};
protected:
	virtual void updateSelf(float dt) override;
	virtual void drawSelf(HDC hdc) override;
protected:
	Camera* _camera;
	std::vector<Node*> _surfaceNodes;
};
#endif // !_SCENE_H_
