#pragma once

#include <cinder/audio/Voice.h>

namespace snake_overflow
{

class game;
class item;
    
class playing_phase_sound_player
{

public:

    playing_phase_sound_player(game& g);
    
private:

    void create_sounds();

    void create_bite_sound();

    void create_electronic_sound();

    void create_invulnerability_sound();

    void create_diet_pill_sound();

    void create_game_over_sound();

    void register_item_picking_sound_emitter(game& g);

    void register_game_over_sound_emitter(game& g);

    void on_item_picked(item const& i) const;

    void play_bite_sound() const;

    void play_electronic_sound() const;

    void play_invulnerability_sound() const;

    void play_diet_pill_sound() const;

    void play_game_over_sound() const;

private:

    cinder::audio::VoiceSamplePlayerNodeRef bite_sound; 

    cinder::audio::VoiceSamplePlayerNodeRef electronic_sound; 

    cinder::audio::VoiceSamplePlayerNodeRef game_over_sound; 

    cinder::audio::VoiceSamplePlayerNodeRef invulnerability_sound; 

    cinder::audio::VoiceSamplePlayerNodeRef diet_pill_sound; 

};

}