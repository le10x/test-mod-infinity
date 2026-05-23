#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Usamos el ciclo de inicialización del Mod en lugar de hooks convencionales
$execute {
    // Buscamos la dirección física en el binario de Android de forma segura a través de Geode.
    // Buscamos la dirección del método encargado de bloquear la colocación por límites.
    auto address = base::get() + geode::modifier::Resolve<int(int)>::address(&LevelEditorLayer::getLimitsForObject);

    // Dependiendo de tu versión exacta de Geometry Dash 2.2 en Android:
    // Reemplazamos la instrucción ensambladora original de la comparación por un retorno forzado.
    // 0x01, 0x00, 0xA0, 0xE3, 0x1E, 0xFF, 0x2F, 0xE1 representan "mov r0, #1" y "bx lr" en arquitectura ARM (retorna true siempre)
    
    uint8_t armPatch[] = { 0x01, 0x00, 0xA0, 0xE3, 0x1E, 0xFF, 0x2F, 0xE1 };
    
    // Aplicamos el parche de memoria directamente sobre los bytes de la función en Android
    auto result = Mod::get()->patch(reinterpret_cast<void*>(address), armPatch);
    
    if (result) {
        log::info("¡Bypass binario inyectado con éxito en la RAM de Android!");
    } else {
        log::error("Error al aplicar el parche de memoria.");
    }
    }
