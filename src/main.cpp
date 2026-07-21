#include <Geode/Geode.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>

using namespace geode::prelude;

class $modify(MyLeaderboardLayer, LeaderboardsLayer) {
    
    struct Fields {
        bool m_isPlatformer = false;
    };

    // Ajustado a los dos argumentos reales definidos en Geode: type y stat
    bool init(LeaderboardType type, LeaderboardStat stat) {
        if (!LeaderboardsLayer::init(type, stat)) return false;

        CCMenu* sideMenu = nullptr;

        // Búsqueda manual usando typeinfo_cast (el estándar correcto en Geode 5.x)
        auto children = this->getChildren();
        if (children) {
            for (int i = 0; i < children->count(); ++i) {
                auto child = typeinfo_cast<CCMenu*>(children->objectAtIndex(i));
                if (child) {
                    // Verificación física de posición en pantalla (menú derecho)
                    if (child->getPositionX() > 200.0f) { 
                        sideMenu = child;
                        break;
                    }
                }
            }
        }

        // Si falla la búsqueda, crea un menú de respaldo
        if (!sideMenu) {
            sideMenu = CCMenu::create();
            sideMenu->setPosition({ CCDirector::sharedDirector()->getWinSize().width - 40.0f, 150.0f });
            this->addChild(sideMenu);
        }

        // Crear la apariencia e interactividad del botón
        auto buttonSprite = ButtonSprite::create("Classic", "goldFont.fnt", "GJ_button_01.png", 0.5f);
        
        auto toggleBtn = CCMenuItemSpriteExtra::create(
            buttonSprite,
            this,
            menu_selector(MyLeaderboardLayer::onToggleLeaderboardMode)
        );
        
        toggleBtn->setID("mode-toggle-button"_spr);
        
        // Adjuntar al contenedor físico de marcadores
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

        // Nota: Para recargar los puntajes visuales, RobTop refresca llamando a setupLeaderboard
        // pasando el tipo y la estadística activa de la capa.
    }
};
