#pragma once

#include "MemoryManager.h"

bool MemoryManager:: check_process(DWORD proc) {
    TCHAR pname[MAX_PATH] = TEXT("<UnKnown>");
    HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, proc);
    if (handle != NULL) {
        HMODULE hMod;
        DWORD cbNeeded;
        if (EnumProcessModules(handle, &hMod, sizeof(hMod), &cbNeeded)) {
            GetModuleBaseName(handle, hMod, pname, sizeof(pname) / sizeof(TCHAR));
        }
        CloseHandle(handle);
    }
    if (!_tcscmp(TEXT(PROCESS_NAME), pname)) {
        this->pid = proc;
        logger->log(INFO, "Process found @ " + std::to_string(proc));
        return true;
    }
    return false;
}

bool MemoryManager::open_process() {
    DWORD proc_list[1024], cbNeeded, number_of_process;
    try {
        if (!EnumProcesses(proc_list, sizeof(proc_list), &cbNeeded)) {
            throw(1);
        }
        number_of_process = cbNeeded / sizeof(DWORD);
        for (unsigned int i = 0; i < number_of_process; i++) {
            if (proc_list[i] != 0) {
                if (check_process(proc_list[i])) {
                    return true;
                }
            }
        }
    }
    catch (int c) {
        switch (c) {
        case 1: {
            logger->log(ERR, "Can't read process list.");
            return false;
            break;
        }
        default: {
            return false;
            break;
        }
        }
        exit(1);
    }
    catch (...) {
        logger->log(ERR, "Error on OpenProcess.\n");
        exit(1);
        return 1;
    }
    return false;
}

MODULEENTRY32 MemoryManager::get_module(const char* mname) {
    HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    MODULEENTRY32 m;
    m.dwSize = sizeof(m);
    const WCHAR* modNameChar;
    int nChars = MultiByteToWideChar(CP_ACP, 0, mname, -1, NULL, 0);
    modNameChar = new WCHAR[nChars];
    MultiByteToWideChar(CP_ACP, 0, mname, -1, (LPWSTR)modNameChar, nChars);

    do {
        if (!wcscmp(m.szModule, modNameChar))
        {
            CloseHandle(h);
            return m;
        }
    }
    while (Module32Next(h, &m));

    CloseHandle(h);
    m.modBaseAddr = 0x0;
    return m;
}

MemoryManager::MemoryManager(Logger* logger) {
    this->logger = logger;
    this->hproc = 0x0;
    this->pid = 0x0;
    try {
        if (!open_process()) {
            throw 1;
        }
        this->hproc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->pid);
        this->engine = get_module(ENGINE_DLL);
        this->client = get_module(CLIENT_DLL);
        this->client_base = (DWORD)this->client.modBaseAddr;
        this->engine_base = (DWORD)this->engine.modBaseAddr;
        
        // For debugging only
        logger->log(INFO, "Client base address is: "+ std::to_string(client_base));
        logger->log(INFO, "Engine base address is: " + std::to_string(engine_base));
        
        if (this->client_base == 0x0) {
            throw 2;
        }
        if (this->engine_base == 0x0) {
            throw 3;
        }

        this->client_size = this->client.dwSize;
        this->engine_size = this->engine.dwSize;
        
        logger->log(INFO, "Client Limite: " + std::to_string(this->client_size));
        logger->log(INFO, "Engine Limite : " + std::to_string(this->engine_size));

    }
    catch (int err) {
        switch (err) {
            case ERR_OPEN_CSGO: {
                logger->log(ERR, "Program is not open. Please open the program and try again.");
                break;
            }
            case ERR_LOAD_ENGINE: {
                logger->log(ERR, "Can't load module Engine.");
                break;
            }
            case ERR_LOAD_CLIENT: {
                logger->log(ERR, "Can't load modele Client.");
            }
        }
        CloseHandle(this->hproc);
        exit(1);
    }
    catch (...) {
        logger->log(ERR, "an unexpected error occurred");
        CloseHandle(this->hproc);
        exit(1);
    }
}

DWORD MemoryManager::get_client_base() {
    return this->client_base;
}

DWORD MemoryManager::get_engine_base() {
    return this->engine_base;
}





MemoryManager::~MemoryManager() {
    
    if (this->hproc != NULL) {
        try {
            CloseHandle(this->hproc);
        }
        catch (...) {
            logger->log(ERR, "Handel to the process was invalid!");
        }
    }

}