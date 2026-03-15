#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>

using namespace geode::prelude;

class $modify(MyLoadingLayer, LoadingLayer) {
    bool m_frozen = false;

    void loadingFinished() {
        m_frozen = true;
        log::info("Loading frozen! Press F12 to continue to menu");

        auto listener = new EventListener<keybinds::InvokeBindFilter>(
            [this](keybinds::InvokeBindEvent* e) {
                if (e->isDown() && m_frozen) {
                    m_frozen = false;
                    LoadingLayer::loadingFinished();
                }
                return ListenControl::Continue;
            },
            keybinds::InvokeBindFilter(nullptr, "freeze-mod/continue"_spr)
        );
        listener->retain();
    }
};
