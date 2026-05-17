#include <Geode/Geode.hpp>
#include <Geode/modify/CommentCell.hpp>
#include <Geode/modify/InfoLayer.hpp>

using namespace geode::prelude;

class $modify(MyCommentCell, CommentCell) {
    void onLike(cocos2d::CCObject* sender) {
        // Verificamos si el interruptor 'enable-likes' está encendido
        bool isEnabled = Mod::get()->getSettingValue<bool>("enable-likes");

        if (isEnabled) {
            auto gsm = GameStatsManager::sharedState();
            if (gsm && m_comment) {
                // Borramos el registro local para que el juego nos deje presionar el botón de nuevo
                gsm->m_likedItems->removeObjectForKey(std::to_string(m_comment->m_commentID));
            }
        }

        CommentCell::onLike(sender);
    }
};

class $modify(MyInfoLayer, InfoLayer) {
    void onLike(cocos2d::CCObject* sender) {
        bool isEnabled = Mod::get()->getSettingValue<bool>("enable-likes");

        if (isEnabled) {
            auto gsm = GameStatsManager::sharedState();
            if (gsm && m_comment) {
                gsm->m_likedItems->removeObjectForKey(std::to_string(m_comment->m_commentID));
            }
        }

        InfoLayer::onLike(sender);
    }
};
