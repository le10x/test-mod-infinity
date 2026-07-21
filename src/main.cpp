#include <Geode/Geode.hpp>
#include <string>

using namespace geode::prelude;

// Modificamos la clase directamente utilizando el namespace implícito de Geode
class $modify(MyPercentMod, UploadCommentPopup) {
    void onPost(CCObject* sender) {
        // 1. Verificamos de manera segura que la caja de texto exista
        if (!m_commentTextInput) {
            UploadCommentPopup::onPost(sender);
            return;
        }
        
        std::string commentText = m_commentTextInput->getString();

        // 2. Buscamos el comando "!percent " al inicio
        if (commentText.rfind("!percent ", 0) == 0) {
            try {
                // Extraemos el número correspondiente
                int customPercent = std::stoi(commentText.substr(9));

                if (customPercent >= 0 && customPercent <= 100) {
                    m_percent = customPercent;
                    
                    // Modificamos el valor numérico visible si existe el texto
                    if (m_percentLabel) {
                        m_percentLabel->setString(fmt::format("{}%", customPercent).c_str());
                    }
                }
            } catch (...) {}

            // Limpiamos el cuadro para evitar que se publique el comando en el servidor
            m_commentTextInput->setString("");
            return; 
        }

        // Si no se introduce el comando, procesamos la acción con normalidad
        UploadCommentPopup::onPost(sender);
    }
};
