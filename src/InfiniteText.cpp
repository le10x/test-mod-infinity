#include <Geode/Geode.hpp>
#include <Geode/modify/CCTextInputNode.hpp>

using namespace geode::prelude;

class $modify(MyTextInputNode, CCTextInputNode) {
    bool onTextFieldInsertText(cocos2d::CCTextFieldTTF* sender, char const* text, int length, cocos2d::enumKeyCodes keyCodes) {
        
        CCTextInputNode::onTextFieldInsertText(sender, text, length, keyCodes);
 
        return false;
    }
};
