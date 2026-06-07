#pragma once
#include "Acoes.h"
#include <vector>
class Observer;

class Subject
{
private:
	std::vector<Observer*> observers;

public:
	Subject();
	~Subject();
	virtual void update(Actions act) = 0;
};