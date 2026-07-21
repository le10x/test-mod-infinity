#include <Geode/Geode.hpp>
#include <Geode/modify/UploadCommentPopup.hpp>
#include <string>

using namespace geode::prelude;

class $modify(MyPercentMod, UploadCommentPopup) {
    void onPost(CCObject* sender) {
        std::string commentText = m_inputField->getString();

        // 1. Buscamos el comando "!percent " en cualquier parte del texto
        size_t commandPos = commentText.find("!percent ");
        
        if (commandPos != std::string::npos) {
            try {
                // Extraemos el número que va justo después del comando
                std::string numStr = commentText.substr(commandPos + 9, 3); // Lee hasta 3 dígitos
                int customPercent = std::stoi(numStr);

                if (customPercent >= 0 && customPercent <= 100) {
                    m_percent = customPercent;
                    m_percentLabel->setString(fmt::format("{}%", customPercent).c_str());
                    
                    // Aseguramos que la casilla esté activa internamente
                    m_isPercentEnabled = true; 
                }

                // 2. BORRAMOS EL COMANDO del texto final
                // Esto quita "!percent XX" del mensaje para que nadie lo descubra
                commentText.erase(commandPos, 12); // Borra el comando y el número aproximado
                
                // Actualizamos el cuadro con el comentario limpio antes de enviar
                m_inputField->setString(commentText.c_str());

            } catch (...) {}
        }

        // El juego envía el comentario limpio con el porcentaje ya modificado
        UploadCommentPopup::onPost(sender);
    }
};
