#include <Geode/Geode.hpp>
#include <Geode/modify/GLMManager.hpp>

using namespace geode::prelude;

class $modify(MyGLMManager, GLMManager) {
    // Interceptamos la función nativa que empaqueta y envía el comentario al servidor
    void uploadComment(std::string comment, CommentKeyType keyType, int levelID, int percent) {
        
        // Leemos las configuraciones desde el mod.json
        bool isEnabled = Mod::get()->getSettingValue<bool>("enable-custom-percent");
        int fakePercent = Mod::get()->getSettingValue<int>("custom-percent-value");

        if (isEnabled) {
            // Reemplazamos el porcentaje real del nivel por nuestro número personalizado
            percent = fakePercent;
        }

        // Llamamos a la función original usando la sintaxis clásica compatible con tu compilador
        GLMManager::uploadComment(comment, keyType, levelID, percent);
    }
};
