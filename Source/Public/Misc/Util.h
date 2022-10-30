// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "Containers/QueueSafe.h"

enum class ELogMessageType : Uint8
{
	Message_Info,
	Message_Debug,
	Message_Warning,
	Message_Error,
};

struct FLogMessage
{
	ELogMessageType Type;
	std::string Text;
};

namespace FUtil
{
	/* Use this function as one of first functions.
	 * Creates thread for logs
	 * @param enableLogging specify wheater to log to file or not
	 * @param logLevel changes level of log. */
	void LogInit(bool EnableLogging = true);

	/* Thread for messages on console. */
	static int MessagesPrinter(void* ptr);

	/* @returns current nano-second since epoch(1 January 1970) - signed integer type of at least 64 bits */
	INLINE_DEBUGABLE size_t GetNanoSeconds();
	/* @returns current micro-second since epoch(1 January 1970) - signed integer type of at least 55 bits */
	INLINE_DEBUGABLE size_t GetMircoSeconds();
	/* @returns current mili-second since epoch(1 January 1970) - signed integer type of at least 45 bits */
	INLINE_DEBUGABLE size_t GetMiliSeconds();
	/* @returns current second since epoch(1 January 1970) - signed integer type of at least 35 bits */
	size_t GetSeconds();
	
	/* Convert nanoseconds to seconds */
	template <class TTypeOut = double>
	INLINE_DEBUGABLE TTypeOut NanoSecondToSecond(const size_t InNanosecond)
	{
		const static size_t FullNanoSecond = 1e9;
		
		return (static_cast<double>(InNanosecond) / static_cast<double>(FullNanoSecond));
	}
	/* Convert MicroSeconds to seconds */
	template <typename TTypeOut = double>
	INLINE_DEBUGABLE TTypeOut MicroSecondToSecond(const size_t InNanosecond)
	{
		const static size_t FullMicroSecond = 1e6;
		
		return (static_cast<double>(InNanosecond) / static_cast<double>(FullMicroSecond));
	}
	/* Convert MiliSeconds to seconds */
	template <typename TTypeOut = double>
	INLINE_DEBUGABLE TTypeOut MiliSecondToSecond(const size_t InNanosecond)
	{
		const static size_t FullMiliSecond = 1e3;
		
		return (static_cast<double>(InNanosecond) / static_cast<double>(FullMiliSecond));
	}

	/** @returns time_t with current time. */
	INLINE_DEBUGABLE time_t GetTime();
	/** @returns time_t with current time. */
	INLINE_DEBUGABLE struct tm GetTimeInfo();

	/** @returns second of minute */
	INLINE_DEBUGABLE int GetSecond(struct tm InTime = GetTimeInfo());
	/** @returns minute of hour */
	INLINE_DEBUGABLE int GetMinute(struct tm InTime = GetTimeInfo());
	/** @returns hour of day */
	INLINE_DEBUGABLE int GetHour(struct tm InTime = GetTimeInfo());
	/** @returns day of Week */
	INLINE_DEBUGABLE int GetDayOfWeek(struct tm InTime = GetTimeInfo());
	/** @returns day of month */
	INLINE_DEBUGABLE int GetDayOfMonth(struct tm InTime = GetTimeInfo());
	/** @returns day of month */
	INLINE_DEBUGABLE int GetDayOfYear(struct tm InTime = GetTimeInfo());
	/** @returns month of year */
	INLINE_DEBUGABLE int GetMonth(struct tm InTime = GetTimeInfo());
	/** @returns year */
	INLINE_DEBUGABLE int GetYear(struct tm InTime = GetTimeInfo());

	/* Starts delay.
	 * @param startMs should be long long int &.
	 * This functions sets time in ms. */
	void StartDelay(size_t& StartMs);

	/* Checks and returns true if it's delayed enough.
	 * @param startMs is long long int& set in startDelay().
	 * @param delayMs is time(in ms) which needs to pass untill this function will return true.*/
	bool IsDelayed(size_t& StartMs, size_t DelayMs);

	/** @returns rawtime */
	INLINE_DEBUGABLE time_t GetRawtime();
	/** @returns time info */
	INLINE_DEBUGABLE struct tm GetTimeInfo();


