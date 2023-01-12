// Copyright 2023 Puny Human, Licensed under either the MIT or Apache 2.0 license.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FArcInventoryEnhancedInputModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
