#include <Geode/Geode.hpp>
#include <Geode/modify/CCTextInputNode.hpp>

using namespace geode::prelude;

class $modify(MyTextInputNode, CCTextInputNode) {
    bool onTextFieldInsertText(cocos2d::CCTextFieldTTF* sender, char const* text, int length, cocos2d::enumKeyCodes keyCodes) {
        
        // Verificamos si el interruptor 'enable-text' está encendido en los ajustes
        bool isEnabled = Mod::get()->getSettingValue<bool>("enable-text");

        if (isEnabled) {
            // Pasamos los parámetros al juego original
            CCTextInputNode::onTextFieldInsertText(sender, text, length, keyCodes);
            // Retornamos false para romper el límite nativo
            return false;
        }

        // Si el mod está apagado, se comporta de manera normal de fábrica
        return CCTextInputNode::onTextFieldInsertText(sender, text, length, keyCodes);
    }
};
