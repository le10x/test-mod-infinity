#include <Geode/Geode.hpp>
#include <Geode/modify/GameStatsManager.hpp>

using namespace geode::prelude;

// Modificamos directamente el gestor de estadísticas del juego
class $modify(MyGameStatsManager, GameStatsManager) {
    
    // Interceptamos la función que comprueba si ya diste like a un elemento
    bool hasLikedItem(LikeItemType type, int id, bool extra) {
        
        // Verificamos si nuestro interruptor en mod.json está encendido
        bool isEnabled = Mod::get()->getSettingValue<bool>("enable-likes");

        if (isEnabled) {
            // Engañamos al juego devolviendo SIEMPRE false.
            // Para el juego, tú NUNCA le has dado like a este comentario.
            return false;
        }

        // Si el mod está apagado, se comporta de forma normal
        return GameStatsManager::hasLikedItem(type, id, extra);
    }
};
