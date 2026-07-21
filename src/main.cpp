#include <Geode/Geode.hpp>
#include <Geode/modify/UploadCommentPopup.hpp>
#include <string>
#include <sstream>

using namespace geode::prelude;

class $modify(MyPercentMod, UploadCommentPopup) {
    void onPost(CCObject* sender) {
        // 1. Buscamos el cuadro de texto escaneando la interfaz
        auto inputField = this->findFirstChildByType<CCTextInputNode>(this);
        if (!inputField) {
            UploadCommentPopup::onPost(sender);
            return;
        }

        std::string commentText = inputField->getString();

        // 2. Buscamos el comando "!percent " estrictamente al inicio
        if (commentText.rfind("!percent ", 0) == 0) {
            try {
                int customPercent = std::stoi(commentText.substr(9));
                
                if (customPercent >= 0 && customPercent <= 100) {
                    // Forzamos el valor numérico en la variable del nivel
                    if (this->m_level) {
                        this->m_level->m_orbCompletion = customPercent; // O m_percentage (varía según la versión de GD)
                    }

                    // Actualizamos el texto del comentario para que contenga el %
                    inputField->setString(fmt::format("{}%", customPercent).c_str());
                    
                    // Dejamos que el flujo normal envíe el comentario ahora que fue modificado
                    UploadCommentPopup::onPost(sender);
                    return;
                }
            } catch (...) {
                // Si escriben mal el número, el mod no se rompe
            }
            
            // Si el comando no es válido (por ejemplo, número mayor a 100), borramos el cuadro de texto
            inputField->setString("");
            return;
        }

        // Si no es un comando, enviamos el comentario con total normalidad
        UploadCommentPopup::onPost(sender);
    }
};
