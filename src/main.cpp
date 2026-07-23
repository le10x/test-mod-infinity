#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>

using namespace geode::prelude;

// Modificamos GameManager de forma segura para ARM (Android)
class $modify(GameManager) {

    // Desbloquea cubos, naves, ufo, wave, ball, swing y jet
    bool isIconUnlocked(int iconID, IconType iconType) {
        return true;
    }

    // Desbloquea colores primarios y secundarios
    bool isColorUnlocked(int colorID, UnlockType unlockType) {
        return true;
    }

    // Desbloquea estelas (trails), efectos de muerte y barcos especiales
    bool hasItemUnlocked(UnlockType unlockType, int itemID) {
        return true;
    }
};
