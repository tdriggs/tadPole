#ifndef DEBUG_OVERLAY_H
#define DEBUG_OVERLAY_H

#include "stdafx.h"

#include "Singleton.h"

#define DEBUG_OVERLAY tadPole::DebugOverlay::getInstance()													///< Convienience macro for the singleton instance.
#define DEBUG_MESSAGE_MAX_COUNT 40																			///< The maximum number of messages to be displayed.
#define DEBUG_MESSAGE_PANEL_RELATIVE_HEIGHT 1.0f															///< The height of the debug message panel relative to the screen height.
#define DEBUG_MESSAGE_PANEL_RELATIVE_WIDTH 0.2f																///< The width of the debug message panel relative to the screen width.
#define DEBUG_MESSAGE_CHAR_HEIGHT (1.0f / DEBUG_MESSAGE_MAX_COUNT) * DEBUG_MESSAGE_PANEL_RELATIVE_HEIGHT	///< The height of the debug message panel characters.
#define DEBUG_INFO_PANEL_RELATIVE_HEIGHT 0.1f																///< The height of the debug info panel relative to the screen height.
#define DEBUG_INFO_PANEL_RELATIVE_WIDTH 0.3f																///< The width of the debug info panel relative to the screen width.
#define DEBUG_INFO_CHAR_HEIGHT 0.5f * DEBUG_INFO_PANEL_RELATIVE_HEIGHT										///< The height of the debug info panel characters.
#define DEBUG_TEXT_TOP_COLOR Ogre::ColourValue(0.6f, 0.6f, 0.6f)											///< The color of the top of the text on the DebugOverlay.
#define DEBUG_TEXT_BOTTOM_COLOR Ogre::ColourValue(1.0f, 1.0f, 1.0f)											///< The color of the bottom of the text on the DebugOverlay.
#define DEBUG_TEXT_FONT_NAME "SdkTrays/Value"																///< The name of the font of the text on the DebugOverlay.
#define DEBUG_PANEL_MATERIAL_NAME "SdkTrays/Base"															///< The name of the material of the panels on the DebugOverlay.

namespace tadPole
{
	/**
	* An on screen overlay that displays debug messages, debug metrics, and other general
	* information. Can be toggled on and off with F11.
	*/
	class DebugOverlay : public Singleton<DebugOverlay> 
	{
		// @@@@@ ATTRIBUTES @@@@@
	protected:
		Ogre::Overlay * overlay;											///< The OGRE representation of the DebugOverlay.
		Ogre::OverlayContainer * messagePanel;								///< The OGRE representation of the message panel on the DebugOverlay.
		Ogre::OverlayContainer * infoPanel;									///< The OGRE representation of the info panel on the DebugOverlay.
		int messageCount;													///< The number of messages that has been displayed on the message panel.
		std::vector<Ogre::TextAreaOverlayElement *> messageElements;		///< The OGRE representation of the current messages being displayed on the message panel.
		Ogre::TextAreaOverlayElement * avgFpsElement;						///< The OGRE representation of the element on the DebugOverlay that displays the average FPS.
		Ogre::TextAreaOverlayElement * bestFpsElement;						///< The OGRE representation of the element on the DebugOverlay that displays the best FPS.
		Ogre::TextAreaOverlayElement * lastFpsElement;						///< The OGRE representation of the element on the DebugOverlay that displays the most recent FPS.
		Ogre::TextAreaOverlayElement * worstFpsElement;						///< The OGRE representation of the element on the DebugOverlay that displays the worst FPS.
		Ogre::TextAreaOverlayElement * triCountElement;						///< The OGRE representation of the element on the DebugOverlay that displays the the number of triangles being rendered.
		Ogre::TextAreaOverlayElement * batchCountElement;					///< The OGRE representation of the element on the DebugOverlay that displays the number of batches that have been rendered.
		Ogre::TextAreaOverlayElement * bestFrameTimeElement;				///< The OGRE representation of the element on the DebugOverlay that displays the smallest time between frames.
		Ogre::TextAreaOverlayElement * worstFrameTimeElement;				///< The OGRE representation of the element on the DebugOverlay that displays the largest time between frames.
		Ogre::TextAreaOverlayElement * deltaTimeElement;					///< The OGRE representation of the element on the DebugOverlay that displays the current time between frames.


		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* DebugOverlay constructor.
		*/
		DebugOverlay();

		/**
		* DebugOverlay destructor.
		*/
		~DebugOverlay();
		

		// @@@@@ PUBLIC METHODS @@@@@
	public:
		/**
		* Post a message to the message panel, kicking out the oldest message if necessary.
		*/
		void postMessage(
			std::string message	///< The message to post to the message panel.
		);

		/**
		* Toggle the visiblity of this DebugOverlay.
		*/
		void toggleVisible();

		/**
		* Update this DebugOverlay and all of its elements.
		*/
		void update(
			float deltaTime	///< The time that has passed since the last frame.
		);


		// @@@@@ PROTECTED METHODS @@@@@
	protected:
		/**
		* Create a new text element and add it to the parent given.
		*/
		Ogre::TextAreaOverlayElement * createTextElement(
			Ogre::OverlayContainer * parent,	///< The container of the element to create.
			std::string name,					///< The name of the element to create.
			std::string caption,				///< The display text of the element to create.
			float relativeX,					///< The x value of the position of the element to create relative to the screen width.
			float relativeY,					///< The y value of the position of the element to create relative to the screen height.
			bool isMessage						///< Whether this text element will be going into the message queue.
		);

		/**
		* Update all text elements that are on the info panel of this DebugOverlay.
		*/
		void updateInfoPanelCaptions(
			float deltaTime	///< The time that has passed since the last frame.
		);

		/**
		* Create the message panel, add it to this DebugOverlay, and create any initial child elements that
		* the message panel may need.
		*/
		void initializeMessagePanel();

		/**
		* Create the info panel, add it to this DebugOverlay, and create any initial child elements that
		* the info panel may need.
		*/
		void initializeInfoPanel();
	};
}

#endif
