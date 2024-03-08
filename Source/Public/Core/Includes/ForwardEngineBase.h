// Created by Przemys³aw Wiewióra 2020 - 2022

#pragma once

// GEngine base classes forward declarations

class FEngineMain;
class FEngine;
class FEngineRender;
class FFileSystem;

class FAssetsManager;
class FAssetBase;

class FRenderer;
class FWindow;

class FWidget;
class FWidgetManager;
class IWidgetManagementInterface;
class IWidgetInteraction;

class FEntityManager;
class EEntity;
class UComponent;

template<class TType = float>
class FVector2D;
class FColorRGBA;
template<typename TReturnType, typename... TInParams>
class FFunctorBase;
#include "Types/Delegate.h"

/** Begin of containers */
template<typename TType, typename TSizeType>
class CContainerBase;
template<typename TType, typename TSizeType>
class CArray;
template<typename TKey, typename TValue, typename TSizeType>
class CMap;
template<typename TKey, typename TValue, typename TSizeType>
class CUnorderedMap;
template<typename TType, typename TSizeType>
class CDeque;
template<typename TType, typename TSizeType>
class CQueueSafe;
/** End of containers */

/** Begin of memory */
template<typename TTypeToStore>
class FAutoDeletePointer;
template<typename TTypeToStore>
class FAutoUIMenu;
/** End of memory */
