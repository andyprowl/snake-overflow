#include "stdafx.hpp"

#include "snake_overflow/diet_pill.hpp"
#include "snake_overflow/fruit.hpp"
#include "snake_overflow/game.hpp"
#include "snake_overflow/invulnerability_potion.hpp"
#include "snake_overflow/playing_phase_sound_player.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/speed_booster.hpp"

namespace snake_overflow
{
    
playing_phase_sound_player::playing_phase_sound_player(game& g)
{
    create_sounds();

    register_item_picking_sound_emitter(g);

    register_game_over_sound_emitter(g);
}

void playing_phase_sound_player::create_sounds()
{
    create_bite_sound();

    create_electronic_sound();

    create_invulnerability_sound();

    create_diet_pill_sound();

    create_game_over_sound();
}

void playing_phase_sound_player::create_bite_sound()
{
    auto const asset = cinder::app::loadAsset("sounds/crunch.wav");
    auto const source = cinder::audio::load(asset);
    this->bite_sound = cinder::audio::Voice::create(source);    
}

void playing_phase_sound_player::create_electronic_sound()
{
    auto const asset = cinder::app::loadAsset("sounds/electronic.wav");
    auto const source = cinder::audio::load(asset);
    this->electronic_sound = cinder::audio::Voice::create(source);    
}

void playing_phase_sound_player::create_invulnerability_sound()
{
    auto const asset = cinder::app::loadAsset("sounds/godlike.wav");
    auto const source = cinder::audio::load(asset);
    this->invulnerability_sound = cinder::audio::Voice::create(source);    
}

void playing_phase_sound_player::create_game_over_sound()
{
    auto const asset = cinder::app::loadAsset("sounds/game over.wav");
    auto const source = cinder::audio::load(asset);
    this->game_over_sound = cinder::audio::Voice::create(source);    
}

void playing_phase_sound_player::create_diet_pill_sound()
{
    auto const asset = cinder::app::loadAsset("sounds/squish.wav");
    auto const source = cinder::audio::load(asset);
    this->diet_pill_sound = cinder::audio::Voice::create(source);    
}

void playing_phase_sound_player::register_item_picking_sound_emitter(game& g)
{
    auto& s = g.get_snake();

    s.register_item_picked_event_handler([this] (item& i)
    {
        on_item_picked(i);
    });
}

void playing_phase_sound_player::register_game_over_sound_emitter(game& g)
{
    g.is_game_over.register_game_over_event_handler([this]
    {
        play_game_over_sound();
    });
}

void playing_phase_sound_player::on_item_picked(item const& i) const
{
    if (dynamic_cast<fruit const*>(&i) != nullptr)
    {
        play_bite_sound();
    }
    else if (dynamic_cast<speed_booster const*>(&i) != nullptr)
    {
        play_electronic_sound();
    }
    else if (dynamic_cast<invulnerability_potion const*>(&i) != nullptr)
    {
        play_invulnerability_sound();
    }
    else if (dynamic_cast<diet_pill const*>(&i) != nullptr)
    {
        play_diet_pill_sound();
    }
}

void playing_phase_sound_player::play_bite_sound() const
{
    this->bite_sound->start();
}

void playing_phase_sound_player::play_electronic_sound() const
{
    this->electronic_sound->start();
}

void playing_phase_sound_player::play_invulnerability_sound() const
{
    this->invulnerability_sound->start();
}

void playing_phase_sound_player::play_diet_pill_sound() const
{
    this->diet_pill_sound->start();
}

void playing_phase_sound_player::play_game_over_sound() const
{
    this->game_over_sound->start();
}

}