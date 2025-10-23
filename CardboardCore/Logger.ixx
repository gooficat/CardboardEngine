#include <ctime>

export module Logger;

import std;

import <chrono>;

import <Windows.h>;


export enum LogType {
	LOG_MESSAGE,
	LOG_WARN,
	LOG_ERROR,
	LOG_CRITICAL
};

// eventually if I need multithreaded logging, perhaps
//export class LogMessage {
//public:
//	std::string message;
//	LogType type;
//};

export class Logger {
public:
	Logger(const std::string& file_path) {
		log_file.open(file_path);
		console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	~Logger() {
		log_file.close();
	}
	void log(const std::string& message, const LogType& type) {
		auto time = std::chrono::system_clock::now();
		std::time_t realtime = std::chrono::system_clock::to_time_t(time);

		char timebuf[60] = { 0 };
		ctime_s(&timebuf[0], sizeof(timebuf), &realtime);

		std::string type_str;

		switch (type) {
		case LOG_MESSAGE:
			type_str = "MESSAGE";
			SetConsoleTextAttribute(console_handle, FOREGROUND_BLUE);
			break;
		case LOG_WARN:
			SetConsoleTextAttribute(console_handle, FOREGROUND_RED | FOREGROUND_BLUE);
			type_str = "WARNING";
			break;
		case LOG_ERROR:
			SetConsoleTextAttribute(console_handle, FOREGROUND_RED | FOREGROUND_GREEN);
			type_str = "ERROR";
			break;
		case LOG_CRITICAL:
			SetConsoleTextAttribute(console_handle, FOREGROUND_RED);
			type_str = "CRITICAL";
			break;
		}

		std::string log = timebuf + type_str + '\n' + message;

		std::cout << log << std::endl;

		log_file << log << "\n\n";
		SetConsoleTextAttribute(console_handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
private:
	std::ofstream log_file;
	HANDLE console_handle;
	// only if I add multithreaded logging
	//std::vector<LogMessage> log_queue;
};