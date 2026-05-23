#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(EditorUI) {
    bool canPlaceObject(int objectID) {
        // Filtrar estrictamente por el ID 1329 (User Coin)
        if (objectID == 1329) {
            // Obtenemos la instancia activa del editor
            if (auto editorLoop = LevelEditorLayer::get()) {
                // El tipo 2 corresponde a las User Coins en Geometry Dash
                int currentCoins = editorLoop->getCoinCount(2);
                
                // Rompemos el límite permitiendo hasta 99 monedas plateadas
                if (currentCoins < 99) {
                    return true; 
                }
            }
        }
        
        // Si es cualquier otro objeto (incluyendo la Secret Coin 142), 
        // se ejecuta la validación original del juego.
        return EditorUI::canPlaceObject(objectID);
    }
};
