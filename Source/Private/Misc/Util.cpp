//

#include "Misc/Util.h"
#include "CoreEngine.h"
#include "Misc/FileSystem.h"

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif

namespace FUtil
{
	bool isLoggingEnabled = false;
	int loggingLevel = 1;
	std::string LogDir = "log";
	std::string LogPrefix = "log_";
	std::string LogFilePath = LogDir + "/" + LogPrefix + GetCurrentTimeNoSpecial();

	bool KeepLogging = true;
	SDL_Thread* LogThread;
	CQueueSafe<FLogMessage> MessagesQueue;

	void LogInit(bool EnableLogging)
	{
		if (EnableLogging)
		{
			// @TODO uncomment
			FFilesystem::CreateDirrectory(LogDir);

			isLoggingEnabled = true;

			std::cout << "LogInit - Logging to: " << LogFilePath << std::endl;
		}
		else
		{
			isLoggingEnabled = false;
		}

		SDL_CreateThread(MessagesPrinter, "Log", (void*)NULL);
	}

	static int MessagesPrinter(void* ptr)
	{
		while (KeepLogging)
		{
			if (MessagesQueue.Size() <= 0)
			{
				SDL_Delay(2);
			}
			else
			{
				FLogMessage& Message = MessagesQueue.PeekFirst();

				switch (Message.Type)
				{
				case ELogMessageType::Message_Info:
					PrintToConsole(Message.Text, 7);
					break;

				case ELogMessageType::Message_Debug:
#ifdef _DEBUG
					PrintToConsole(Message.Text, 5);
#endif // _DEBUG
					break;

				case ELogMessageType::Message_Warning:
					PrintToConsole(Message.Text, 6);
					break;

				case ELogMessageType::Message_Error:
					PrintToConsole(Message.Text, 4);
					break;

				default:
					// Should be impossible (infinite loop may happen)
					// @TODO Create type assert
					break;
				}

				if (isLoggingEnabled)
				{
					// @TODO Either append or keep it open

					std::ofstream LogFile;
					LogFile.open(LogFilePath, std::ios_base::app);
					LogFile << Message.Text << std::endl;
					LogFile.close();
				}

				// Remove item
				MessagesQueue.PopSafe();
			}
		}

		return 0;
	}

	/* Return current Milisecond */
	inline long long unsigned int GetMiliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	/* Starts delay you need variable long long int and pass it as reference */
	void StartDelay(time_t& startMs)
	{
		startMs = GetMiliseconds();
	}

	bool IsDelayed(time_t& startMs, time_t& delayMs)
	{
		long long signed int Difference = startMs + delayMs;

		if (static_cast<long long signed int>(GetMiliseconds()) >= Difference)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	time_t GetRawtime()
	{
		time_t rawtime;
		time(&rawtime);
		struct tm timeinfo;
		localtime_s(&timeinfo, &rawtime);

		return rawtime;
	}

	std::string GetCurrentTimeNoSpecial()
	{
		std::string MonthTable[12] = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };

		time_t rawtime;
		time(&rawtime);
		struct tm timeinfo;
		localtime_s(&timeinfo, &rawtime);

		std::string ctm = std::to_string(timeinfo.tm_mday) + "_" + MonthTable[timeinfo.tm_mon] + "_" + std::to_string(timeinfo.tm_year + 1900) + "_"
			+ std::to_string(timeinfo.tm_hour) + "_" + std::to_string(timeinfo.tm_min) + "_" + std::to_string(timeinfo.tm_sec);

		return ctm;
	}

	std::string GetCurrTime()
	{
		std::string MonthTable[12] = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };

		time_t rawtime;
		time(&rawtime);
		struct tm timeinfo;
		localtime_s(&timeinfo, &rawtime);

		std::string ctm = std::to_string(timeinfo.tm_mday) + "-" + MonthTable[timeinfo.tm_mon] + "-" + std::to_string(timeinfo.tm_year + 1900) + " "
			+ std::to_string(timeinfo.tm_hour) + ":" + std::to_string(timeinfo.tm_min) + ":" + std::to_string(timeinfo.tm_sec);

		return ctm;
	}

	void Info(std::string Message)
	{
		Message = GetCurrTime() + " (Info): " + Message;

		MessagesQueue.PushSafe({ ELogMessageType::Message_Info, Message });
	}

	void Info(std::ostream& Message)
	{
		Info(dynamic_cast<std::ostringstream&>(Message).str());
	}

	void Debug(std::string Message)
	{
#ifdef _DEBUG // if debug
		Message = GetCurrTime() + " (Debug): " + Message;

		MessagesQueue.PushSafe({ ELogMessageType::Message_Debug, Message });
#endif
	}

	void Debug(std::ostream& Message)
	{
		Debug(dynamic_cast<std::ostringstream&>(Message).str());
	}

	void Warn(std::string Message)
	{
		Message = GetCurrTime() + " (Warn): " + Message;

		MessagesQueue.PushSafe({ ELogMessageType::Message_Warning, Message });
	}

	void Warn(std::ostream& Message)
	{
		Warn(dynamic_cast<std::ostringstream&>(Message).str());
	}

	void Error(std::string Message)
	{
		Message = GetCurrTime() + " (Error): " + Message;

		MessagesQueue.PushSafe({ ELogMessageType::Message_Error, Message });
	}

	void Error(std::ostream& Message)
	{
		Error(dynamic_cast<std::ostringstream&>(Message).str());
	}

	void PrintToConsole(std::string& Message, const int Color)
	{
#if defined(_WIN32) || defined(_WIN64)
		// Change color to red
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // text color
		SetConsoleTextAttribute(hConsole, Color);
#endif

		std::cout << Message << std::endl;

#if defined(_WIN32) || defined(_WIN64)
		// Change color back to white
		SetConsoleTextAttribute(hConsole, 7);
#endif
	}
}

