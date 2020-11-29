// 

#pragma once

class FEngine
{
public:
	FEngine();
	~FEngine();

	/** First init ever called. */
	virtual void PreInit();

	/** Init (Inits SDL, Engine stuff). */
	virtual void Init(int argc, char* argv[]);

	/** Third init function. */
	virtual void PostInit();

	/** Is inside of loop. Runs until Exit() is called. */
	virtual void MainLoop();

	/** MainLoop() runs untill this return false. */
	bool CanContinueMainLoop() const;

	/** True if framerate limit is enabled. */
	bool IsFrameRateLimit() const;

	/** Call to stop main loop. (Exit engine) */
	virtual void Stop();

	/** Called when main loops stop but before destructor. */
	virtual void PreExit();

	/** Clean up memory. */
	virtual void Clean();

protected:
	bool bFrameRateLimit;

private:
	bool bContinueMainLoop;
};

