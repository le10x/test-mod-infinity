#include <Geode/Geode.hpp>

using namespace geode::prelude;

//I'm gonna leave comments in here because I like to
//At least this code doesn't have any catgirls in it unlike my other project :3
// Why did I leave this comment here lol
// Also this code is interesting but like it works
#include <Geode/modify/PauseLayer.hpp>
class $modify(LDPauseLayer, PauseLayer) {
	void customSetup() {
		PauseLayer::customSetup();
		auto rightButtonMenu = this->getChildByID("right-button-menu");
		auto spr = CCSprite::createWithSpriteFrameName("GJ_levelLeaderboardBtn_001.png");
		spr->setScale(0.65f);
		auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(LDPauseLayer::onLeaderboard));
		rightButtonMenu->addChild(btn);
		btn->setID("leaderboard-button"_spr);
		rightButtonMenu->updateLayout();
	}
	
	void onLeaderboard(CCObject* sender) {
		if (PlayLayer::get()) { //Check if there is a PlayLayer
			auto level = PlayLayer::get()->m_level;
			auto levelLeaderboardType = static_cast<LevelLeaderboardType>(GameManager::get()->getIntGameVariable("0098"));
			auto levelLeaderboardMode = static_cast<LevelLeaderboardMode>(GameManager::get()->getIntGameVariable("0164"));
			LevelLeaderboard::create(level, levelLeaderboardType, levelLeaderboardMode)->show();
			return;
		}
		FLAlertLayer::create("Uh Oh", "No PlayLayer found, you sure you in a level?", "OK")->show();
	}
};

#include <Geode/modify/LevelLeaderboard.hpp>
class $modify(LDLevelLeaderboard, LevelLeaderboard) {
	bool init(GJGameLevel* p0, LevelLeaderboardType p1, LevelLeaderboardMode p2) {
		if (!LevelLeaderboard::init(p0, p1, p2)) return false;

		//Makes sure its above everything if its created without the show function (I'm looking at you betterinfo)
		this->setZOrder(std::max(0x69, CCDirector::sharedDirector()->getRunningScene()->getHighestChildZ()));

		return true;
	}
};
