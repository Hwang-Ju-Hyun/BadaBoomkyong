#pragma once

class Boss;
class Player;
class Transform;
class RigidBody;
class Monster;

class BlackBoard
{
public:
	BlackBoard();
	~BlackBoard();
	void BBInit(Boss* _boss);
private:
	Boss* m_pBoss;
	Player* m_pPlayer;
	RigidBody* m_pBossRigidBody;
	Transform* m_pPlayerTransform;
	Transform* m_pBossTransform;
public:
	inline Boss* GetBoss()const { return m_pBoss; }
	inline Player* GetPlayer()const { return m_pPlayer; }
	inline Transform* GetPlayerTransform()const { return m_pPlayerTransform; }
	inline Transform* GetBossTransform()const { return m_pBossTransform; }
	inline RigidBody* GetBossRigidBody()const { return m_pBossRigidBody; }

//CONDITION
public:
	bool IsPlayerNear(Monster* _monster);
	bool IsPlayerNearX(Monster* _monster);
};

