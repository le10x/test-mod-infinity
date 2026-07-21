#include <Geode/Geode.hpp>
#include <string>

using namespace geode::prelude;

// Al configurar CMakeLists, Geode ya reconocerá UploadCommentPopup automáticamente
class $modify(MyPercentMod, UploadCommentPopup) {
    void onPost(CCObject* sender) {
        // 1. Verificamos que el cuadro de texto exista de forma segura
        if (!m_commentTextInput) {
            UploadCommentPopup::onPost(sender);
            return;
        }
        
        std::string commentText = m_commentTextInput->getString();

        // 2. Buscamos el comando "!percent " estrictamente al inicio
        if (commentText.rfind("!percent ", 0) == 0) {
            try {
                // Extraemos el número correspondiente después del comando
                int customPercent = std::stoi(commentText.substr(9));

                if (customPercent >= 0 && customPercent <= 100) {
                    m_percent = customPercent;
                    
                    // Modificamos visualmente el texto de la casilla vanilla
                    if (m_percentLabel) {
                        m_percentLabel->setString(fmt::format("{}%", customPercent).c_str());
                    }
                }
            } catch (...) {
                // Si hay error al procesar el número, se ignora de forma segura
            }

            // Limpiamos el cuadro para evitar enviar el comando escrito al servidor
            m_commentTextInput->setString("");
            return; 
        }

        // Si no se usó el comando, el juego procesa el comentario normal
        UploadCommentPopup::onPost(sender);
    }
};
