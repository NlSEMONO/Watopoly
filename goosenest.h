#ifndef __GOOSENEST_H__
#define __GOOSENEST_H__

#include "square.h"

class GooseNest : public Square {
    int accumulated;

    public:
        virtual ~GooseNest() override;
        GooseNest();
        int getAccumulated() const;
        void setAccumulated(int n);
};

#endif
