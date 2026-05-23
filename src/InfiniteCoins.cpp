#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

using namespace geode::prelude;

// Hookeamos la clase del Editor de Niveles
class $modify(LevelEditorLayer) {

    // Modificamos la función encargada de contar las monedas puestas
    int getCoinCount(int coinType) {
        // coinType identifica si es Secret Coin (moneda dorada) o User Coin (moneda plateada)
        
        // Al retornar siempre 0, el editor "piensa" que no has colocado ninguna moneda,
        // permitiéndote colocar tantas monedas como desees de forma infinita.
        return 0; 
    }
};
