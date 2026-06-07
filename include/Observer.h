#pragma once
#include "Acoes.h"
class Observer
{
private:
public:
	Observer();
	~Observer();
	virtual void Update(Actions act) = 0;
};