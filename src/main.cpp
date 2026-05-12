#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/SongInfoLayer.hpp>



class $modify(MySongInfoLayer, SongInfoLayer) {
    void onDownload(CCObject* sender) {
        web::openLinkInBrowser("ngsong.isobun.workers.dev?songID=" + numToString(m_songID));
    }
};