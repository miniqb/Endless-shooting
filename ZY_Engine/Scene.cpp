#include "Scene.h"

Scene::Scene() :
	Node()
{
	_camera = Camera::GetInstance();
}

Scene::~Scene()
{
}

const Vec2& Scene::getPosition()
{
	//return -_camera->getPosition();
	return _position;
}

void Scene::init()
{
}

void Scene::handleInput(UINT32 KeyChar, int ActionType)
{
}

void Scene::handleInput(int x, int y, int ActionType)
{
}

void Scene::addSurfaceNode(Node* node)
{
	_surfaceNodes.push_back(node);
}

void Scene::updateSelf(float dt)
{
	updateCamera();
	unsigned int length = _surfaceNodes.size();
	for (size_t i = 0; i < length; ++i)
	{
		_surfaceNodes[i]->update(dt);
	}
}

void Scene::drawSelf(HDC hdc)
{
	unsigned int length = _surfaceNodes.size();
	for (size_t i = 0; i < length; ++i)
	{
		_surfaceNodes[i]->draw(hdc);
	}
}
