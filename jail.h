#ifndef __JAIL_H_
#define __JAIL_H_
#include <map>
#include "square.h"
#include "player.h"

class Jail : public Square
{

public:
    Jail();
    virtual ~Jail() override;
};

#endif
