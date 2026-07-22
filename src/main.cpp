#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/LevelLeaderboard.hpp>

using namespace geode::prelude;

class $modify(LDPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        CCMenu* targetMenu = nullptr;

        // Buscamos los menús secundarios del menú de pausa
        if (auto children = this->getChildren()) {
            for (int i = 0; i < children->count(); ++i) {
                if (auto child = typeinfo_cast<CCMenu*>(children->objectAtIndex(i))) {
                    float xPos = child->getPositionX();
                    
                    // Buscamos el menú del lado izquierdo (generalmente xPos < 100.0f)
                    if (xPos < 100.0f) {
                        targetMenu = child;
                        break;
                    }
                }
            }
        }

        // Si no se encuentra el menú izquierdo de forma estricta, usamos el menú derecho o central como respaldo
        if (!targetMenu) {
            targetMenu = this->getChildByID("left-button-menu");
            if (!targetMenu) targetMenu = this->getChildByID("right-button-menu");
        }

        if (targetMenu) {
            if (auto spr = CCSprite::createWithSpriteFrameName("GJ_levelLeaderboardBtn_001.png")) {
                spr->setScale(0.65f);
                
                // Tinte azul para identificar que es el marcador de plataforma
                spr->setColor({0, 128, 255}); 

                if (auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(LDPauseLayer::onLeaderboard))) {
                    targetMenu->addChild(btn);
                    targetMenu->updateLayout();
                }
            }
        }
    }
    
    void onLeaderboard(CCObject* sender) {
        if (auto playLayer = PlayLayer::get()) {
            if (playLayer->m_level) {
                auto gm = GameManager::get();
                auto type = static_cast<LevelLeaderboardType>(gm->getIntGameVariable("0098"));
                auto mode = static_cast<LevelLeaderboardMode>(gm->getIntGameVariable("0164"));
                
                // Guardamos el estado original para no alterar la física del nivel al reanudar
                bool originalMode = playLayer->m_level->m_isPlatformer;

                // Engañamos al juego forzando el modo plataforma antes de generar el menú
                playLayer->m_level->m_isPlatformer = true;

                auto leaderboard = LevelLeaderboard::create(playLayer->m_level, type, mode);
                if (leaderboard) {
                    leaderboard->show();
                }

                // Restauramos el tipo de nivel original inmediatamente
                playLayer->m_level->m_isPlatformer = originalMode;
                return;
            }
        }
        FLAlertLayer::create("Uh Oh", "No PlayLayer found, you sure you in a level?", "OK")->show();
    }
};

class $modify(LDLevelLeaderboard, LevelLeaderboard) {
    bool init(GJGameLevel* level, LevelLeaderboardType type, LevelLeaderboardMode mode) {
        if (!LevelLeaderboard::init(level, type, mode)) return false;

        // Se mantiene el renderizado prioritario sobre la interfaz de pausa
        if (auto scene = CCDirector::sharedDirector()->getRunningScene()) {
            this->setZOrder(std::max(105, scene->getHighestChildZ()));
        }
        return true;
    }
};
