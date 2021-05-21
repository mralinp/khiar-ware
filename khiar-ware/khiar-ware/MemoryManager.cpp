#include "MemoryManager.h"

int MemoryManager:: _checkProcess(DWORD proc) {
    TCHAR pname[MAX_PATH] = TEXT(UNKNOWN_PROCESS_NAME);
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
        this->_pid = proc;
        return 0;
    }
    return 1;
}

int MemoryManager:: _openProcess() {
    DWORD procList[MAX_PROCESS_NUMBER], cbNeeded, numProcess;
    if (!EnumProcesses(procList, sizeof(procList), &cbNeeded)) {
        return ERR_NUMBER_OF_PROCESS_EXCIDED;
    }
    numProcess = cbNeeded / sizeof(DWORD);
    for (unsigned int i = 0; i < numProcess; i++) {
        if (procList[i] != 0) {
            if (!this->_checkProcess(procList[i])) {
                return 0;
            }
        }
    }
    return 1;
}

MODULEENTRY32 MemoryManager:: _getModule(const char* moduleName) {
    HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->_pid);
    MODULEENTRY32 m{};
    m.dwSize = sizeof(m);
    const WCHAR* modNameChar;
    int nChars = MultiByteToWideChar(CP_ACP, 0, moduleName, -1, NULL, 0);
    modNameChar = new WCHAR[nChars];
    MultiByteToWideChar(CP_ACP, 0, moduleName, -1, (LPWSTR)modNameChar, nChars);

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

MemoryManager::MemoryManager() {
    this->_pid = 0x0;
    try {
        if (this->_openProcess()) {
            throw ERR_OPEN_PROCESS;
        }
        this->_hproc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->_pid);
        this->_client = this->_getModule(CLIENT_DLL);
        this->_clientBase = (DWORD)this->_client.modBaseAddr;
        if (this->_clientBase == 0x0) {
            throw 2;
        }
        this->_engine = this->_getModule(ENGINE_DLL);
        this->_engineBase = (DWORD)this->_engine.modBaseAddr;
        if (this->_engineBase == 0x0) {
            throw 3;
        }
        this->_clientSize = this->_client.dwSize;
        this->_engineSize = this->_engine.dwSize;
    }
    catch ( int err ) {
        if (err == ERR_OPEN_PROCESS)
            std::cout << "ERROR: " << "Program is not open. Please open the program and try again." << std::endl;
        else if (err == ERR_LOAD_ENGINE)
            std::cout << "ERROR: " << "Can't load module Engine." << std::endl;
        else if (err == ERR_LOAD_CLIENT)
            std::cout << "ERROR: "<< "Can't load modele Client." << std::endl;
        CloseHandle(this->_hproc);
        exit(1);
    }
    catch (...) {
        std::cout << "ERROR: " << "an unexpected error occurred" << std::endl;
        CloseHandle(this->_hproc);
        exit(2);
    }
}

DWORD MemoryManager::getClientBaseAddr() {
    return this->_clientBase;
}


/*
    For debugging only.
*/
int MemoryManager::printModules(DWORD pid) {
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me32;

    //  Take a snapshot of all modules in the specified process. 
    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    if (hModuleSnap == INVALID_HANDLE_VALUE)
    {
        std::cout <<"CreateToolhelp32Snapshot (of modules)" << std::endl;
        return(FALSE);
    }

    //  Set the size of the structure before using it. 
    me32.dwSize = sizeof(MODULEENTRY32);

    //  Retrieve information about the first module, 
    //  and exit if unsuccessful 
    if (!Module32First(hModuleSnap, &me32))
    {
        std::cout << "Module32First" << std::endl;  // Show cause of failure 
        CloseHandle(hModuleSnap);     // Must clean up the snapshot object! 
        return(FALSE);
    }

    //  Now walk the module list of the process, 
    //  and display information about each module 
    do
    {
        _tprintf(TEXT("\n\n     MODULE NAME:     %s"), me32.szModule);
        _tprintf(TEXT("\n     executable     = %s"), me32.szExePath);
        _tprintf(TEXT("\n     process ID     = 0x%08X"), me32.th32ProcessID);
        _tprintf(TEXT("\n     ref count (g)  =     0x%04X"), me32.GlblcntUsage);
        _tprintf(TEXT("\n     ref count (p)  =     0x%04X"), me32.ProccntUsage);
        _tprintf(TEXT("\n     base address   = 0x%08X"), (DWORD)me32.modBaseAddr);
        _tprintf(TEXT("\n     base size      = %d"), me32.modBaseSize);

    } while (Module32Next(hModuleSnap, &me32));

    _tprintf(TEXT("\n"));

    //  Do not forget to clean up the snapshot object. 
    CloseHandle(hModuleSnap);
    return(TRUE);
}


MemoryManager::~MemoryManager() {
    
    if (this->_hproc != NULL) {
        try {
            CloseHandle(this->_hproc);
        }
        catch (...) {
            std::cout << "Error closing handle to process." << std::endl;
        }
    }

}