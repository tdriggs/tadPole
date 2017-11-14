#include "stdafx.h"
#include "DebugOverlay.h"

#include "Application.h"

using namespace tadPole;

DebugOverlay::DebugOverlay() : Singleton<DebugOverlay>()
{
	this->overlay = RENDER_MANAGER->overlayManager->create("DebugOverlay");
	this->messageCount = 0;
	this->messageElements = std::vector<Ogre::TextAreaOverlayElement *>();

	this->initializeMessagePanel();
	this->initializeInfoPanel();

	this->overlay->show();
}

DebugOverlay::~DebugOverlay()
{
}

Ogre::TextAreaOverlayElement * DebugOverlay::createTextElement(Ogre::OverlayContainer * parent, std::string name, std::string caption, float relX, float relY)
{
	Ogre::TextAreaOverlayElement * result = (Ogre::TextAreaOverlayElement *)
		(RENDER_MANAGER->overlayManager->createOverlayElement("TextArea", name));

	result->setMetricsMode(Ogre::GMM_RELATIVE);
	result->setPosition(relX, relY);
	result->setColourBottom(DEBUG_TEXT_BOTTOM_COLOR);
	result->setColourTop(DEBUG_TEXT_TOP_COLOR);
	result->setCharHeight(DEBUG_INFO_CHAR_HEIGHT);
	result->setFontName(DEBUG_TEXT_FONT_NAME);
	result->setCaption(caption);
	parent->addChild(result);

	return result;
}

void tadPole::DebugOverlay::updateInfoPanelCaptions(float deltaTime)
{
	this->avgFpsElement->setCaption("AVERAGE FPS: " + std::to_string((int)RENDER_MANAGER->renderWindow->getStatistics().avgFPS));
	this->bestFpsElement->setCaption("BEST FPS: " + std::to_string((int)RENDER_MANAGER->renderWindow->getStatistics().bestFPS));
	this->lastFpsElement->setCaption("LAST FPS: " + std::to_string((int)RENDER_MANAGER->renderWindow->getStatistics().lastFPS));
	this->worstFpsElement->setCaption("WORST FPS: " + std::to_string((int)RENDER_MANAGER->renderWindow->getStatistics().worstFPS));
	this->triCountElement->setCaption("TRIANGLES: " + std::to_string(RENDER_MANAGER->renderWindow->getStatistics().triangleCount));
	this->batchCountElement->setCaption("BATCHES RENDERED: " + std::to_string(RENDER_MANAGER->renderWindow->getStatistics().batchCount));
	this->bestFrameTimeElement->setCaption("BEST FRAME TIME: " + std::to_string(RENDER_MANAGER->renderWindow->getStatistics().bestFrameTime));
	this->worstFrameTimeElement->setCaption("WORST FRAME TIME: " + std::to_string(RENDER_MANAGER->renderWindow->getStatistics().worstFrameTime));
	this->deltaTimeElement->setCaption("DELTA TIME: " + std::to_string(deltaTime));
}

void DebugOverlay::initializeMessagePanel()
{
	this->messagePanel = (Ogre::OverlayContainer *)
		(RENDER_MANAGER->overlayManager->createOverlayElement("Panel", "MessagePanel"));
	this->messagePanel->setMetricsMode(Ogre::GMM_RELATIVE);
	this->messagePanel->setPosition(0.0f, 0.0f);
	this->messagePanel->setDimensions(DEBUG_MESSAGE_PANEL_RELATIVE_WIDTH, DEBUG_MESSAGE_PANEL_RELATIVE_HEIGHT);
	//this->messagePanel->setMaterialName(DEBUG_PANEL_MATERIAL_NAME);
	this->overlay->add2D(this->messagePanel);
}

void tadPole::DebugOverlay::initializeInfoPanel()
{
	this->infoPanel = (Ogre::OverlayContainer *)
		(RENDER_MANAGER->overlayManager->createOverlayElement("Panel", "InfoPanel"));
	this->infoPanel->setMetricsMode(Ogre::GMM_RELATIVE);
	this->infoPanel->setPosition(1.0f - DEBUG_INFO_PANEL_RELATIVE_WIDTH, 0.0f);
	this->infoPanel->setDimensions(DEBUG_INFO_PANEL_RELATIVE_WIDTH, DEBUG_INFO_PANEL_RELATIVE_HEIGHT);
	//this->infoPanel->setMaterialName(DEBUG_PANEL_MATERIAL_NAME);
	this->overlay->add2D(this->infoPanel);

	this->avgFpsElement = this->createTextElement(
		this->infoPanel,
		"AvgFps",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		0.0f
	);

	this->bestFpsElement = this->createTextElement(
		this->infoPanel,
		"BestFps",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		DEBUG_INFO_CHAR_HEIGHT
	);

	this->lastFpsElement = this->createTextElement(
		this->infoPanel,
		"LastFps",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		DEBUG_INFO_CHAR_HEIGHT * 2
	);

	this->worstFpsElement = this->createTextElement(
		this->infoPanel,
		"WorstFps",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		DEBUG_INFO_CHAR_HEIGHT * 3
	);

	this->triCountElement = this->createTextElement(
		this->infoPanel,
		"TriCount",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		DEBUG_INFO_CHAR_HEIGHT * 4
	);

	this->batchCountElement = this->createTextElement(
		this->infoPanel,
		"BatchCount",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		DEBUG_INFO_CHAR_HEIGHT * 5
	);

	this->bestFrameTimeElement = this->createTextElement(
		this->infoPanel,
		"BestFrameTime",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		DEBUG_INFO_CHAR_HEIGHT * 6
	);

	this->worstFrameTimeElement = this->createTextElement(
		this->infoPanel,
		"WorstFrameTime",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		DEBUG_INFO_CHAR_HEIGHT * 7
	);

	this->deltaTimeElement = this->createTextElement(
		this->infoPanel,
		"DeltaTime",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		DEBUG_INFO_CHAR_HEIGHT * 8
	);

	this->avgFpsElement->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Right);
	this->bestFpsElement->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Right);
	this->lastFpsElement->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Right);
	this->worstFpsElement->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Right);
	this->triCountElement->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Right);
	this->batchCountElement->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Right);
	this->bestFrameTimeElement->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Right);
	this->worstFrameTimeElement->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Right);
	this->deltaTimeElement->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Right);
}

void DebugOverlay::postMessage(std::string message)
{
	if (this->messageElements.size() + 1 > DEBUG_MESSAGE_MAX_COUNT)
	{
		this->messagePanel->removeChild(this->messageElements.at(0)->getName());

		Ogre::TextAreaOverlayElement * message = this->messageElements.at(0);
		this->messageElements.erase(this->messageElements.begin());
		delete message;
	}

	Ogre::TextAreaOverlayElement * messageElement = this->createTextElement(
		this->messagePanel,
		"Message " + std::to_string(this->messageCount),
		message,
		0.0f,
		DEBUG_MESSAGE_CHAR_HEIGHT * this->messageElements.size()
	);

	this->messageElements.push_back(messageElement);
	++this->messageCount;
}

void DebugOverlay::toggleVisible()
{
	if (this->overlay->isVisible())
	{
		this->overlay->hide();
	}
	else
	{
		this->overlay->show();
	}
}

void DebugOverlay::update(float deltaTime)
{
	// Update Message Panel
	for (int i = 0; i < this->messageElements.size(); ++i)
	{
		this->messageElements.at(i)->setPosition(0.0f, DEBUG_MESSAGE_CHAR_HEIGHT * i);
	}

	// Update Info Panel
	this->updateInfoPanelCaptions(deltaTime);
}
