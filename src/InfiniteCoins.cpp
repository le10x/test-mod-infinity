#include <Geode/Geode.hpp>
#include <Geode/modify/GameObject.hpp>

using namespace geode::prelude;

class $modify(GameObject) {
    // Interceptamos la creación del objeto mediante su ID clave
    static GameObject* createWithKey(int objectID) {
        // Llamamos a la creación normal del objeto
        auto obj = GameObject::createWithKey(objectID);
        
        // Si el objeto creado es una User Coin (1329) y se creó correctamente
        if (obj && objectID == 1329) {
            // Modificamos su propiedad de tipo de objeto en el editor.
            // Al cambiar temporalmente su tipo interno de 'UserCoin' a un tipo genérico o interactivo común,
            // el motor del editor deja de rastrearlo en su lista de "objetos límite" ignorando el contador.
            obj->m_objectType = GameObjectType::Decoration; 
        }
        
        return obj;
    }
};
