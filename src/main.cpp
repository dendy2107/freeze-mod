#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>

using namespace geode::prelude;

class $modify(MyLoadingLayer, LoadingLayer) {
    struct Fields {
        bool m_frozen = false;
    };

    void loadAssets() {
        if (m_fields->m_frozen) return;
        LoadingLayer::loadAssets();
    }

    bool init(bool fromReload) {
        if (!LoadingLayer::init(fromReload)) return false;
        this->setKeyboardEnabled(true);
        return true;
    }

    void keyDown(enumKeyCodes key, double timestamp) {
        if (key == enumKeyCodes::KEY_F) {
            m_fields->m_frozen = !m_fields->m_frozen;
            log::info("Freeze: {}", m_fields->m_frozen);
        }
        LoadingLayer::keyDown(key, timestamp);
    }
};    void resubscribeKey(float) {
        this->schedule(schedule_selector(MyLoadingLayer::checkKey), 0.1f);
    }
};
