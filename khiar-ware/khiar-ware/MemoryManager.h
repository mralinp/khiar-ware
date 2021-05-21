/*
    Memory manager class for our cheat engine.
    We are able to modify process memory using this object.
*/

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <psapi.h>
#include <iostream>

#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#define PROCESS_NAME "csgo.exe"
#define CLIENT_DLL "client.dll"
#define ENGINE_DLL "engine.dll"

#define ERR_NUMBER_OF_PROCESS_EXCIDED 0x0A
#define ERR_OPEN_PROCESS 0x0B
#define ERR_LOAD_ENGINE 0x0C
#define ERR_LOAD_CLIENT 0x0D

#define MAX_PROCESS_NUMBER 2048
#define UNKNOWN_PROCESS_NAME "<UNKNOWN>"

class MemoryManager {
private:
    DWORD _pid;
    HANDLE _hproc;
    MODULEENTRY32 _client, _engine;
    DWORD _clientBase, _clientSize;
    DWORD _engineBase, _engineSize;

    int _checkProcess(DWORD proc);
    int _openProcess();
    MODULEENTRY32 _getModule(const char* moduleName);

public:

    MemoryManager();

    DWORD getClientBaseAddr(); 
    
    template<class type>
    auto read(DWORD dwAddress) {
        type buff{};
        ReadProcessMemory(this->_hproc, (LPVOID)dwAddress, &buff, sizeof(type), NULL);
        return buff;
    }

    template<class type>
    BOOL write(DWORD dwAddress, type ValueToWrite) {
        return WriteProcessMemory(this->_hproc, (LPVOID)dwAddress, &ValueToWrite, sizeof(type), NULL);
    }

    int printModules(DWORD pid);

    ~MemoryManager();
};

#endif // !MEMORYMANAGER_H
