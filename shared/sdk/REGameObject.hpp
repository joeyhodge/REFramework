#pragma once

#include "REManagedObject.hpp"

namespace utility {
namespace re_game_object {
std::string get_name(::REGameObject* obj);
::RETransform* get_transform(::REGameObject* obj);
}
}
