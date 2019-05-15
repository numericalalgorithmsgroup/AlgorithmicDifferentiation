#ifndef __MC_INCLUDED__
#define __MC_INCLUDED__

template<typename ATYPE>
void price(
    const ACTIVE_INPUTS<ATYPE> &X,
    const PASSIVE_INPUTS &XP,
    ACTIVE_OUTPUTS<ATYPE> &Y,
    PASSIVE_OUTPUTS &YP
    );

#include "mc.impl.hpp"

#endif
