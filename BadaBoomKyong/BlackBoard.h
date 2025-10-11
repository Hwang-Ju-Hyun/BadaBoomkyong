#pragma once

class Boss;
class Player;
class Transform;


class BlackBoard
{
public:
	BlackBoard();
	~BlackBoard();
	void BBInit(Boss* _boss);
private:
	Boss* m_pBoss;
	Player* m_pPlayer;
	Transform* m_pPlayerTransform;
	Transform* m_pBossTransform;
public:
	inline Boss* GetBoss()const { return m_pBoss; }
	inline Player* GetPlayer()const { return m_pPlayer; }
	inline Transform* GetPlayerTransform()const { return m_pPlayerTransform; }
	inline Transform* GetBossTransform()const { return m_pBossTransform; }
};

