#include <Geode/Geode.hpp>
#include <Geode/modify/LikeItemLayer.hpp>

using namespace geode::prelude;

class $modify(MyLikeItemLayer, LikeItemLayer) {
    // Interceptamos el método nativo que se ejecuta al presionar el botón de Like o Dislike
    void onLikeItem(cocos2d::CCObject* sender) {
        
        // Verificamos si el interruptor 'enable-likes' está encendido en mod.json
        bool isEnabled = Mod::get()->getSettingValue<bool>("enable-likes");

        if (isEnabled) {
            // El juego guarda el tipo de objeto (2 es para comentarios) y su ID dentro de la clase LikeItemLayer
            // m_itemType == 2 significa que estamos interactuando con un comentario
            if (m_itemType == 2) {
                auto gsm = GameStatsManager::sharedState();
                if (gsm) {
                    // Borramos el ID del comentario actual de la lista de elementos ya votados en esta sesión
                    gsm->m_likedItems->removeObjectForKey(std::to_string(m_itemID));
                }
            }
        }

        // Ejecutamos la función original para enviar el voto al servidor
        LikeItemLayer::onLikeItem(sender);
    }
};
