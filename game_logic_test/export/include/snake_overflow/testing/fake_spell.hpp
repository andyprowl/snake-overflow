#pragma once

#include "snake_overflow/spell.hpp"

namespace snake_overflow
{

class fake_spell : public spell
{

public:
    
    fake_spell(std::vector<spell*>* last_affecting_spells = nullptr)
        : last_affecting_spells{last_affecting_spells}
    {
    }

    virtual void affect(snake&) override
    {
        if (this->last_affecting_spells != nullptr)
        {
            this->last_affecting_spells->push_back(this);
        }
    }

private:

    std::vector<spell*>* last_affecting_spells = nullptr;

};

}