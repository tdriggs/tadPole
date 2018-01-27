#include "stdafx.h"
#include "Singleton.h"

#include "LogManager.h"
#include "DebugOverlay.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "PythonScriptManager.h"

template <> tadPole::LogManager					* tadPole::Singleton<tadPole::LogManager>::instance = NULL;
template <> tadPole::DebugOverlay				* tadPole::Singleton<tadPole::DebugOverlay>::instance = NULL;
template <> tadPole::InputManager				* tadPole::Singleton<tadPole::InputManager>::instance = NULL;
template <> tadPole::RenderManager				* tadPole::Singleton<tadPole::RenderManager>::instance = NULL;
template <> tadPole::PythonScriptManager		* tadPole::Singleton<tadPole::PythonScriptManager>::instance = NULL;
