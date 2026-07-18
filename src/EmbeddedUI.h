#ifndef EMBEDDED_UI_H
#define EMBEDDED_UI_H


// Core

#include "core/Version.h"
#include "core/Types.h"
#include "core/Event.h"
#include "core/EventQueue.h"
#include "core/Screen.h"
#include "core/ScreenManager.h"
#include "core/Engine.h"


// Input

#include "input/Encoder.h"
#include "input/InputEvent.h"
#include "input/InputManager.h"


// Menu

#include "widgets/menu/Node.h"
#include "widgets/menu/ValueNode.h"
#include "widgets/menu/Menu.h"
#include "widgets/menu/Cursor.h"
#include "widgets/menu/Navigation.h"
#include "widgets/menu/InteractionState.h"
#include "widgets/menu/Builder.h"


// Render

#include "render/Renderer.h"
#include "render/Layout.h"
#include "render/ScrollManager.h"
#include "render/Bitmap.h"


// Theme / Font

#include "theme/Theme.h"
#include "font/Font.h"


// Drivers

#include "drivers/display/DisplayDriver.h"
#include "drivers/display/U8g2Display.h"


#endif