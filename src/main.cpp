#include <Geode/Geode.hpp>
// Corrección del header: se añade la 's' a LeaderboardsLayer
#include <Geode/modify/LeaderboardsLayer.hpp>

using namespace geode::prelude;

// Corrección de la macro modificadora: se cambia LeaderboardLayer por LeaderboardsLayer
class $modify(MyLeaderboardLayer, LeaderboardsLayer) {
    
    struct Fields {
        bool m_isPlatformer = false;
    };

    bool init(LeaderboardState state) {
        if (!LeaderboardsLayer::init(state)) return false;

        CCMenu* sideMenu = nullptr;

        // Búsqueda manual iterando por los nodos hijos del contenedor
        auto children = this->getChildren();
        if (children) {
            for (int i = 0; i < children->count(); ++i) {
                auto child = GameObjCast<CCMenu*>(children->objectAtIndex(i));
                if (child) {
                    // RobTop posiciona este menú lateral hacia la derecha en la pantalla
                    if (child->getPositionX() > 200.0f) { 
                        sideMenu = child;
                        break;
                    }
                }
            }
        }

        // Menú de respaldo en caso de no encontrarse dinámicamente
        if (!sideMenu) {
            sideMenu = CCMenu::create();
            sideMenu->setPosition({ CCDirector::sharedDirector()->getWinSize().width - 40.0f, 150.0f });
            this->addChild(sideMenu);
        }

        // Creación del sprite base del botón alternador
        auto buttonSprite = ButtonSprite::create("Classic", "goldFont.fnt", "GJ_button_01.png", 0.5f);
        
        auto toggleBtn = CCMenuItemSpriteExtra::create(
            buttonSprite,
            this,
            menu_selector(MyLeaderboardLayer::onToggleLeaderboardMode)
        );
        
        toggleBtn->setID("mode-toggle-button"_spr);
        
        // Adjuntar e indicar el rediseño del layout
        sideMenu->addChild(toggleBtn);
        sideMenu->updateLayout();

        return true;
    }

    void onToggleLeaderboardMode(CCObject* sender) {
        m_fields->m_isPlatformer = !m_fields->m_isPlatformer;

        auto btn = static_cast<CCMenuItemSpriteExtra*>(sender);
        auto spr = static_cast<ButtonSprite*>(btn->getNormalImage());
        
        if (m_fields->m_isPlatformer) {
            spr->setString("Plat");
        } else {
            spr->setString("Classic");
        }

        // Espacio reservado para invocar la recarga de datos en GD 2.2081 de forma manual
        // El método de actualización interna de RobTop suele requerir el estado actual
        // this->setupLeaderboard(m_state);
    }
};
