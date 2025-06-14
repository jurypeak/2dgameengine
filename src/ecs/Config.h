#ifndef CONFIG_H
#define CONFIG_H

#include <bitset>

/* 
 * A bitset (1 and 0s) to keep track of which components
 * an entity has, and also helps keep track of which
 * entities a system is intrested in.
*/

constexpr unsigned int MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

#endif
