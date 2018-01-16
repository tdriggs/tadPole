#ifndef STDAFX_H
#define STDAFX_H

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Other Headers to be Pre-Compiled
#include "SDL.h"

#include "rapidjson.h"
#include "document.h"

#include "glm.hpp"
#include "gtc/quaternion.hpp"

#include "Ogre.h"
#include "OgreOverlay.h"
#include "OgreOverlaySystem.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"


#endif
