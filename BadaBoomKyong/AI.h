#pragma once
#include <map>
#include <vector>
#include "header.h"
#include "BaseComponent.h"

class GameObject;
class BaseState;
class Monster;

class AI
	:public BaseComponent
{
public:
	AI(GameObject* _owner);
	~AI();
private:
	std::map<MONSTER_STATE, BaseState*> m_mapMonsterState;
	BaseState* m_pCurState;
	Monster* m_pMonster;
public:
	//todo ������ Ű���� �ְ� switch�ϴ½����� �ϴµ� rtti�� ������ �׷������� ���߿� �����丵�ض�
	void InsertState(MONSTER_STATE _state);
	void SetCurState(MONSTER_STATE _state);
	void ChangeState(MONSTER_STATE _state);
	inline BaseState* GetCurrentState()const { return m_pCurState; }
	BaseState* FindState(MONSTER_STATE _state)const;
	inline void RegistryMonster(Monster* _mon) { m_pMonster = _mon; }
	inline Monster* GetMonster()const { return m_pMonster; }
public:
	virtual void Init()  override;
	virtual void Update()override;
	virtual void Exit()  override;
public:
	static BaseRTTI* CreateAIComponent();
public:
	static constexpr const char* AITypeName = "AI";
	static constexpr const char* StateListTypeName = "StateList";
	virtual void LoadFromJson(const json& _str) override;
	virtual json SaveToJson(const json& _str)   override;
};