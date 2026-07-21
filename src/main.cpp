#include <Geode/Geode.hpp>
// Incluimos explícitamente el binding y el modify de la clase
#include <Geode/binding/UploadCommentPopup.hpp>
#include <Geode/modify/UploadCommentPopup.hpp>
#include <string>

using namespace geode::prelude;

// Usamos la macro con la estructura correcta para Geode v3+
class $modify(MyPercentMod, UploadCommentPopup) {
    void onPost(CCObject* sender) {
        // 1. Obtenemos el texto del cuadro de comentarios
        // Usamos la variable m_commentTextInput (nombre exacto en la estructura de GD 2.2)
        if (!m_commentTextInput) {
            UploadCommentPopup::onPost(sender);
            return;
        }
        
        std::string commentText = m_commentTextInput->getString();

        // 2. Buscamos el comando "!percent " estrictamente al inicio
        if (commentText.rfind("!percent ", 0) == 0) {
            try {
                int customPercent = std::stoi(commentText.substr(9));

                if (customPercent >= 0 && customPercent <= 100) {
                    // Forzamos el porcentaje interno
                    m_percent = customPercent;
                    
                    // Modificamos el texto visual en pantalla si existe la etiqueta
                    if (m_percentLabel) {
                        m_percentLabel->setString(fmt::format("{}%", customPercent).c_str());
                    }
                }
            } catch (...) {}

            // Limpiamos el cuadro para que el comando no se envíe textualmente
            m_commentTextInput->setString("");
            return; 
        }

        // Si no se usa el comando, el juego procesa normalmente
        UploadCommentPopup::onPost(sender);
    }
};
