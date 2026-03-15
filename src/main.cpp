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

        auto listener = addEventListener<keybinds::InvokeBindFilter>(
            [this](keybinds::InvokeBindEvent* e) {
                if (e->isDown()) {
                    m_fields->m_frozen = !m_fields->m_frozen;
                    log::info("Freeze: {}", m_fields->m_frozen);
                }
                return ListenControl::Continue;
            },
            "freeze-mod/toggle"_spr
        );

        return true;
    }
};
