#pragma once
#include "Header.h"
#include "GameObject.h"

// �߷��� �ο��ȴ�.
class RigidBody {

private:
	std::shared_ptr<GameObject> parentObject;

public:
	int mass;
	float gravitySpeed;

public:
	RigidBody(std::shared_ptr<GameObject>& obj);
	~RigidBody();

	void Update();
	
	void AddForce(int powerX, int powerY);

};