	/* Returns current time in format 12_01_2019_12_37_23. */
	INLINE_DEBUGABLE std::string GetCurrentTimeNoSpecial();

	/* Returns current time in format 12:01:2019 12:37:23. */
	INLINE_DEBUGABLE std::string GetCurrentTime();


	/** Logs (Info): with white(default) color. */
	inline void Info(std::string Message);
	/** Logs (Info): with white(default) color. Print any value (std::ostream). */
	void Info(std::ostream& Message);

/** Logs (Info): with white(default) color. */
#define LOG_INFO(Message) (FUtil::Info(std::ostringstream().flush() << Message))

	/** Logs (Debug): with log color. LOGS ONLY WHEN IN _DEBUG mode. */
	inline void Debug(std::string Message);
	/** Logs (Debug): with log color. LOGS ONLY WHEN IN _DEBUG mode. Print any value (std::ostream). */
	void Debug(std::ostream& Message);

#if _DEBUG
/** Logs (Debug): with log color. LOGS ONLY WHEN IN _DEBUG mode. */
#define LOG_DEBUG(Message) (FUtil::Debug(std::ostringstream().flush() << Message))
#else
#define LOG_DEBUG(Message)
#endif

	/** Logs (Warn): with yellow color. Has overloads. */
	inline void Warn(std::string Message);
	/** Logs (Warn): with yellow color. Print any value (std::ostream). */
	void Warn(std::ostream& Message);

/** Logs (Warn): with yellow color. Logs with file and line. */
#define LOG_WARN(Message) (FUtil::Warn(std::ostringstream().flush() << Message << std::endl << " in " << __FILE__ << "@" << __LINE__))

	
	/** Logs (Error): with red color */
	inline void Error(std::string Message);
	/** Logs (Error): with red color. Print any value (std::ostream). */
	void Error(std::ostream& Message);
	
/** Logs (Error): with red color. Logs with file and line. */
#define LOG_ERROR(Message) (FUtil::Error(std::ostringstream().flush() << Message << std::endl << " in " << __FILE__ << "@" << __LINE__))


	/* Print text to console with specified Color.
	 * @param Color see link below.
	 * @see https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c for Color types
	 * This function doesn't log to file. */
	inline void PrintToConsole(std::string& Message, const int Color = 7);

/** Set bit on bitmask */
#define BITMASK_SET(Variable, Mask) ((Variable) |= (Mask));
#define BITMASK_UNSET(Variable, Mask) ((Variable) &= ~(Mask));
#define BITMASK_TOGGLE(Variable, Mask) ((Variable) ^= (Mask));
/** Use this to check wheater bit on bitmask is set */
#define BITMASK_IS_SET(Variable, Mask) (((Variable) & (Mask)) == (Mask))
	
	template<typename TValue = int>
	TValue GetRandomValue(TValue Min, TValue Max)
	{
		return ((rand() % Max) + Min);
	}

	template<typename TValue = float>
	TValue GetRandomValueFloating(TValue Min, TValue Max)
	{
		return Min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (Max - Min)));
	}

	FColorRGBA GetRandomColor();
	
	template<typename TValue = int>
	FVector2D<TValue> GetPointAngle(const TValue Distance, const TValue Angle)
	{
		FVector2D<TValue> Vector;
		
		Vector.X = cos(Angle) * Distance;
		Vector.Y = sin(Angle) * Distance;

		return Vector;
	}

	/* Path to file with log. */ 
	extern std::string LogFilePath;

	/* Log directory. Default: "log". */
	extern std::string LogDir;

	/* Log prefix. Default: "log_". eg: log_13_01_19... */
	extern std::string LogPrefix;

	/* Sets whether logging to file is enabled or not with LogInit() function. */
	extern bool bIsLoggingEnabled;


	/* Set to false to stop logging (on thread). */
	extern bool KeepLogging;

	/* Thread for console and log output */
	extern SDL_Thread* LogThread;

	/* Queue for messages. */
	extern CQueueSafe<FLogMessage> MessagesQueue;
}
