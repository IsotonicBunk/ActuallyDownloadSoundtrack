#include <Geode/Geode.hpp>
#include <Geode/binding/SongInfoLayer.hpp>

using namespace geode::prelude;

#include <Geode/modify/SongInfoLayer.hpp>

class $modify(MySongInfoLayer, SongInfoLayer) {
    void onDownload(CCObject* sender) {
        if (!Mod::get()->getSettingValue<bool>("enabled")) return SongInfoLayer::onDownload(sender);
        auto song = MusicDownloadManager::sharedState()->getSongInfoObject(m_songID);
        if (!song) {
            log::error("Failed to get SongInfoObject!");
            return;
        }
        gd::string url = song->m_songUrl;
        log::debug("song link is {}", song->m_songUrl);
        if (url == "") {
            MusicDownloadManager::sharedState()->getSongInfo(m_songID, false);
            log::warn("Failed to get song URL. Please try again!");
        } else log::debug("song link is {}", song->m_songUrl); 
        
        web::openLinkInBrowser(url);
    }
};