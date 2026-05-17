#include <Geode/Geode.hpp>
#include <Geode/modify/LikeItemLayer.hpp>

using namespace geode::prelude;

class $modify(MyLikeItemLayer, LikeItemLayer) {
    // Interceptamos el método nativo que se ejecuta al presionar el botón físico de Like en la interfaz
    void onLike(cocos2d::CCObject* sender) {
        
        // Verificamos si la configuración de likes infinitos está habilitada
        bool isEnabled = Mod::get()->getSettingValue<bool>("enable-likes");

        if (isEnabled) {
            // Ejecutamos triggerLike directamente de forma infinita.
            // Al llamarlo directamente saltándonos la comprobación nativa del botón de 'onLike',
            // enviamos el paquete HTTP al servidor sin que el juego desactive el botón localmente.
            this->triggerLike(true);
            return;
        }

        // Si el mod está desactivado, dejamos que el juego actúe de manera normal
        LikeItemLayer::onLike(sender);
    }
};
