#include <Geode/Geode.hpp>
#include <Geode/modify/LikeItemLayer.hpp>

using namespace geode::prelude;

class $modify(MyLikeItemLayer, LikeItemLayer) {
    // Interceptamos el momento exacto en que se va a enviar el voto al servidor
    void triggerLike(bool isLike) {
        
        bool isEnabled = Mod::get()->getSettingValue<bool>("enable-likes");

        if (isEnabled) {
            auto gsm = GameStatsManager::sharedState();
            // Verificamos que tengamos acceso a los datos y que la ventana tenga un ID de comentario válido
            if (gsm && m_itemID != 0) {
                // Buscamos el diccionario nativo de Cocos2d donde se guardan los elementos votados
                auto likedDict = gsm->m_likedItems;
                if (likedDict) {
                    // Convertimos el ID del comentario a texto
                    std::string itemKey = std::to_string(m_itemID);
                    // Borramos el registro para que el juego olvide que ya votaste por él
                    likedDict->removeObjectForKey(itemKey.c_str());
                }
            }
        }

        // Llamamos a la función original para que envíe el paquete HTTP al servidor
        LikeItemLayer::triggerLike(isLike);
    }
};
