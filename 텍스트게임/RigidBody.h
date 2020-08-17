#pragma once
#include "Header.h"
#include "GameObject.h"

// 중력이 부여된다.
class RigidBody {

private:
	std::weak_ptr<GameObject> parentObject;

public:
	int mass;
	float gravitySpeed;

public:
	RigidBody(std::shared_ptr<GameObject>& obj);
	~RigidBody();

	void Update();
	
	void AddForce(float powerX, float powerY);

};