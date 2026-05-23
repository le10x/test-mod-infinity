#include <Geode/Geode.hpp>
#include <Geode/modify/GameObject.hpp>

using namespace geode::prelude;

class $modify(GameObject) {
    // Interceptamos la inicialización de cualquier objeto que se crea en el juego
    bool init(int objectID) {
        // Primero dejamos que el objeto se inicialice de forma completamente normal
        if (!GameObject::init(objectID)) return false;

        // Si el objeto que se está creando es una User Coin (1329)
        if (objectID == 1329) {
            // Desactivamos la propiedad interna que le dice al juego 
            // "soy un objeto con límite estricto de cantidad en el editor"
            this->m_isIsolate = false; 
        }

        return true;
    }
};
