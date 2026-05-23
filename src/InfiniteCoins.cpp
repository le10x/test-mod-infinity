#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(EditorUI) {
    void onCreateButton(cocos2d::CCObject* sender) {
        auto item = typeinfo_cast<CreateMenuItem*>(sender);
        auto ed = LevelEditorLayer::get();

        if (item && item->m_objectID == 1329 && ed && ed->m_level) {
            int originalCoins = ed->m_level->m_coins;
            
            // Bypass temporal: simula 0 monedas si hay menos de 99
            if (originalCoins < 99) ed->m_level->m_coins = 0;
            
            EditorUI::onCreateButton(sender);
            ed->m_level->m_coins = originalCoins;
            return;
        }
        EditorUI::onCreateButton(sender);
    }
};
