/*
 * JenkinsHash.cpp
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#include "pola/utils/JenkinsHash.h"

namespace pola {
namespace utils {

uint32_t JenkinsHashMix(uint32_t hash, uint32_t data) {
    hash += data;
    hash += (hash << 10);
    hash ^= (hash >> 6);
    return hash;
}

hash_t JenkinsHashWhiten(uint32_t hash) {
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

uint32_t JenkinsHashMixBytes(uint32_t hash, const uint8_t* bytes, size_t size) {
    hash = JenkinsHashMix(hash, (uint32_t)size);
    size_t i;
    for (i = 0; i < (size & -4); i += 4) {
        uint32_t data = bytes[i] | (bytes[i+1] << 8) | (bytes[i+2] << 16) | (bytes[i+3] << 24);
        hash = JenkinsHashMix(hash, data);
    }
    if (size & 3) {
        uint32_t data = bytes[i];
        data |= ((size & 3) > 1) ? (bytes[i+1] << 8) : 0;
        data |= ((size & 3) > 2) ? (bytes[i+2] << 16) : 0;
        hash = JenkinsHashMix(hash, data);
    }
    return hash;
}

uint32_t JenkinsHashMixShorts(uint32_t hash, const uint16_t* shorts, size_t size) {
    hash = JenkinsHashMix(hash, (uint32_t)size);
    size_t i;
    for (i = 0; i < (size & -2); i += 2) {
        uint32_t data = shorts[i] | (shorts[i+1] << 16);
        hash = JenkinsHashMix(hash, data);
    }
    if (size & 1) {
        uint32_t data = shorts[i];
        hash = JenkinsHashMix(hash, data);
    }
    return hash;
}

}
}
