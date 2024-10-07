#include "config.h"
#include "WUPSConfigItemButtonCombo.h"
#include "retain_vars.hpp"
#include <map>
#include <wups/config/WUPSConfigItemMultipleValues.h>

extern void UpdateAudioOutput();

static void boolItemChangedConfig(ConfigItemBoolean *item, bool newValue) {
    if (!item || !item->identifier) {
        DEBUG_FUNCTION_LINE_WARN("Invalid item or identifier in bool item callback");
        return;
    }
    DEBUG_FUNCTION_LINE_VERBOSE("New value in %s changed: %d", item->identifier, newValue);
    if (std::string_view(ENABLED_CONFIG_STRING) == item->identifier) {
        gEnabled = newValue;
        UpdateAudioOutput();
    } else if (std::string_view(ENABLED_CHANGE_AUDIO_COMBO_CONFIG_STRING) == item->identifier) {
        gChangeAudioOutputButtonComboEnabled = newValue;
    } else if (std::string_view(ENABLE_NOTIFICATIONS_CONFIG_STRING) == item->identifier) {
        gShowNotifications = newValue;
    } else {
        DEBUG_FUNCTION_LINE_WARN("Unexpected boolean item: %s", item->identifier);
        return;
    }
    WUPSStorageError err;
    if ((err = WUPSStorageAPI::Store(item->identifier, newValue)) != WUPS_STORAGE_ERROR_SUCCESS) {
        DEBUG_FUNCTION_LINE_WARN("Failed to store value %d to storage item \"%s\": %s (%d)", newValue, item->identifier, WUPSStorageAPI_GetStatusStr(err), err);
    }
}

static void buttonComboItemChanged(ConfigItemButtonCombo *item, uint32_t newValue) {
    if (!item || !item->identifier) {
        DEBUG_FUNCTION_LINE_WARN("Invalid item or identifier in button combo item callback");
        return;
    }
    DEBUG_FUNCTION_LINE_VERBOSE("New value in %s changed: %d", item->identifier, newValue);
    if (std::string_view(CHANGE_AUDIO_BUTTON_COMBO_CONFIG_STRING) == item->identifier) {
        gSwapAudioButtonCombo = newValue;
    } else {
        DEBUG_FUNCTION_LINE_WARN("Unexpected button combo item: %s", item->identifier);
        return;
    }

    WUPSStorageError err;
    if ((err = WUPSStorageAPI::Store(item->identifier, newValue)) != WUPS_STORAGE_ERROR_SUCCESS) {
        DEBUG_FUNCTION_LINE_WARN("Failed to store value %d to storage item \"%s\": %s (%d)", newValue, item->identifier, WUPSStorageAPI_GetStatusStr(err), err);
    }
}

static void multiItemChanged(ConfigItemMultipleValues *item, uint32_t newValue) {
    if (!item || !item->identifier) {
        DEBUG_FUNCTION_LINE_WARN("Invalid item or identifier in multi item callback");
        return;
    }
    DEBUG_FUNCTION_LINE_VERBOSE("New value in %s changed: %d", item->identifier, newValue);

    if (std::string_view(AUDIO_OUTPUT_CONFIG_STRING) == item->identifier) {
        gCurAudioOutput = static_cast<SwipSwapAudioOutput>(newValue);
    } else {
        DEBUG_FUNCTION_LINE_WARN("Unexpected button combo item: %s", item->identifier);
        return;
    }

    WUPSStorageError err;
    if ((err = WUPSStorageAPI::Store(item->identifier, newValue)) != WUPS_STORAGE_ERROR_SUCCESS) {
        DEBUG_FUNCTION_LINE_WARN("Failed to store value %d to storage item \"%s\": %s (%d)", newValue, item->identifier, WUPSStorageAPI_GetStatusStr(err), err);
    }
}

WUPSConfigAPICallbackStatus ConfigMenuOpenedCallback(WUPSConfigCategoryHandle rootHandle) {
    try {
        WUPSConfigCategory root = WUPSConfigCategory(rootHandle);

        root.add(WUPSConfigItemBoolean::Create(ENABLED_CONFIG_STRING,
                                               "Plugin enabled",
                                               DEFAULT_ENABLED_CONFIG_VALUE, gEnabled,
                                               &boolItemChangedConfig));
        root.add(WUPSConfigItemBoolean::Create(ENABLE_NOTIFICATIONS_CONFIG_STRING,
                                               "Show notifications",
                                               DEFAULT_ENABLE_NOTIFICATIONS_CONFIG_VALUE, gShowNotifications,
                                               &boolItemChangedConfig));

        constexpr WUPSConfigItemMultipleValues::ValuePair audioOutputMap[] = {
                {AUDIO_OUTPUT_DEFAULT, "Normal"},
                {AUDIO_OUTPUT_SWAP, "Swap TV and GamePad sound"},
                {AUDIO_OUTPUT_MATCH_SCREEN, "Sound matches screen"},
                {AUDIO_OUTPUT_COMBINE, "Combine TV and GamePad sound"},

        root.add(WUPSConfigItemMultipleValues::CreateFromValue(AUDIO_OUTPUT_CONFIG_STRING,
                                                               "Audio output:",
                                                               DEFAULT_AUDIO_OUTPUT_CONFIG_VALUE, gCurAudioOutput,
                                                               audioOutputMap,
                                                               &multiItemChanged));

        auto buttonCombos = WUPSConfigCategory::Create("Button Combos");

        buttonCombos.add(WUPSConfigItemBoolean::Create(ENABLED_CHANGE_AUDIO_COMBO_CONFIG_STRING,
                                                       "Enable change audio output button combo",
                                                       DEFAULT_ENABLED_CHANGE_AUDIO_COMBO_CONFIG_VALUE, gChangeAudioOutputButtonComboEnabled,
                                                       &boolItemChangedConfig));

        buttonCombos.add(WUPSConfigItemButtonCombo::Create(CHANGE_AUDIO_BUTTON_COMBO_CONFIG_STRING,
                                                           "Change audio output",
                                                           DEFAULT_CHANGE_AUDIO_BUTTON_COMBO_CONFIG_VALUE, gSwapAudioButtonCombo,
                                                           &buttonComboItemChanged));
        root.add(std::move(buttonCombos));
    } catch (std::exception &e) {
        OSReport("Exception: %s\n", e.what());
        return WUPSCONFIG_API_CALLBACK_RESULT_ERROR;
    }

    return WUPSCONFIG_API_CALLBACK_RESULT_SUCCESS;
}

void ConfigMenuClosedCallback() {
    // Save all changes
    WUPSStorageError err;
    if ((err = WUPSStorageAPI::SaveStorage()) != WUPS_STORAGE_ERROR_SUCCESS) {
        DEBUG_FUNCTION_LINE_ERR("Failed to close storage: %s (%d)", WUPSStorageAPI_GetStatusStr(err), err);
    }
}