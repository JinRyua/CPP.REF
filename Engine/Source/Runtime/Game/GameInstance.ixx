// Copyright 2020-2021 Aumoa.lib. All right reserved.

export module SC.Runtime.Game:GameInstance;

import std.core;
import SC.Runtime.Core;
import SC.Runtime.RenderCore;
import :GameObject;
import :SubclassOf;

using namespace std;
using namespace std::chrono;

export class GameEngine;
export class Level;
export class World;
export struct IFrameworkView;

/// <summary>
/// Represents single game instance while application are running.
/// </summary>
export class GameInstance : public GameObject
{
public:
	using Super = GameObject;
	using PostInitializedEvent = MulticastEvent<GameInstance, void()>;

private:
	IFrameworkView* _frameworkView = nullptr;
	GameEngine* _engine = nullptr;
	World* _world = nullptr;

public:
	SubclassOf<Level> StartupLevel;

public:
	/// <summary>
	/// Initialize new <see cref="GameInstance"/> instance.
	/// </summary>
	GameInstance();

	virtual void Tick(duration<float> elapsedTime);

	/// <summary>
	/// Run the application.
	/// </summary>
	/// <param name="frameworkView"> The core framework view window. </param>
	/// <returns> Return primary exit code. </returns>
	int32 Run(IFrameworkView* frameworkView);

	/// <summary>
	/// Event for game engine be initialized.
	/// </summary>
	PostInitializedEvent PostInitialized;

	/// <summary>
	/// Get core framework view.
	/// </summary>
	IFrameworkView* GetFrameworkView() const;

protected:
	/// <summary>
	/// Initialize the game engine.
	/// </summary>
	virtual void InitializeEngine();
};