#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

using namespace geode::prelude;

class $modify(LevelEditorLayer) {
    // Interceptamos la validación lógica de colocación de objetos en el mapa
    bool canPlaceObject(GameObject* object) {
        // Si el juego está verificando una User Coin, saltamos la comprobación del contador
        if (object && object->m_objectID == 1329) {
            return true; // Le aseguramos al motor que siempre es válido colocarla
        }
        
        // Para cualquier otro objeto, dejamos que el juego use sus reglas normales
        return LevelEditorLayer::canPlaceObject(object);
    }
};
