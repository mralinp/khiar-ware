#pragma once

#define PROCESS_NAME "csgo.exe"
#define CLIENT_DLL "client_panorama.dll"
#define ENGINE_DLL "engine.dll"

class MemoryManager {

	DWORD pid;
	HANDLE hproc;
    MODULEENTRY32 engine, client;
    DWORD client_base, client_size, engine_base, engine_size;

    bool check_process(DWORD proc) {
        TCHAR pname[MAX_PATH] = TEXT("<UnKnown>");
        HANDLE h = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, proc);
        if (NULL != h) {
            HMODULE hMod;
            DWORD cbNeeded;
            if (EnumProcessModules(h, &hMod, sizeof(hMod), &cbNeeded)) {
                GetModuleBaseName(h, hMod, pname, sizeof(pname) / sizeof(TCHAR));
            }
        }
        if (h != 0) {
            CloseHandle(h);
        }
        if (!_tcscmp(TEXT(PROCESS_NAME), pname)) {
            this->pid = proc;
            _tprintf(TEXT("Process found @ %s  (PID: %u)\n"), pname, proc);
            return true;
        }
        return false;
    }

    bool open_process() {
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
                    printf("Can't read process list.\n");
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
            printf("Unhandled Error detected.\n");
            exit(1);
            return 1;
        }
        return false;
    }

    MODULEENTRY32 get_module(const char* mname) {
        HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
        MODULEENTRY32 m;
        m.dwSize = sizeof(m);
        const WCHAR* modNameChar;
        int nChars = MultiByteToWideChar(CP_ACP, 0, mname, -1, NULL, 0);
        modNameChar = new WCHAR[nChars];
        MultiByteToWideChar(CP_ACP, 0, mname, -1, (LPWSTR)modNameChar, nChars);

        do
            if (!wcscmp(m.szModule, modNameChar))
            {
                CloseHandle(h);
                return m;
            }
        while (Module32Next(h, &m));

        CloseHandle(h);
        m.modBaseAddr = 0x0;
        return m;
    }

public:

    MemoryManager() {
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
            printf_s("client base addr: %d, engine base addr: %d\n", client_base, engine_base);
            if (this->client_base == 0x0) {
                throw 2;
            }
            if (this->engine_base == 0x0) {
                throw 3;
            }
            this->client_size = this->client.dwSize;
            this->engine_size = this->engine.dwSize;
            printf_s("client size: %d, engine size: %d\n", client_size, engine_size);
        }
        catch (int c) {
            switch (c) {
            case 1: {
                printf_s("Process %s not found, Please open csgo and try again.\n", PROCESS_NAME);
                break;
            }
            case 2: {
                printf_s("can't open module %s.\n", ENGINE_DLL);
                break;
            }
            case 3: {
                printf_s("can't open module %s.\n", CLIENT_DLL);
            }
            }
            exit(1);
        }
        catch (...) {
            printf_s("unhandled exception occurred\n");
            exit(1);
        }
    }

    DWORD get_client_base() {
        return this->client_base;
    }
    DWORD get_engine_base() {
        this->engine_base;
    }

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


    ~MemoryManager() {
        if (this->hproc != NULL) {
            try {
                CloseHandle(this->hproc);
            }
            catch (...) {
                printf_s("error in distructor... handel to the process is invalid!");
            }
        }
    }
};