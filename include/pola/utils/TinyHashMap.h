#ifndef POLA_TINYHASHMAP_H_
#define POLA_TINYHASHMAP_H_

#include "pola/utils/BasicHashtable.h"

namespace pola {
namespace utils {

/**
 * A very simple hash map that doesn't allow duplicate keys, overwriting the older entry.
 */
template <typename TKey, typename TValue>
class TinyHashMap {
public:
    typedef key_value_pair_t<TKey, TValue> TEntry;

    /**
     * Puts an entry in the hash, removing any existing entry with the same key
     */
    void put(TKey key, TValue value) {
        hash_t hash = hash_type(key);

        ssize_t index = mTable.find(-1, hash, key);
        if (index != -1) {
            mTable.removeAt(index);
        }

        TEntry initEntry(key, value);
        mTable.add(hash, initEntry);
    }

    /**
     * Return true if key is in the map, in which case stores the value in the output ref
     */
    bool get(TKey key, TValue& outValue) {
        hash_t hash = hash_type(key);
        ssize_t index = mTable.find(-1, hash, key);
        if (index == -1) {
            return false;
        }
        outValue = mTable.entryAt(index).value;
        return true;
    }

    void clear() { mTable.clear(); }

private:
    BasicHashtable<TKey, TEntry> mTable;
};

}
};

#endif // POLA_TINYHASHMAP_H_
