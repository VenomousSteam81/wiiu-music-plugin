#include "main.h"
#include "retain_vars.hpp"
#include "utils/WUPSConfigItemButtonCombo.h"
#include "utils/config.h"
#include "utils/logger.h"
#include <wups.h>
#include "DRCAttachCallback.h"
#include "utils/utils.h"
#include <string>
#include <notifications/notifications.h>

// Mandatory plugin information.
WUPS_PLUGIN_NAME("Music-Plugin");
WUPS_PLUGIN_DESCRIPTION("Plays music that is stored in the music folder on the SDCard");
WUPS_PLUGIN_VERSION(PLUGIN_VERSION_FULL);
WUPS_PLUGIN_AUTHOR("VSteam81");
WUPS_PLUGIN_LICENSE("GPL");

// FS Access
WUPS_USE_WUT_DEVOPTAB();