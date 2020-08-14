#include "ObjectMgr.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "GameMgr.h"
ObjectMgr* ObjectMgr::instance = nullptr;

ObjectMgr::ObjectMgr() :done(false), scBuff1(), scBuff2(), frontBuff(nullptr), backBuff(nullptr) {

	ShowConsoleCursor(false);

	int x, y;

	for (x = 0; x < ScreenWidth; x++) {
		for (y = 0; y < ScreenHeight; y++) {
			scBuff1[y* ScreenWidth + x] = ' ';
			scBuff2[y * ScreenWidth + x] = ' ';
			scColorBuff1[y * ScreenWidth + x] = 0;
			scColorBuff2[y * ScreenWidth + x] = 0;
		}

	}

	frontBuff = scBuff1;
	backBuff = scBuff2;
	frontColorBuff = scColorBuff1;
	backColorBuff = scColorBuff2;
	done = false;
}

ObjectMgr::~ObjectMgr()
{
}

void ObjectMgr::ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void ObjectMgr::begin()
{
	backLock.lock();
}

void ObjectMgr::clearScreen()
{
	int x, y;

	for (x = 0; x < ScreenWidth; x++) {
		for (y = 0; y < ScreenHeight; y++) {
			backBuff[y * ScreenWidth + x] = ' ';
			backColorBuff[y * ScreenWidth + x] = 0;
		}
	}
}

void ObjectMgr::end()
{
	backLock.unlock();
}

void ObjectMgr::present()
{
	frontLock.lock();
	backLock.lock();

	if (frontBuff == scBuff1) {
		frontBuff = scBuff2;
		backBuff = scBuff1;
		frontColorBuff = scColorBuff2;
		backColorBuff = scColorBuff1;
	}
	else {
		frontBuff = scBuff1;
		backBuff = scBuff2;
		frontColorBuff = scColorBuff1;
		backColorBuff = scColorBuff2;
	}

	frontLock.unlock();
	backLock.unlock();
}

void ObjectMgr::CheckCollider(std::shared_ptr<GameObject>& obj1, std::shared_ptr<GameObject>& obj2)
{
	if (!wcscmp(obj1->GetName(), L"Enemy") && !wcscmp(obj2->GetName(), L"Terrain"))
	{
		if (obj1->GetPos().x + obj1->GetWidth() - 1 >= obj2->GetPos().x &&
			obj1->GetPos().x <= obj2->GetPos().x &&
			obj1->GetPos().y + obj1->GetHeight() - 1 >= obj2->GetPos().y-1&&
			obj1->GetPos().y <= obj2->GetPos().y-1)
		{
			if (!(obj1->GetIsLand()) && !(obj2->GetIsLand()))
			{
				obj1->SetIsLand(true);
				obj2->SetIsLand(true);
				obj1->SetCollisionObjPos(obj2->GetPos());
				obj1->AddCollisionCount();
			}
		}
		else
		{
			if (obj2->GetIsLand())
			{
				obj2->SetIsLand(false);
				obj1->SubCollisionCount();
			}
		}
	}

	if (!wcscmp(obj1->GetName(), L"Player") && !wcscmp(obj2->GetName(), L"Terrain"))
	{
		if (obj1->GetPos().x + obj1->GetWidth() - 1 >= obj2->GetPos().x &&
			obj1->GetPos().x <= obj2->GetPos().x &&
			obj1->GetPos().y + obj1->GetHeight() - 1 >= obj2->GetPos().y - 1 &&
			obj1->GetPos().y <= obj2->GetPos().y - 1)
		{
			if (!(obj1->GetIsLand()) && !(obj2->GetIsLand()))
			{
				obj1->SetIsLand(true);
				obj2->SetIsLand(true);
				obj1->SetCollisionObjPos(obj2->GetPos());
				obj1->AddCollisionCount();
			}
		}
		else
		{
			if (obj2->GetIsLand())
			{
				obj2->SetIsLand(false);
				obj1->SubCollisionCount();
			}
		}
	}

	if (!wcscmp(obj1->GetName(), L"Player") && !wcscmp(obj2->GetName(), L"Enemy"))
	{
		if (obj1->GetPos().x + obj1->GetWidth() - 1 >= obj2->GetPos().x &&
			obj1->GetPos().x <= obj2->GetPos().x &&
			obj1->GetPos().y + obj1->GetHeight() - 1 >= obj2->GetPos().y &&
			obj1->GetPos().y <= obj2->GetPos().y)
		{
			obj1->SetIsAttacked(true);
			std::shared_ptr<Player> P = std::dynamic_pointer_cast<Player>(obj1);
			std::shared_ptr<Enemy> E = std::dynamic_pointer_cast<Enemy>(obj2);
			P->SetHp(E->GetStatus().attackDamage);
			printf("플레이어 공격 당함");
			P->Knockback();
		}
		else
			obj1->SetIsAttacked(false);
	}

	if (!wcscmp(obj1->GetName(), L"Bullet") && !wcscmp(obj2->GetName(), L"Enemy"))
	{
		std::shared_ptr<Bullet> B = std::dynamic_pointer_cast<Bullet>(obj1);

			// 높이 && (오른쪽 || 왼쪽)
			if(
				(obj2->GetPos().y + obj2->GetHeight() - 1 >= obj1->GetPos().y &&
					obj2->GetPos().y <= obj1->GetPos().y) && 
				(
				(B->m_dir &&
				obj1->GetPos().x + obj1->GetWidth()  >= obj2->GetPos().x  &&
				obj1->GetPos().x <= obj2->GetPos().x ) ||
				(!B->m_dir && 
					obj2->GetPos().x + obj2->GetWidth() >= obj1->GetPos().x  &&
					obj2->GetPos().x <= obj1->GetPos().x )
				)

			  )
		{
			//obj2->SetIsAttacked(true);
			obj1->SetIsAttacked(true);
			
			std::shared_ptr<Enemy> E = std::dynamic_pointer_cast<Enemy>(obj2);
			E->SetHp(B->m_bulletDamage);
			GameMgr::GetInstance()->SetEnemy(E);
			//E->Knockback();
			
		}
		else
		{
			//obj1->SetIsAttacked(false);
			obj2->SetIsAttacked(false);
		}
	}
}

