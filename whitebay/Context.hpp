#pragma once

#include <atomic>
#include <unordered_map>
#include <shared_mutex>
#include <unordered_map>
#include <string>

struct Context
{
    std::atomic<int> count{0};
    std::unordered_map<int, std::pair<int/*fd*/, std::string/*name*/>> filesForWrite;
    std::shared_mutex guard;
};