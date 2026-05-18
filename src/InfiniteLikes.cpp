#include <Geode/Geode.hpp>
#include <Geode/modify/LikeItemLayer.hpp>

using namespace geode::prelude;

class $modify(MyLikeItemLayer, LikeItemLayer) {
    // Interceptamos cuando la ventana de votación se dibuja en pantalla
    bool init(LikeItemType type, int id, bool extra) {
        
        bool isEnabled = Mod::get()->getSettingValue<bool>("enable-likes");

        // Al forzar que 'extra' sea false, el juego asume que NO has votado.
        // Al forzar que 'type' sea un tipo genérico externo, se eliminan bloqueos de autoría.
        if (isEnabled) {
            extra = false; 
        }

        return LikeItemLayer::init(type, id, extra);
    }
};
