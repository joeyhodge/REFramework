#include "RETypeDB.hpp"

#include "REComponent.hpp"
#include "REGameObject.hpp"

namespace utility::re_component::detail {
::REGameObject* get_game_object_via_property(::REComponent* comp) {
    if (comp == nullptr) {
        return nullptr;
    }

    static const auto component_t = sdk::find_type_definition("via.Component");
    static const auto get_game_object_method = component_t != nullptr ? component_t->get_method("get_GameObject") : nullptr;

    if (get_game_object_method == nullptr) {
        return nullptr;
    }

    return get_game_object_method->call<::REGameObject*>(sdk::get_thread_context(), comp);
}
}

namespace utility::re_game_object {
std::string get_name(REGameObject* obj) {
    if (obj == nullptr) {
        return {};
    }

    // Only doing this on newer versions where we know it works
    // Haven't tested it on older versions so just to be safe.
#if TDB_VER >= 71
    static const auto game_object_t = sdk::find_type_definition("via.GameObject");
    static const auto get_name_fn = game_object_t != nullptr ? game_object_t->get_method("get_Name") : nullptr;

    if (get_name_fn != nullptr) {
        auto str = get_name_fn->call<::SystemString*>(sdk::get_thread_context(), obj);

        if (str != nullptr) {
            return utility::re_string::get_string(str);
        }
    }
#endif

    // We rely on the reflected function first because
    // this offset might change between versions.
    return utility::re_string::get_string(obj->name);
}

RETransform* get_transform(REGameObject* obj) {
    if (obj == nullptr) {
        return nullptr;
    }

    static const auto game_object_t = sdk::find_type_definition("via.GameObject");
    static const auto get_transform_fn = game_object_t != nullptr ? game_object_t->get_method("get_Transform") : nullptr;

    if (get_transform_fn != nullptr) {
        if (auto transform = get_transform_fn->call<::RETransform*>(sdk::get_thread_context(), obj); transform != nullptr) {
            return transform;
        }
    }

    return obj->transform;
}
}
