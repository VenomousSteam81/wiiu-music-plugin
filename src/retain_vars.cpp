#include "retain_vars.hpp"
#include "utils/config.h"

bool gEnabled                            = DEFAULT_ENABLED_CONFIG_VALUE;
uint32_t gSwapAudioButtonCombo           = DEFAULT_CHANGE_AUDIO_BUTTON_COMBO_CONFIG_VALUE;
bool gChangeAudioOutputButtonComboEnabled  = DEFAULT_ENABLED_CHANGE_AUDIO_COMBO_CONFIG_VALUE;
bool gShowNotifications                  = DEFAULT_ENABLE_NOTIFICATIONS_CONFIG_VALUE;

MusicAudioOutput gCurAudioOutput   = DEFAULT_AUDIO_OUTPUT_CONFIG_VALUE;

bool gNotificationModuleInitDone = true;