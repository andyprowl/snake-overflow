#include "stdafx.hpp"

#include "snake_overflow/snake.hpp"

namespace snake_overflow
{

snake::snake(std::unique_ptr<snake_body>&& body, std::string skin)
    : body{std::move(body)}
    , skin(std::move(skin))
    , is_dead{false}
    , invulnerability_bonus{false, is_dead}
    , speed{2, is_dead, 1, 5}
    , age{0}
    , next_action{maneuvre::straight_move}
{
    this->collider = std::make_unique<collision_handler>(*this, this->is_dead);
}

snake_body& snake::get_body() const
{
    return *(this->body);
}

terrain& snake::get_terrain() const
{
    return this->body->get_terrain();
}

int snake::get_length() const
{
    return this->body->get_length();
}

void snake::update()
{
    if (this->is_dead)
    {
        return;
    }

    if (is_time_to_move_body())
    {
        move_body();
    }

    affect_by_pending_spells();

    ++(this->age);
}

void snake::turn_left()
{
    throw_if_dead();

    next_action = maneuvre::left_turn;
}

void snake::turn_right()
{
    throw_if_dead();

    next_action = maneuvre::right_turn;
}

void snake::grow(int const size)
{
    throw_if_dead();

    this->body->grow(size);
}

void snake::shrink(int const size)
{
    throw_if_dead();

    this->body->shrink(size);
}

void snake::add_spell(std::unique_ptr<spell>&& s)
{
    this->spells.push_back(std::move(s));
}

void snake::remove_spell(spell const& s)
{
    auto const it = std::find_if(
        std::begin(this->spells),
        std::end(this->spells),
        [&s] (std::unique_ptr<spell> const& existing_spell)
    {
        return (existing_spell.get() == &s);
    });

    this->spells.erase(it);
}

std::vector<spell*> snake::get_all_spells() const
{
    auto v = std::vector<spell*>{};

    v.reserve(this->spells.size());

    std::transform(std::cbegin(this->spells),
                   std::cend(this->spells),
                   std::back_inserter(v),
                   [] (std::unique_ptr<spell> const& s)
    {
        return s.get();
    });

    return v;
}

void snake::throw_if_dead()
{
    if (this->is_dead)
    {
        throw dead_snake_exception{};
    }
}

bool snake::is_time_to_move_body() const
{
    auto const update_interval = get_snake_update_interval(*this);

    return (this->age % update_interval == 0);
}

void snake::move_body()
{
    if (this->next_action == maneuvre::left_turn)
    {
        this->body->turn_left();
    }
    else if (this->next_action == maneuvre::right_turn)
    {
        this->body->turn_right();
    }

    this->body->advance();

    this->next_action = maneuvre::straight_move;
}

void snake::affect_by_pending_spells()
{
    // Affecting spells will remove themselves when expiring, so we cannot
    // directly iterate through the owning container...

    auto all_spells = get_all_spells();

    for (auto const s : all_spells)
    {
        s->affect(*this);
    }
}

int get_snake_update_interval(snake const& s)
{
    return *(s.speed.maximum_value) - s.speed + 1;
}

}