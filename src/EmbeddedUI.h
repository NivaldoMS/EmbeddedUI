#ifndef EMBEDDED_UI_H
#define EMBEDDED_UI_H


/*
 * EmbeddedUI
 *
 * Interface pública principal da biblioteca.
 */


// Core

#include "core/Version.h"
#include "core/Types.h"
#include "core/Event.h"
#include "core/EventQueue.h"
#include "core/Callback.h"
#include "core/Component.h"
#include "core/Screen.h"
#include "core/ScreenManager.h"
#include "core/Engine.h"


// Input

#include "input/InputDevice.h"
#include "input/InputEvent.h"
#include "input/Encoder.h"
#include "input/Buttons.h"
#include "input/InputManager.h"

// Menu

#include "widgets/menu/Node.h"
#include "widgets/menu/ValueNode.h"
#include "widgets/menu/Menu.h"
#include "widgets/menu/Cursor.h"
#include "widgets/menu/InteractionState.h"
#include "widgets/menu/Navigation.h"
#include "widgets/menu/Builder.h"
#include "widgets/menu/MenuScreen.h"


// Render

#include "render/Bitmap.h"
#include "render/Background.h"
#include "render/Layout.h"
#include "render/ScrollManager.h"
#include "render/Renderer.h"


// Theme

#include "theme/Theme.h"


// Font

#include "font/Font.h"


// Display drivers

#include "drivers/display/DisplayDriver.h"
#include "drivers/display/U8g2Display.h"


#endif