#pragma once

#include "snake_overflow/item_position_picker.hpp"

namespace snake_overflow { namespace testing
{

class item_position_picker_strict_mock : public item_position_picker
{

public:

    MOCK_CONST_METHOD0(pick_item_position, position());

};

using item_position_picker_mock = 
      ::testing::NiceMock<item_position_picker_strict_mock>;

} }