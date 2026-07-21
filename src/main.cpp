#include <Geode/Geode.hpp>
#include <string>

using namespace geode::prelude;

// Solo necesitas heredar de la clase usando la macro $modify
class $modify(UploadCommentPopup) {
    void onPost(CCObject* sender) {
        // 1. Obtenemos el texto del cuadro de comentarios
        std::string commentText = m_inputField->getString();

        // 2. Buscamos el comando "!percent " estrictamente al inicio (posición 0)
        if (commentText.rfind("!percent ", 0) == 0) {
            try {
                // Extraemos el número después de los 9 caracteres de "!percent "
                int customPercent = std::stoi(commentText.substr(9));

                if (customPercent >= 0 && customPercent <= 100) {
                    m_percent = customPercent;
                    
                    // Modificamos el texto visual en pantalla
                    if (m_percentLabel) {
                        m_percentLabel->setString(fmt::format("{}%", customPercent).c_str());
                    }
                }
            } catch (...) {
                // Si el usuario escribe mal el número, el mod ignora el comando de forma segura
            }

            // Limpiamos el cuadro para que el comando no se publique en los servidores
            m_inputField->setString("");
            return; 
        }

        // Si no empieza con el comando, el juego procesa el comentario de manera normal
        UploadCommentPopup::onPost(sender);
    }
};