void ObjectMgr::Draw(const wchar_t * img, int w, int h, int x, int y, int color)
{
	int i, j;
	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			int ty = y + j;
			int tx = x + i;
			if (tx < 0 || tx >= ScreenWidth) {
				continue;
			}
			if (ty < 0 || ty >= ScreenHeight) {
				continue;
			}
			backBuff[ty*ScreenWidth + tx] = img[j*w + i];
			backColorBuff[ty * ScreenWidth + tx] = color;
		}
	}
}

void ObjectMgr::Update()
{
	COORD pos;
	while (done == false) {
		frontLock.lock();
		int x, y;
		for (y = 0; y < ScreenHeight; y++) {
			pos.X = 0;
			pos.Y = y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			for (x = 0; x < ScreenWidth; x++) {
				SetColor(frontColorBuff[y * ScreenWidth + x], 0);
				putwchar((int)frontBuff[y * ScreenWidth + x]);
			}
		}
		ShowConsoleCursor(false);
		frontLock.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void ObjectMgr::UpdateObjects()
{
	for (int i = 0; i < TYPE_END; ++i)
	{
		for (auto iter = m_ObjectList[i].begin(); iter != m_ObjectList[i].end();)
		{
			if ((*iter).get()->Update() < 0)
				m_ObjectList[i].erase(iter++);
			else
				++iter;
		}
	}
	for (auto& object : m_ObjectList[TERRAIN])
		CheckCollider(m_ObjectList[PLAYER].front(), object); // player, terrain

	for (auto& object : m_ObjectList[ENEMY])
		CheckCollider(m_ObjectList[PLAYER].front(), object); // pleyer, enemy

	for (auto& object1 : m_ObjectList[BULLET])
		for (auto& object2 : m_ObjectList[ENEMY])
			CheckCollider(object1, object2); // bullet, enemy
}

void ObjectMgr::LateUpdateObjects()
{
	for (int i = 0; i < TYPE_END; ++i)
	{
		for (auto iter = m_ObjectList[i].begin(); iter != m_ObjectList[i].end();)
		{
			if ((*iter).get()->LateUpdate() < 0)
				m_ObjectList[i].erase(iter++);
			else
				++iter;
		}
	}

}

void ObjectMgr::RenderObjects()
{
	begin();
	clearScreen();

	for (int i = 0; i < TYPE_END; ++i)
	{
		
		for (auto& object : m_ObjectList[i])
		{
			object->Render();
		}
	}

	end();
	present();
}

HRESULT ObjectMgr::InsertObject(OBJTYPE objType, std::shared_ptr<GameObject>& obj)
{
	if (obj.get() == nullptr)
		return E_FAIL;
	m_ObjectList[objType].push_back(obj);
	return S_OK;
}
