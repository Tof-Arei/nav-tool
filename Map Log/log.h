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
		bool LoadFile(System::String^ inFileName);
		LogEntry(void);
		~LogEntry(void);
		void SetName(char* inName);
};
