# GhostRunner - Advanced Process Injection Toolkit

![GhostRunner Banner]([https://i.imgur.com/JkQ2Z4f.png](https://th.bing.com/th/id/OIP.Z22EvgQou-Temet-QeuE2gHaEo?w=258&h=180&c=7&r=0&o=7&cb=iwp1&dpr=1.3&pid=1.7&rm=3))

GhostRunner is a powerful CLI tool designed for security professionals and researchers to demonstrate and analyze various process injection techniques on Windows systems.

## Features

- **DLL Injection**: Inject dynamic libraries into running processes
- **Process Listing**: View all running processes with PIDs
- **Multi-DLL Support**: Inject multiple DLLs in a single operation
- **Error Handling**: Detailed error reporting for troubleshooting
- **Stealth Operations**: Minimal process disruption during injection

## How It Works

GhostRunner uses Windows API functions to perform its operations:

### DLL Injection Process
1. **Process Selection**:
   - Lists all running processes using `CreateToolhelp32Snapshot`
   - Allows user to select target process by PID

2. **Memory Allocation**:
   - Opens target process with `OpenProcess`
   - Allocates remote memory with `VirtualAllocEx`

3. **DLL Path Writing**:
   - Writes DLL path to target process using `WriteProcessMemory`

4. **Thread Creation**:
   - Locates `LoadLibraryA` in kernel32.dll
   - Creates remote thread with `CreateRemoteThread` to load the DLL

5. **Verification**:
   - Checks thread exit code to verify successful injection

## Prerequisites

- Windows 7 or later (32-bit or 64-bit)
- Visual Studio 2019 or later (for compilation)
- Administrator privileges (for process injection)

## Installation

```bash
# Clone the repository
https://github.com/hiiamyash/GhostRunner
cd GhostRunner

# Compile using Visual Studio
msbuild GhostRunner.sln /p:Configuration=Release
