#pragma once
#include "logger.h"
#include "retain_vars.hpp"
#include <string>
#include <vpad/input.h>
#include <wups/config/WUPSConfigItemBoolean.h>
#include <wups/storage.h>

#define DEFAULT_ENABLED_CONFIG_VALUE                     true
#define DEFAULT_ENABLED_CHANGE_AUDIO_COMBO_CONFIG_VALUE  false
#define DEFAULT_ENABLE_NOTIFICATIONS_CONFIG_VALUE        true
#define DEFAULT_CHANGE_AUDIO_BUTTON_COMBO_CONFIG_VALUE   VPAD_BUTTON_STICK_L

#define DEFAULT_AUDIO_MODE_CONFIG_VALUE                  AUDIO_MODE_MATCH_SCREEN

#define ENABLED_CONFIG_STRING                            "enabled"
#define ENABLED_CHANGE_AUDIO_COMBO_CONFIG_STRING         "changeAudioComboEnabled"
#define ENABLE_NOTIFICATIONS_CONFIG_STRING               "notificationsEnabled"
#define CHANGE_AUDIO_BUTTON_COMBO_CONFIG_STRING          "audioButtonCombo"
#define AUDIO_MODE_CONFIG_STRING                         "audioOutput"

WUPSConfigAPICallbackStatus ConfigMenuOpenedCallback(WUPSConfigCategoryHandle rootHandle);

void ConfigMenuClosedCallback();