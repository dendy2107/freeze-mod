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

        // Слухаємо клавішу F через schedule
        this->schedule(schedule_selector(MyLoadingLayer::checkKey), 0.1f);

        return true;
    }

    void checkKey(float) {
        auto kb = CCDirector::get()->getKeyboardDispatcher();
        if (kb->getKeyState(enumKeyCodes::KEY_F)) {
            m_fields->m_frozen = !m_fields->m_frozen;
            log::info("Freeze: {}", m_fields->m_frozen);
            // невелика затримка щоб не флікало
            this->unschedule(schedule_selector(MyLoadingLayer::checkKey));
            this->scheduleOnce(
                schedule_selector(MyLoadingLayer::resubscribeKey), 0.3f
            );
        }
    }

    void resubscribeKey(float) {
        this->schedule(schedule_selector(MyLoadingLayer::checkKey), 0.1f);
    }
};
