#pragma once

#include "Acoes.h"

class Subject
{
public:
    Subject();
    virtual ~Subject();

    virtual void update(Actions act) = 0;
};