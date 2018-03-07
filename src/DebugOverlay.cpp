#include "stdafx.h"
#include "DebugOverlay.h"

#include "RenderManager.h"

tadPole::DebugOverlay::DebugOverlay() : Singleton<DebugOverlay>()
{
	this->overlay = RENDER_MANAGER->overlayManager->create("DebugOverlay");
	this->messageCount = 0;
	this->messageElements = std::vector<Ogre::TextAreaOverlayElement *>();

	this->initializeMessagePanel();
	this->initializeInfoPanel();

	this->overlay->show();
}

tadPole::DebugOverlay::~DebugOverlay()
{ 
	this->messageElements.clear();
}

void tadPole::DebugOverlay::postMessage(std::string message)
{
	std::string messageLine = "";
	std::string messageRemainder = message;

	while (messageRemainder != "" && messageRemainder != "\n")
	{
		int newLineIndex = messageRemainder.find_first_of("\n");
		if (newLineIndex != std::string::npos)
		{
			messageLine = messageRemainder.substr(0, newLineIndex);
			messageRemainder = messageRemainder.substr(newLineIndex + 1, messageRemainder.size());
		}
		else
		{
			messageLine = messageRemainder;
			messageRemainder = "";
		}

		if (this->messageElements.size() + 1 > DEBUG_MESSAGE_MAX_COUNT)
		{
			Ogre::TextAreaOverlayElement * m = this->messageElements.at(0);
			this->messagePanel->removeChild(m->getName());
			this->messageElements.erase(this->messageElements.begin());
			delete m;
		}

		Ogre::TextAreaOverlayElement * messageElement = this->createTextElement(
			this->messagePanel,
			"Message " + std::to_string(this->messageCount),
			messageLine,
			0.0f,
			DEBUG_MESSAGE_CHAR_HEIGHT * this->messageElements.size(),
			true
		);

		this->messageElements.push_back(messageElement);
		++this->messageCount;

		for (int i = 0; i < this->messageElements.size(); ++i)
		{
			this->messageElements.at(i)->setPosition(0.0f, DEBUG_MESSAGE_CHAR_HEIGHT * i);
		}
	}
}

void tadPole::DebugOverlay::toggleVisible()
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

void tadPole::DebugOverlay::update(float deltaTime)
{
	for (int i = 0; i < this->messageElements.size(); ++i)
	{
		this->messageElements.at(i)->setPosition(0.0f, DEBUG_MESSAGE_CHAR_HEIGHT * i);
	}

	// Update Info Panel
	this->updateInfoPanelCaptions(deltaTime);
}

Ogre::TextAreaOverlayElement * tadPole::DebugOverlay::createTextElement(Ogre::OverlayContainer * parent, std::string name, std::string caption, float relativeX, float relativeY, bool isMessage)
{
	Ogre::TextAreaOverlayElement * result = (Ogre::TextAreaOverlayElement *)
		(RENDER_MANAGER->overlayManager->createOverlayElement("TextArea", name));

	result->setMetricsMode(Ogre::GMM_RELATIVE);
	result->setPosition(relativeX, relativeY);
	result->setColourBottom(DEBUG_TEXT_BOTTOM_COLOR);
	result->setColourTop(DEBUG_TEXT_TOP_COLOR);
	result->setCharHeight(isMessage ? DEBUG_MESSAGE_CHAR_HEIGHT : DEBUG_INFO_CHAR_HEIGHT);
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

void tadPole::DebugOverlay::initializeMessagePanel()
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
		0.0f,
		false
	);

	this->bestFpsElement = this->createTextElement(
		this->infoPanel,
		"BestFps",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		DEBUG_INFO_CHAR_HEIGHT,
		false
	);

	this->lastFpsElement = this->createTextElement(
		this->infoPanel,
		"LastFps",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		DEBUG_INFO_CHAR_HEIGHT * 2,
		false
	);

	this->worstFpsElement = this->createTextElement(
		this->infoPanel,
		"WorstFps",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		DEBUG_INFO_CHAR_HEIGHT * 3,
		false
	);

	this->triCountElement = this->createTextElement(
		this->infoPanel,
		"TriCount",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		DEBUG_INFO_CHAR_HEIGHT * 4,
		false
	);

	this->batchCountElement = this->createTextElement(
		this->infoPanel,
		"BatchCount",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		DEBUG_INFO_CHAR_HEIGHT * 5,
		false
	);

	this->bestFrameTimeElement = this->createTextElement(
		this->infoPanel,
		"BestFrameTime",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		DEBUG_INFO_CHAR_HEIGHT * 6,
		false
	);

	this->worstFrameTimeElement = this->createTextElement(
		this->infoPanel,
		"WorstFrameTime",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		DEBUG_INFO_CHAR_HEIGHT * 7,
		false
	);

	this->deltaTimeElement = this->createTextElement(
		this->infoPanel,
		"DeltaTime",
		"",
		DEBUG_INFO_PANEL_RELATIVE_WIDTH,
		DEBUG_INFO_CHAR_HEIGHT * 8,
		false
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
