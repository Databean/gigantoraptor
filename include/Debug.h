#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

#define DEBUG_MESSAGES 0

#if DEBUG_MESSAGES
#define DEBUG(t) std::cout << t << std::endl
#else
#define DEBUG(t)
#endif

#endif