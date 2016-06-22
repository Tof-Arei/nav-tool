#pragma once

class LogEntry
{
	public:
		// variables
		char* engineName;
		double jumpRange;
		char* systemName;
		NavEntry* position;
		// functions
		bool LoadFile(System::String^ inFileName, System::String^ saveDataFormat);
		LogEntry(void);
		~LogEntry(void);
		void SetName(char* inName);
};
