// Created by Przemys³aw Wiewióra 2020

#pragma once

// Engine
#include "Misc/Util.h"

#include "Assets/Assets/AssetBase.h"
#include "Assets/AssetsManager.h"

#include "Public/Containers/ContainerBase.h"
#include "Public/Containers/Array.h"
#include "Public/Containers/Map.h"
#include "Public/Containers/UnorderedMap.h"
#include "Public/Containers/Deque.h"
#include "Public/Containers/QueueSafe.h"

#include "Public/Types/Vector2D.h"
#include "Public/Types/ColorRGBA.h"
#include "Public/Types/FunctorBase.h"

#include "Core/Object.h"
#include "Core/Engine.h"
#include "Core/EngineRender.h"
#include "Core/EngineMain.h"

#include "Core/Memory/AutoDeletePointer.h"

#include "Core/ECS/EntityManager.h"

#include "Renderer/Window.h"
#include "Renderer/Renderer.h"

#include "Renderer/Widgets/Widget.h"
#include "Renderer/Widgets/WidgetsManagementInterface.h"
#include "Renderer/Widgets/WidgetManager.h"
#include "Renderer/Widgets/WidgetInteraction.h"
