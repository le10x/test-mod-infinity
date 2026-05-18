#include <Geode/Geode.hpp>
#include <Geode/modify/LikeItemLayer.hpp>

using namespace geode::prelude;

class $modify(MyLikeItemLayer, LikeItemLayer) {
    // Interceptamos la inicialización del recuadro de Likes
    bool init(LikeItemType type, int id, bool extra) {
        
        // Verificamos si el interruptor 'enable-likes' está encendido en mod.json
        bool isEnabled = Mod::get()->getSettingValue<bool>("enable-likes");

        if (isEnabled) {
            // Engañamos al juego forzando que 'extra' (que controla si ya diste voto) sea siempre false.
            // Esto desbloquea el botón e impide que el juego sepa que ya habías votado.
            extra = false;
        }

        // Llamamos al inicializador original usando la sintaxis clásica de Geode
        return LikeItemLayer::init(type, id, extra);
    }
};
