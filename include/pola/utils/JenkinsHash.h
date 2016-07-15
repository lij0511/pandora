
#ifndef POLA_JENKINSHASH_H_
#define POLA_JENKINSHASH_H_

#include "pola/utils/TypeHelpers.h"

namespace pola {
namespace utils {

uint32_t JenkinsHashMix(uint32_t hash, uint32_t data);

hash_t JenkinsHashWhiten(uint32_t hash);

uint32_t JenkinsHashMixBytes(uint32_t hash, const uint8_t* bytes, size_t size);

uint32_t JenkinsHashMixShorts(uint32_t hash, const uint16_t* shorts, size_t size);

}
}

#endif // POLA_JENKINSHASH_H_
