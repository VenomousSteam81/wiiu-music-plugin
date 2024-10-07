#pragma once

#include <cstdint>

typedef enum SwipSwapAudioOutput {
    AUDIO_OUTPUT_NONE              = 0,
    AUDIO_OUTPUT_SWAP              = 1,
    AUDIO_OUTPUT_COMBINE           = 2,
    AUDIO_OUTPUT_MAX_VALUE         = 3
} SwipSwapAudioOutput;

extern uint32_t gSwapAudioButtonCombo;
extern bool gChangeAudioModeButtonComboEnabled;
extern bool gEnabled;
extern bool gShowNotifications;
extern bool gNotificationModuleInitDone;

extern SwipSwapAudioOutput gCurAudioOutput;