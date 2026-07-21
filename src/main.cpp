#include <Geode/Geode.hpp>
#include <Geode/modify/LeaderboardLayer.hpp>

using namespace geode::prelude;

class $modify(MyLeaderboardLayer, LeaderboardLayer) {
    
    struct Fields {
        bool m_isPlatformer = false;
    };

    bool init(LeaderboardState state) {
        if (!LeaderboardLayer::init(state)) return false;

        CCMenu* sideMenu = nullptr;

        // Búsqueda manual sin depender de Node IDs externos
        // Recorremos los nodos hijos para dar con el CCMenu contenedor de botones (Top, Week, Friends)
        auto children = this->getChildren();
        if (children) {
            for (int i = 0; i < children->count(); ++i) {
                auto child = GameObjCast<CCMenu*>(children->objectAtIndex(i));
                if (child) {
                    // Verificación de seguridad por coordenadas: RobTop posiciona este menú a la derecha
                    if (child->getPositionX() > 200.0f) { 
                        sideMenu = child;
                        break;
                    }
                }
            }
        }

        // Si no se encuentra de forma segura, creamos un menú flotante alternativo
        if (!sideMenu) {
            sideMenu = CCMenu::create();
            sideMenu->setPosition({ CCDirector::sharedDirector()->getWinSize().width - 40.0f, 150.0f });
            this->addChild(sideMenu);
        }

        // Crear interfaz estética del botón independiente
        auto buttonSprite = ButtonSprite::create("Classic", "goldFont.fnt", "GJ_button_01.png", 0.5f);
        
        auto toggleBtn = CCMenuItemSpriteExtra::create(
            buttonSprite,
            this,
            menu_selector(MyLeaderboardLayer::onToggleLeaderboardMode)
        );
        
        toggleBtn->setID("mode-toggle-button"_spr);
        
        // Inserción en el menú físico
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

        // Modificación del GameManager global de RobTop en GD 2.2081
        auto gameManager = GameManager::sharedState();
        if (gameManager) {
            // Nota: Este booleano define el filtrado interno del cliente antes de enviar la petición HTTP
            // gameManager->m_isPlatformer = m_fields->m_isPlatformer;
        }

        // Forzar actualización visual limpiando y recargando la lista
        // this->setupLeaderboard(m_state);
    }
};
