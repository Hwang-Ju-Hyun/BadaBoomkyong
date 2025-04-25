#pragma once
#include "BaseComponent.h"
class Player :
    public BaseComponent
{
public:
    Player(GameObject* _owner);
    virtual ~Player()override;
public:
    void Jump();
    void Move();    
};