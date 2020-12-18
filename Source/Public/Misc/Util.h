//

#pragma once

#include "CoreMinimal.h"
#include <string>
#include <sstream>
#include "QueueSafe.h"

enum class ELogMessageType
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

	/* @Returns current nano-second since epoch(1 January 1970) - signed integer type of at least 64 bits */
	INLINE_DEBUGABLE size_t GetNanoSeconds();
	/* @Returns current micro-second since epoch(1 January 1970) - signed integer type of at least 55 bits */
	INLINE_DEBUGABLE size_t GetMircoSeconds();
	/* @Returns current mili-second since epoch(1 January 1970) - signed integer type of at least 45 bits */
	INLINE_DEBUGABLE size_t GetMiliseconds();
	/* @Returns current second since epoch(1 January 1970) - signed integer type of at least 35 bits */
	INLINE_DEBUGABLE size_t GetSeconds();

	/** @Returns time_t with current time. */
	INLINE_DEBUGABLE time_t GetTime();
	/** @Returns time_t with current time. */
	INLINE_DEBUGABLE struct tm GetTimeInfo();

	/** @Returns second of minute */
	INLINE_DEBUGABLE int GetSecond(struct tm InTime = GetTimeInfo());
	/** @Returns minute of hour */
	INLINE_DEBUGABLE int GetMinute(struct tm InTime = GetTimeInfo());
	/** @Returns hour of day */
	INLINE_DEBUGABLE int GetHour(struct tm InTime = GetTimeInfo());
	/** @Returns day of Week */
	INLINE_DEBUGABLE int GetDayOfWeek(struct tm InTime = GetTimeInfo());
	/** @Returns day of month */
	INLINE_DEBUGABLE int GetDayOfMonth(struct tm InTime = GetTimeInfo());
	/** @Returns day of month */
	INLINE_DEBUGABLE int GetDayOfYear(struct tm InTime = GetTimeInfo());
	/** @Returns month of year */
	INLINE_DEBUGABLE int GetMonth(struct tm InTime = GetTimeInfo());
	/** @Returns year */
	INLINE_DEBUGABLE int GetYear(struct tm InTime = GetTimeInfo());

	/* Starts delay.
	 * @param startMs should be long long int &.
	 * This functions sets time in ms. */
	void StartDelay(size_t& StartMs);

	/* Checks and returns true if it's delayed enough.
	 * @param startMs is long long int& set in startDelay().
	 * @param delayMs is time(in ms) which needs to pass untill this function will return true.*/
	bool IsDelayed(size_t& StartMs, size_t DelayMs);


	/** @Returns rawtime */
	INLINE_DEBUGABLE time_t GetRawtime();
	/** @Returns time info */
	INLINE_DEBUGABLE struct tm GetTimeInfo();


	/* Returns current time in format 12_01_2019_12_37_23. */
	INLINE_DEBUGABLE std::string GetCurrentTimeNoSpecial();

	/* Returns current time in format 12:01:2019 12:37:23. */
	INLINE_DEBUGABLE std::string GetCurrTime();


	/** Logs (Info): with white(default) color. */
	INLINE_DEBUGABLE void Info(std::string Message);
	/** Logs (Info): with white(default) color. Print any value (std::ostream). */
	INLINE_DEBUGABLE void Info(std::ostream& Message);

/** Logs (Info): with white(default) color. */
#define LOG_INFO(Message) FUtil::Info(std::ostringstream().flush() << Message)

	/** Logs (Debug): with log color. LOGS ONLY WHEN IN _DEBUG mode. */
	INLINE_DEBUGABLE void Debug(std::string Message);
	/** Logs (Debug): with log color. LOGS ONLY WHEN IN _DEBUG mode. Print any value (std::ostream). */
	INLINE_DEBUGABLE void Debug(std::ostream& Message);

#if _DEBUG
/** Logs (Debug): with log color. LOGS ONLY WHEN IN _DEBUG mode. */
#define LOG_DEBUG(Message) FUtil::Debug(std::ostringstream().flush() << Message)
#else
#define LOG_DEBUG(Message)
#endif

	/** Logs (Warnning): with yellow color. Has overloads. */
	INLINE_DEBUGABLE void Warn(std::string Message);
	/** Logs (Warnning): with yellow color. Print any value (std::ostream). */
	INLINE_DEBUGABLE void Warn(std::ostream& Message);

/** Logs (Warnning): with yellow color. Has overloads. */
#define LOG_WARN(Message) FUtil::Warn(std::ostringstream().flush() << Message)

	
	/** Logs (Error): with red color */
	INLINE_DEBUGABLE void Error(std::string Message);
	/** Logs (Error): with red color. Print any value (std::ostream). */
	INLINE_DEBUGABLE void Error(std::ostream& Message);

/** Logs (Error): with red color */
#define LOG_ERROR(Message) FUtil::Error(std::ostringstream().flush() << Message)


	/* Print text to console with specified color.
	 * @param color see link below.
	 * @see https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c for color types
	 * This function doesn't log to file. */
	INLINE_DEBUGABLE void PrintToConsole(std::string& message, const int color = 7);


	/* Path to file with log. */ 
	extern std::string LogFilePath;

	/* Log directory. Deault: "log". */
	extern std::string LogDir;

	/* Log prefix. Defult: "log_". eg: log_13_01_19... */
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