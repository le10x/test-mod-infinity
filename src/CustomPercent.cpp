#include <Geode/Geode.hpp>
#include <Geode/modify/GameLevelManager.hpp>

using namespace geode::prelude;

class $modify(MyGameLevelManager, GameLevelManager) {
    // Cambiamos 'CommentKeyType' por 'CommentType' para coincidir exactamente con el binding
    void uploadComment(std::string comment, CommentType keyType, int levelID, int percent) {
        
        bool isEnabled = Mod::get()->getSettingValue<bool>("enable-custom-percent");
        int fakePercent = Mod::get()->getSettingValue<int>("custom-percent-value");

        if (isEnabled) {
            // Asignamos tu porcentaje personalizado (acepta hasta 999)
            percent = fakePercent;
        }

        // Llamamos a la función original con el tipo de dato corregido
        GameLevelManager::uploadComment(comment, keyType, levelID, percent);
    }
};
