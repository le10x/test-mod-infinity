#include <Geode/Geode.hpp>
// Importamos los archivos maestros que contienen todas las clases de Geometry Dash
#include <Geode/binding/Classes.hpp>
#include <Geode/modify/Classes.hpp>
#include <string>

using namespace geode::prelude;

// Modificamos la clase usando el catálogo maestro ya cargado
class $modify(MyPercentMod, UploadCommentPopup) {
    void onPost(CCObject* sender) {
        // 1. Verificamos de forma segura que el cuadro de texto exista en esta versión
        if (!m_commentTextInput) {
            UploadCommentPopup::onPost(sender);
            return;
        }
        
        std::string commentText = m_commentTextInput->getString();

        // 2. Buscamos el comando "!percent " estrictamente al inicio
        if (commentText.rfind("!percent ", 0) == 0) {
            try {
                // Extraemos el número que sigue al comando
                int customPercent = std::stoi(commentText.substr(9));

                if (customPercent >= 0 && customPercent <= 100) {
                    m_percent = customPercent;
                    
                    // Actualizamos visualmente la etiqueta del porcentaje en pantalla
                    if (m_percentLabel) {
                        m_percentLabel->setString(fmt::format("{}%", customPercent).c_str());
                    }
                }
            } catch (...) {}

            // Limpiamos el cuadro para evitar que el comando se envíe como texto público
            m_commentTextInput->setString("");
            return; 
        }

        // Si no se inicia con el comando, procesa el comentario de manera normal
        UploadCommentPopup::onPost(sender);
    }
};
