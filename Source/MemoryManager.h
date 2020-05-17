#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <psapi.h>
#include "Logger.h"

#define PROCESS_NAME "csgo.exe"
#define CLIENT_DLL "client_panorama.dll"
#define ENGINE_DLL "engine.dll"
#define ERR_OPEN_CSGO 1
#define ERR_LOAD_ENGINE 2
#define ERR_LOAD_CLIENT 3


class MemoryManager {
private:
    Logger* logger;
    DWORD pid;
    HANDLE hproc;
    MODULEENTRY32 engine, client;
    DWORD client_base, client_size, engine_base, engine_size;

    bool check_process(DWORD proc);
    bool open_process();
        
    MODULEENTRY32 get_module(const char* mname);

public:

    MemoryManager(Logger* logger);

    DWORD get_client_base(); 
    DWORD get_engine_base(); 

    template<class c>
    c read(DWORD dwAddress) {
        c val;
        ReadProcessMemory(this->hproc, (LPVOID)dwAddress, &val, sizeof(c), NULL);
        return val;
    }

    template<class c>
    BOOL write(DWORD dwAddress, c ValueToWrite) {
        return WriteProcessMemory(this->hproc, (LPVOID)dwAddress, &ValueToWrite, sizeof(c), NULL);
    }
    ~MemoryManager();
};