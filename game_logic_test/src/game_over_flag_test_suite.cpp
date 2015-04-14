#include "stdafx.hpp"

#include "snake_overflow/game_over_flag.hpp"
#include "snake_overflow/dead_snake_flag.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::Test;

class GameOverFlag : public Test
{
    
protected:

    dead_snake_flag snake_dead{false};

    game_over_flag game_over{false, this->snake_dead};

};

TEST_THAT(GameOverFlag,
     WHAT(Set),
     WHEN(Always),
     THEN(InvokesRegisteredEventHandlers))
{
    auto invoked = false;
    this->game_over.register_game_over_event_handler([&invoked]
    {
        invoked = true;
    });

    this->game_over.set();

    EXPECT_TRUE(invoked);
}

TEST_THAT(GameOverFlag,
     WHAT(InternalEventHandlingLogic),
     WHEN(WhenTheAssociatedSnakeDeadFlagIsSet),
     THEN(SetsTheGameOverFlag))
{
    auto invoked = false;
    this->game_over.register_game_over_event_handler([&invoked]
    {
        invoked = true;
    });

    this->snake_dead.set();

    EXPECT_TRUE(invoked);
    EXPECT_TRUE(this->game_over);
}

} }