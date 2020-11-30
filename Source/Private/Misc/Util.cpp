#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
#include "Util.h"
#include <chrono>
//#include <filesystem> // or #include <experimental/filesystem> // for creating directory in LogInit()

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif


void SafeQueue::safePush(const Message & value)
{
	while (!m_mutex.try_lock())
	{
		SDL_Delay(1);
	}

	m_queque.push(value);
	m_mutex.unlock();
}

void SafeQueue::safePop()
{
	while (!m_mutex.try_lock())
	{
		SDL_Delay(1);
	}

	m_queque.pop();
	m_mutex.unlock();
}

namespace Util
{
	bool isLoggingEnabled = false;
	int loggingLevel = 1;
	std::string logDir = "log";
	std::string logPrefix = "log_";
	std::string logFilePath = logDir + "/" + logPrefix + GetCurrentTimeNoSpecial();

	bool keepLogging = true;
	SDL_Thread *thread;
	SafeQueue messagesQueue;

	void LogInit(bool enableLogging, int logLevel)
	{
		// @TODO - Create directory error if doesn't exist (Windows only)
		// @TODO - Crossplatform

		if (enableLogging)
		{

// Windows check if log folder exists
#if defined(_WIN32) || defined(_WIN64)
			CreateDirectory(logDir.c_str(), NULL);

			//namespace fs = std::experimental::filesystem;
			//if (!fs::is_directory(logDir) || !fs::exists(logDir)) // Check if folder exists
			//{
			//	// Create folder if not
			//	fs::create_directory(logDir);
			//}
#endif

// Linux
#ifdef linux
// TODO create dir on linux
			Util::Warning("Creating directory on linux isn't implemented yet. Please create one or log will don't be created");
#endif
			isLoggingEnabled = true;
			std::cout << "Logging to: " << logFilePath << std::endl;
		}
		else
		{
			isLoggingEnabled = false;
		}

		loggingLevel = logLevel;

		SDL_CreateThread(MessagesPrinter, "Log", (void *)NULL);
	}

	static int MessagesPrinter(void * ptr)
	{
		while (keepLogging) 
			if (messagesQueue.m_queque.size() <= 0)
			{ 
				SDL_Delay(2);
			}
			else
			{
				switch (messagesQueue.m_queque.front().type)
				{
				case Message_Info:
					PrintToConsole(messagesQueue.m_queque.front().text, 7);
					break;

				case Message_Debug:
#ifdef _DEBUG
					PrintToConsole(messagesQueue.m_queque.front().text, 5);
#endif // _DEBUG
					break;

				case Message_Warning:
					PrintToConsole(messagesQueue.m_queque.front().text, 6);
					break;

				case Message_Error:
					PrintToConsole(messagesQueue.m_queque.front().text, 4);
					break;

				default:
					// Should be impossible (infinite loop may happen)
					
					break;
				}

				if (isLoggingEnabled)
				{
					std::ofstream LogFile;
					LogFile.open(logFilePath, std::ios_base::app);
					LogFile << messagesQueue.m_queque.front().text << std::endl;
					LogFile.close();
				}

				// Remove item
				messagesQueue.safePop();
			}

		return 0;
	}

	/* Return current Milisecond */
	inline long long int GetMiliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	/* Starts delay you need variable long long int and pass it as reference */
	void startDelay(long long int &startMs)
	{
		startMs = GetMiliseconds();
	}

	bool isDelayed(long long int &startMs, long int &delayMs)
	{
		if (GetMiliseconds() >= startMs + delayMs)
			return true;

		return false;
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

	void Info(std::string message) 
	{
		message = GetCurrTime() + " (Info): " + message;
		
		messagesQueue.safePush({ Message_Info , message });
	}

	void Debug(std::string message) 
	{
#ifdef _DEBUG // if debug
		message = GetCurrTime() + " (Debug): " + message;

		messagesQueue.safePush({ Message_Debug , message });
#endif
	}

	void Warning(std::string message) 
	{
		message = GetCurrTime() + " (Warning): " + message;
		
		messagesQueue.safePush({ Message_Warning , message });
	}

	void Error(std::string message) 
	{
		message = GetCurrTime() + " (Error): " + message;
		
		messagesQueue.safePush({ Message_Error , message });
	}

	void PrintToConsole(std::string &message, int color)
	{
#if defined(_WIN32) || defined(_WIN64)
		// Change color to red
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // text color
		SetConsoleTextAttribute(hConsole, color);
#endif

		std::cout << message << std::endl;

#if defined(_WIN32) || defined(_WIN64)
		// Change color back to white
		SetConsoleTextAttribute(hConsole, 7);
#endif
	}
}

