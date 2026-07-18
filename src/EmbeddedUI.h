#ifndef EMBEDDED_UI_H
#define EMBEDDED_UI_H


// Core
#include "core/Version.h"
#include "core/Types.h"
#include "core/Event.h"
#include "core/Callback.h"
#include "core/Component.h"
#include "core/Screen.h"
#include "core/ScreenManager.h"
#include "core/Engine.h"

// Input
#include "input/Encoder.h"
#include "input/InputEvent.h"
#include "input/InputManager.h"

// Menu
#include "menu/Item.h"
#include "menu/Value.h"
#include "menu/MenuScreen.h"

// Render
#include "render/Renderer.h"
#include "render/Background.h"
#include "render/Bitmap.h"

// Drivers
#include "drivers/display/U8g2Display.h"

namespace EmbeddedUI
{


class UIEngine;


}


#endif