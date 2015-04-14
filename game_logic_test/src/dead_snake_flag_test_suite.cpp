#include "stdafx.hpp"

#include "snake_overflow/dead_snake_flag.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::Test;

class DeadSnakeFlag : public Test
{
    
protected:

    dead_snake_flag snake_dead{false};

};

TEST_THAT(DeadSnakeFlag,
     WHAT(Set),
     WHEN(Always),
     THEN(InvokesRegisteredEventHandlers))
{
    auto invoked = false;
    this->snake_dead.register_death_event_handler([&invoked]
    {
        invoked = true;
    });

    this->snake_dead.set();

    EXPECT_TRUE(invoked);
}

} }