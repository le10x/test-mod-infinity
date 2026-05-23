#include <Geode/Geode.hpp>
#include <Geode/modify/ObjectManager.hpp>

using namespace geode::prelude;

class $modify(ObjectManager) {
    // Interceptamos la función que le dice al juego si un ID tiene límites estrictos de cantidad
    bool isPersistentObject(int objectID) {
        // En Geometry Dash, las monedas y los Start Pos son "Persistent" o aislados.
        // Si el juego pregunta si la User Coin (1329) es un objeto restringido, le decimos que NO.
        if (objectID == 1329) {
            return false; 
        }

        // Para cualquier otro objeto, dejamos que el juego use sus límites nativos
        return ObjectManager::isPersistentObject(objectID);
    }
};
