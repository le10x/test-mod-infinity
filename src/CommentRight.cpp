#include <Geode/Geode.hpp>
#include <Geode/modify/ProfilePage.hpp>

using namespace geode::prelude;

class $modify(MyProfilePage, ProfilePage) {
    bool init(int accountID, bool ownProfile) {
        if (!ProfilePage::init(accountID, ownProfile)) {
            return false;
        }

        // 1. Encontrar los elementos usando sus IDs de Geode
        auto commentBtn = this->m_mainLayer->getChildByID("comment-button");
        auto leftMenu = this->m_mainLayer->getChildByID("left-menu");
        auto rightMenu = this->m_mainLayer->getChildByID("right-menu");

        if (commentBtn && rightMenu) {
            // 2. Romper la sincronización con el menú izquierdo
            commentBtn->removeFromParentAndCleanup(false);

            // 3. Insertar el botón en el menú de la derecha
            rightMenu->addChild(commentBtn);

            // 4. Forzar la actualización física de ambos menús para aplicar los cambios
            if (leftMenu) {
                leftMenu->updateLayout();
            }
            rightMenu->updateLayout();
        }

        return true;
    }
};
