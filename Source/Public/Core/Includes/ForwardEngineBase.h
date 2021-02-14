// Created by Przemys³aw Wiewióra 2020

#pragma once

// Engine base classes forward declarations
class FEngineMain;
class FEngine;
class FEngineRender;
class FFilesystem;

class FRenderer;
class FWindow;

class FWidget;
class FWidgetManager;
class IWidgetInteraction;

template<class TType = float>
class FVector2D;
class FColorRGBA;
template<typename TReturnType, typename... TInParams>
class FFunctorBase;
#include "Types/Delegate.h"

template<typename TType>
class CContainerBase;
template<typename TType>
class CArray;
template<typename TKey, typename TValue>
class CMap;
template<typename TType>
class CDeque;
template<typename TType>
class CQueueSafe;
