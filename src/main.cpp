#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/SongInfoLayer.hpp>


class $modify(MySongInfoLayer, SongInfoLayer) {
    
    

    bool init(std::string name, std::string artist, std::vector<GJLinkObject> sogLinks, std::vector<GJLinkObject> artstLinks, int sogId, std::string p5, int p6) {

        if (!Mod::get()->getSettingValue<bool>("enabled")) return SongInfoLayer::init(name, artist, sogLinks, artstLinks, sogId, p5, p6); // <- if disabled

        if (!sogId) return SongInfoLayer::init(name, artist, sogLinks, artstLinks, sogId, p5, p6); // <- if not a custom song

        auto song = MusicDownloadManager::sharedState()->getSongInfoObject(sogId); 
        if (!song) {
            log::error("Failed to get SongInfoObject!");
            Notification::create("Failed to get song info!", NotificationIcon::Error)->show();
            return SongInfoLayer::init(name, artist, sogLinks, artstLinks, sogId, p5, p6);
        }
        
        std::string url = song->m_songUrl;
        if (sogId >= 10000000) {
            url = MusicDownloadManager::sharedState()->generateCustomContentURL(fmt::format("/music/{}.ogg", sogId)); // if a music from sound library
        }
        
        if (url.empty()) {
            MusicDownloadManager::sharedState()->getSongInfo(sogId, false);
            log::warn("Failed to get song URL. Please try again!");
            Notification::create("Failed to get song URL! Please try again!", NotificationIcon::Error)->show();
            return SongInfoLayer::init(name, artist, sogLinks, artstLinks, sogId, p5, p6);
        } else log::debug("song link is {}", song->m_songUrl); 

        auto linkObj = GJLinkObject(); 
        linkObj.m_link = url;
        linkObj.m_title = "Download";
        sogLinks.push_back(linkObj);

        log::info("hiiii");
        return SongInfoLayer::init(name, artist, sogLinks, artstLinks, sogId, p5, p6);
    }
};