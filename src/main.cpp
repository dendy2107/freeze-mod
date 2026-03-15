#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>

using namespace geode::prelude;

static bool s_frozen = false;

class $modify(MyCCKeyboardDispatcher, CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool isKeyDown, bool isKeyRepeat, double timestamp) {
        if (isKeyDown && !isKeyRepeat && key == enumKeyCodes::KEY_F) {
            s_frozen = !s_frozen;
            log::info("Freeze toggled: {}", s_frozen);
        }
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, isKeyDown, isKeyRepeat, timestamp);
    }
};

class $modify(MyLoadingLayer, LoadingLayer) {
    void loadAssets() {
        // loadAssets викликається з прогресом 0..100
        // коли m_loadStep досягає кінця — більше не викликається
        // тому просто блокуємо якщо frozen
        if (s_frozen) return;

        LoadingLayer::loadAssets();

        // після останнього кроку завантаження — заморожуємо
        if (m_loadStep >= 14) {
            s_frozen = true;
            log::info("Auto-frozen after last load step. Press F to unfreeze.");
        }
    }
};
