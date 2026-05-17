#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/SongInfoLayer.hpp>

class $modify(MySongInfoLayer, SongInfoLayer) {
    
    bool init(gd::string songName, gd::string artistName, gd::string songURL, gd::string newgroundsURL, gd::string youtubeURL, gd::string facebookURL, int songID, gd::string songTags, int nongType) {
        if (!SongInfoLayer::init(songName, artistName, songURL, newgroundsURL, youtubeURL, facebookURL, songID, songTags, nongType)) return false;
        MusicDownloadManager::sharedState()->getSongInfo(songID, false);
        return true;
    }
    void onDownload(CCObject* sender) {
        if (!Mod::get()->getSettingValue<bool>("enabled")) return SongInfoLayer::onDownload(sender); // <- if disabled
        if (!m_songID) return SongInfoLayer::onDownload(sender); // <- if not a custom song
        auto song = MusicDownloadManager::sharedState()->getSongInfoObject(m_songID); 
        if (!song) {
            log::error("Failed to get SongInfoObject!");
            return;
        }
        gd::string url = song->m_songUrl;
        if (url == "") {
            MusicDownloadManager::sharedState()->getSongInfo(m_songID, false);
            log::warn("Failed to get song URL. Please try again!");
        } else log::debug("song link is {}", song->m_songUrl); 
        
        web::openLinkInBrowser(url);
    }
};