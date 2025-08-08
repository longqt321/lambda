#pragma once
#include <vector>

template<typename V>
bool operator==(const std::vector<V>& a, const std::vector<V>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}