//#pragma once
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <tlhelp32.h>

#define GAME_NAME "csgo.exe"
#define CLIENT_DLL "client_panorama.dll"
#define ENGINE_DLL "engine.dll"

class memory_manager {
private:
    HANDLE hProcc;
    DWORD pid;

    int getProcessNameAndID(DWORD processID) {
        TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
        if (NULL != hProcess) {
            HMODULE hMod;
            DWORD cbNeeded;
            if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
                GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
            }
        }
        CloseHandle(hProcess);
        if (!_tcscmp(TEXT(GAME_NAME), szProcessName)) {
            this->pid = processID;
            _tprintf(TEXT("found @ %s  (PID: %u)\n"), szProcessName, processID);
            return 0;
        }
        return 1;
    }

    int get_cProcessList() {
        DWORD aProcesses[1024], cbNeeded, cProcesses;
        try {
            if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
                throw("Error code: <0x01>");
            }
            cProcesses = cbNeeded / sizeof(DWORD);
            for (unsigned int i = 0; i < cProcesses; i++) {
                if (aProcesses[i] != 0) {
                    if (!getProcessNameAndID(aProcesses[i])) {
                        return 0;
                    }
                }
            }
        }
        catch (...) {
            printf("Error Getting Process ids. \n");
            return 1;
        }
        return 1;
    }
public:
    MODULEENTRY32 ClientDLL;
    MODULEENTRY32 EngineDLL;
    DWORD ClientDLL_Base, ClientDLL_Size;
    DWORD EngineDLL_Base, EngineDLL_Size;

    /*bool AttachProcess(char* ProcessName){
        HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        const WCHAR* procNameChar;
        int nChars = MultiByteToWideChar(CP_ACP, 0, ProcessName, -1, NULL, 0);
        procNameChar = new WCHAR[nChars];
        MultiByteToWideChar(CP_ACP, 0, ProcessName, -1, (LPWSTR)procNameChar, nChars);

        do
            if (!wcscmp(procEntry.szExeFile, procNameChar))
            {
                this->pid = procEntry.th32ProcessID;
                CloseHandle(hPID);
                this->hProcc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->pid);
                return true;
            }
        while (Process32Next(hPID, &procEntry));

        CloseHandle(hPID);
        return false;
    }*/

    MODULEENTRY32 GetModule(const char* ModuleName){
        HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
        MODULEENTRY32 mEntry;
        mEntry.dwSize = sizeof(mEntry);

        const WCHAR* modNameChar;
        int nChars = MultiByteToWideChar(CP_ACP, 0, ModuleName, -1, NULL, 0);
        modNameChar = new WCHAR[nChars];
        MultiByteToWideChar(CP_ACP, 0, ModuleName, -1, (LPWSTR)modNameChar, nChars);

        do
            if (!wcscmp(mEntry.szModule, modNameChar))
            {
                CloseHandle(hModule);
                return mEntry;
            }
        while (Module32Next(hModule, &mEntry));

        CloseHandle(hModule);
        mEntry.modBaseAddr = 0x0;
        return mEntry;
    }

    template<class c>
    c Read(DWORD dwAddress)
    {
        c val;
        ReadProcessMemory(hProcc, (LPVOID)dwAddress, &val, sizeof(c), NULL);
        return val;
    }

    template<class c>
    BOOL Write(DWORD dwAddress, c ValueToWrite)
    {
        return WriteProcessMemory(hProcc, (LPVOID)dwAddress, &ValueToWrite, sizeof(c), NULL);
    }

    DWORD GetProcID() { return this->pid; }
    HANDLE GetProcHandle() { return this->hProcc; }

    memory_manager(){
        this->hProcc = NULL;
        this->pid = NULL;
        try {
            if (get_cProcessList()) throw 1;
            this->hProcc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->pid);
            this->ClientDLL = GetModule(CLIENT_DLL);
            this->EngineDLL = GetModule(ENGINE_DLL);
            this->ClientDLL_Base = (DWORD)this->ClientDLL.modBaseAddr;
            this->EngineDLL_Base = (DWORD)this->EngineDLL.modBaseAddr;
            printf("%d, %d", ClientDLL_Base, EngineDLL_Base);
            
            if (this->ClientDLL_Base == 0x0) throw 2;
            if (this->EngineDLL_Base == 0x0) throw 3;
            this->ClientDLL_Size = this->ClientDLL.dwSize;
            this->EngineDLL_Size = this->EngineDLL.dwSize;
        }
        catch (int iEx) {
            switch (iEx)
            {
            case 1: printf("CS:GO must be running"); break;
            case 2: printf("Couldn't find Client.dll"); break;
            case 3: printf("Couldn't find Engine.dll"); break;
            default: throw;
            }
        }
        catch (...) {
            printf("Unhandled exception thrown");
        }
        printf("Handles Successfuly created.\n");
    }
    ~memory_manager()
    {
        CloseHandle(this->hProcc);
    }
};
