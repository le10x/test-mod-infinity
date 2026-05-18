#include <Geode/Geode.hpp>
#include <Geode/modify/GameLevelManager.hpp>

using namespace geode::prelude;

class $modify(MyGameLevelManager, GameLevelManager) {
    void uploadComment(std::string comment, CommentKeyType keyType, int levelID, int percent) {
        
        bool isEnabled = Mod::get()->getSettingValue<bool>("enable-custom-percent");
        int fakePercent = Mod::get()->getSettingValue<int>("custom-percent-value");

        if (isEnabled) {
            // Aquí se asignará el valor falso (incluso si es 999)
            percent = fakePercent;
        }

        GameLevelManager::uploadComment(comment, keyType, levelID, percent);
    }
};
