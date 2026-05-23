#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(EditorUI) {
    // Interceptamos la función que valida si se puede construir el objeto de un botón
    bool canBuildObjectForButton(EditButton* button) {
        // Validamos que el botón exista y tenga un objeto asignado
        if (button && button->getObjID() == 1329) {
            
            // Obtenemos el total de User Coins directamente desde la variable del nivel actual
            if (auto levelEditor = LevelEditorLayer::get()) {
                if (auto level = levelEditor->m_level) {
                    // m_coins es la variable nativa de GD que almacena cuántas monedas tiene el nivel
                    int currentCoins = level->m_coins;
                    
                    // Si tienes menos de 99, te deja colocarla directamente
                    if (currentCoins < 99) {
                        return true;
                    }
                }
            }
        }
        
        // Si no es una User Coin (1329), ejecuta la lógica por defecto del juego
        return EditorUI::canBuildObjectForButton(button);
    }
};
