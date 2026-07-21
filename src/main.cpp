#include <Geode/Geode.hpp>
#include <string>

using namespace geode::prelude;

// Engañamos al compilador haciendo el hook sobre FLAlertLayer (clase base de alertas).
// Esto evita que busque el archivo UploadCommentPopup.hpp que no existe en Android.
class $modify(FLAlertLayer) {
    void onPost(CCObject* sender) {
        // 1. Verificamos si la ventana actual en pantalla es el Popup de comentarios
        if (std::string(typeid(*this).name()).find("UploadCommentPopup") != std::string::npos) {
            // 2. Buscamos el cuadro de texto escaneando la interfaz
            auto inputField = this->findFirstChildByType<CCTextInputNode>(this);
            
            if (inputField) {
                std::string commentText = inputField->getString();
                
                // 3. Detectamos si el usuario ingresó el comando !percent
                if (commentText.rfind("!percent", 0) == 0) {
                    try {
                        int customPercent = std::stoi(commentText.substr(9));
                        
                        if (customPercent >= 0 && customPercent <= 100) {
                            // Modificamos la etiqueta visual del porcentaje
                            if (auto label = this->findFirstChildByType<CCLabelBMFont>(this)) {
                                label->setString(fmt::format("{}%", customPercent).c_str());
                            }
                            
                            // Accedemos de forma segura al campo de porcentaje mediante punteros genéricos
                            int* percentPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x1F8);
                            if (percentPtr) {
                                *percentPtr = customPercent;
                            }
                        }
                    } catch (...) {
                        // Manejo de errores por si el usuario ingresa texto no numérico
                    }
                    
                    // Limpiamos la caja para camuflar el comando
                    inputField->setString("");
                    return; // Importante: Salimos tras ejecutar nuestro comando para evitar duplicidades
                }
            }
        }
        
        // Llamamos al método original si no se ejecutó nuestro comando
        FLAlertLayer::onPost(sender);
    }
};
