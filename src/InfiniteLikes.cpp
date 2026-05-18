#include <Geode/Geode.hpp>
#include <Geode/modify/GameStatsManager.hpp>

using namespace geode::prelude;

class $modify(MyGameStatsManager, GameStatsManager) {
    
    bool hasLikedItem(LikeItemType type, int id, bool extra) {
        
        // Verificamos si nuestro interruptor en mod.json está encendido
        bool isEnabled = Mod::get()->getSettingValue<bool>("enable-likes");

        if (isEnabled) {
            // Engañamos al juego devolviendo siempre false para que crea que nunca has votado por el elemento
            return false;
        }

        // Usamos std::move(original) para llamar de forma segura al comportamiento base de Geode
        return std::move(original)(type, id, extra);
    }
};
