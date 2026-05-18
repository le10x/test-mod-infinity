#include <Geode/Geode.hpp>
#include <Geode/modify/ProfilePage.hpp>

using namespace geode::prelude;

class $modify(MyProfilePage, ProfilePage) {
    bool init(int accountID, bool ownProfile) {
        if (!ProfilePage::init(accountID, ownProfile)) {
            return false;
        }

        // 1. Buscar el botón original y el menú derecho del perfil
        auto commentBtn = this->m_mainLayer->getChildByID("comment-button");
        auto rightMenu = this->m_mainLayer->getChildByID("right-menu");

        // 2. Verificar que ambos elementos existan
        if (commentBtn && rightMenu) {
            
            // 3. Quitar el botón de su posición actual sin destruirlo
            // 'false' significa "no lo borres de la memoria, solo quítalo de la pantalla"
            commentBtn->removeFromParentAndCleanup(false);

            // 4. Añadir el botón existente al menú de la derecha
            rightMenu->addChild(commentBtn);

            // 5. Ordenar al menú de la derecha que se reorganice solo
            // Esto acomoda el botón automáticamente en la fila/columna derecha
            rightMenu->updateLayout();
        }

        return true;
    }
};
