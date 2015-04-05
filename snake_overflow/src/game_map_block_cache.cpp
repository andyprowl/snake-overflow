#include "stdafx.hpp"

#include "snake_overflow/game_map.hpp"
#include "snake_overflow/game_map_block_cache.hpp"

namespace snake_overflow
{

std::vector<block> game_map_block_cache::get_map_blocks(game_map const& m) const
{
    auto const map_name = m.get_name();

    auto const it = this->block_map.find(map_name);
    if (it == std::cend(this->block_map))
    {
        cache_map_blocks(m);

        return this->block_map.at(map_name);
    }

    return it->second;
}

void game_map_block_cache::cache_map_blocks(game_map const& m) const
{
    auto& t = m.get_terrain();

    auto blocks = get_all_visible_blocks(t);

    sort_blocks_for_rendering(blocks);

    auto name = m.get_name();

    this->block_map.emplace(std::move(name), std::move(blocks));
}

void game_map_block_cache::sort_blocks_for_rendering(
    std::vector<block>& blocks) const
{
    std::stable_sort(std::begin(blocks), 
                     std::end(blocks),
                     [] (util::value_ref<block> lhs, 
                         util::value_ref<block> rhs)
    {
        if (lhs.color.alpha == rhs.color.alpha)
        {
            return (lhs.origin < rhs.origin);
        }
        else
        {
            return (lhs.color.alpha > rhs.color.alpha);
        }
    });
}

}