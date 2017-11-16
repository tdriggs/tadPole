#ifndef DEBUG_OVERLAY_H
#define DEBUG_OVERLAY_H

#include "stdafx.h"

#include "Singleton.h"

#define DEBUG_OVERLAY tadPole::DebugOverlay::getInstance()
#define DEBUG_MESSAGE_MAX_COUNT 15
#define DEBUG_MESSAGE_PANEL_RELATIVE_HEIGHT 0.75f
#define DEBUG_MESSAGE_PANEL_RELATIVE_WIDTH 0.2f
#define DEBUG_MESSAGE_CHAR_HEIGHT (1.0f / DEBUG_MESSAGE_MAX_COUNT) * DEBUG_MESSAGE_PANEL_RELATIVE_HEIGHT
#define DEBUG_INFO_PANEL_RELATIVE_HEIGHT 0.1f
#define DEBUG_INFO_PANEL_RELATIVE_WIDTH 0.3f
#define DEBUG_INFO_CHAR_HEIGHT 0.5f * DEBUG_INFO_PANEL_RELATIVE_HEIGHT
#define DEBUG_TEXT_TOP_COLOR Ogre::ColourValue(0.6f, 0.6f, 0.6f)
#define DEBUG_TEXT_BOTTOM_COLOR Ogre::ColourValue(1.0f, 1.0f, 1.0f)
#define DEBUG_TEXT_FONT_NAME "SdkTrays/Value"
#define DEBUG_PANEL_MATERIAL_NAME "SdkTrays/Base"

namespace tadPole
{
	class DebugOverlay : public Singleton<DebugOverlay> 
	{
	protected:
		Ogre::Overlay * overlay;
		Ogre::OverlayContainer * messagePanel;
		Ogre::OverlayContainer * infoPanel;

		int messageCount;
		std::vector<Ogre::TextAreaOverlayElement *> messageElements;

		Ogre::TextAreaOverlayElement * avgFpsElement;
		Ogre::TextAreaOverlayElement * bestFpsElement;
		Ogre::TextAreaOverlayElement * lastFpsElement;
		Ogre::TextAreaOverlayElement * worstFpsElement;
		Ogre::TextAreaOverlayElement * triCountElement;
		Ogre::TextAreaOverlayElement * batchCountElement;
		Ogre::TextAreaOverlayElement * bestFrameTimeElement;
		Ogre::TextAreaOverlayElement * worstFrameTimeElement;
		Ogre::TextAreaOverlayElement * deltaTimeElement;

	public:
		DebugOverlay();
		~DebugOverlay();

		void postMessage(std::string message);
		void toggleVisible();
		void update(float deltaTime);

	protected:
		Ogre::TextAreaOverlayElement * createTextElement(Ogre::OverlayContainer * parent, std::string name, std::string caption, float relX, float relY);
		void updateInfoPanelCaptions(float deltaTime);
		void initializeMessagePanel();
		void initializeInfoPanel();
	};
}

#endif
