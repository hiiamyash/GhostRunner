# ![GhostRunner - Process Injection Toolkit](https://via.placeholder.com/800x200?text=GhostRunner+Process+Injection+Toolkit)

A comprehensive **process injection toolkit** written in C++ that implements various advanced code injection techniques for **educational and research purposes**.  

> ⚠️ **Disclaimer**: This tool is for educational purposes only.  
> Use only on systems you own or have explicit permission to test.  
> Unauthorized use is illegal.  

---

## Features

- **DLL Injection** – Classic LoadLibrary-based injection  
- **PE Injection** – Direct portable executable injection  
- **Thread Execution Hijacking** – Hijack existing threads  
- **Extra Window Memory Injection (EWMI)** – Use window properties for injection  
- **Process Hollowing** – Replace process memory with payload  
- **Process Doppelgänging** – Advanced process creation technique  

---

## Prerequisites

- Windows OS (7/8/10/11)  
- Visual Studio or MinGW compiler  
- Administrator privileges  
- Windows SDK (for some advanced features)  

---

## Installation

Clone the repository:

```bash
git clone https://github.com/yourusername/ghostrunner.git
cd ghostrunner
```

### Compile the project

**Using Visual Studio**:  
- Open the solution file and build the project  

**Using MinGW**:  
```bash
g++ -o ghostrunner.exe main.cpp -lntdll -ldbghelp -static
```

---

## Usage

Run GhostRunner from an elevated command prompt:  

```bash
ghostrunner.exe
```

You'll be presented with a **menu to select the injection technique**.  

---

## Attack Techniques Guide

### 1. DLL Injection
- **Description**: Classic injection using `LoadLibrary`.  
- **How it works**:
  - Allocate memory in target process  
  - Write DLL path to allocated memory  
  - Create a remote thread that calls `LoadLibrary`  

---

### 2. PE Injection
- **Description**: Injects a full portable executable (EXE) into another process.  
- **How it works**:
  - Parse PE headers  
  - Allocate memory in target process  
  - Copy PE sections into memory  
  - Execute entry point  

---

### 3. Thread Execution Hijacking
- **Description**: Redirects execution of an existing thread.  
- **How it works**:
  - Find a thread in the target process  
  - Suspend the thread  
  - Change context to shellcode  
  - Resume execution  

---

### 4. Extra Window Memory Injection (EWMI)
- **Description**: Uses window properties/messages for injection.  
- **How it works**:
  - Find window owned by target process  
  - Store shellcode in window properties  
  - Trigger execution with window messages  

---

### 5. Process Hollowing
- **Description**: Replace a legitimate process’s memory with payload.  
- **How it works**:
  - Create a process in suspended state  
  - Unmap original memory  
  - Write malicious payload  
  - Resume execution  

---

### 6. Process Doppelgänging
- **Description**: Uses NTFS transactions for stealthy process creation.  
- **How it works**:
  - Create transacted file operations  
  - Create process from transactional file  
  - Run payload while appearing legitimate  

---

## Detection Evasion

GhostRunner uses several stealth techniques:
- Direct system calls (where implemented)  
- Avoidance of suspicious API calls  
- Memory-only payloads  
- Legitimate process spoofing  

---

## Defense Recommendations

To defend against such attacks:  
- Use modern EDR/AV with **behavioral detection**  
- Implement **application whitelisting**  
- Restrict **administrator privileges**  
- Monitor **unusual process behavior**  
- Use **process integrity levels** and sandboxing  

---

## Contributing

Contributions are welcome!  
- Submit a Pull Request  
- Open Issues for discussion  

---

## License

This project is licensed under the **MIT License** – see the [LICENSE](LICENSE) file for details.  

---

## Acknowledgments

- Inspired by various security researchers studying process injection  
- Developed strictly for **educational purposes**  
- Always obtain proper **authorization** before testing  
