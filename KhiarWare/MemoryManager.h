//#pragma once
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <tchar.h>
#include <psapi.h>

#define GAME_NAME "csgo.exe"

class memory_manager {
private:
    //const TCHAR szProcessName[MAX_PATH] = TEXT("csgo.exe");
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

        //_tprintf(TEXT("%s  (PID: %u)\n"), szProcessName, processID);
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
            _tprintf(TEXT("Error Getting Process ids. \n"));
        }
        return 1;
    }
public:
    memory_manager() {
        if (!get_cProcessList()) {
            _tprintf(TEXT("Process found @ pid=%d\n"), this->pid);
        }
        else {
            _tprintf(TEXT("Error: Process Not found Please lunch the game and try again."));
        }
    }
};
