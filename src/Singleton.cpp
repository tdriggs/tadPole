#include "stdafx.h"
#include "Singleton.h"

#include "Application.h"
#include "LogManager.h"
#include "DebugOverlay.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "GameObjectManager.h"

using namespace tadPole;

template <> Application * Singleton<Application>::instance = NULL;
template <> LogManager * Singleton<LogManager>::instance = NULL;
template <> DebugOverlay * Singleton<DebugOverlay>::instance = NULL;
template <> InputManager * Singleton<InputManager>::instance = NULL;
template <> RenderManager * Singleton<RenderManager>::instance = NULL;
template <> GameObjectManager * Singleton<GameObjectManager>::instance = NULL;
