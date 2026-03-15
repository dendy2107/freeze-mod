#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>

using namespace geode::prelude;

static bool s_frozen = false;

class $modify(MyCCKeyboardDispatcher, CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool isKeyDown, bool isKeyRepeat) {
        if (isKeyDown && !isKeyRepeat && key == enumKeyCodes::KEY_F) {
            s_frozen = !s_frozen;
            log::info("Freeze toggled: {}", s_frozen);
        }
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, isKeyDown, isKeyRepeat);
    }
};

class $modify(MyLoadingLayer, LoadingLayer) {
    void loadAssets() {
        if (s_frozen) return;
        LoadingLayer::loadAssets();
    }

    void loadingFinished() {
        s_frozen = true;
        log::info("Loading finished — auto-frozen. Press F to continue.");
        // не викликаємо LoadingLayer::loadingFinished() — не переходимо в меню
    }
};
