# GhostRunner

GhostRunner is a post-exploitation tool designed to demonstrate advanced process injection techniques. It allows security researchers and red teamers to experiment with different methods of code injection against live processes in controlled environments.

⚠️ **Disclaimer:** GhostRunner is for **educational and research purposes only**. Use it only in lab environments or systems you are explicitly authorized to test. Misuse may violate laws and result in severe consequences.

---

# 📺 Demo Video

[![Watch the video](https://img.youtube.com/vi/_P7Kp50mX14/maxresdefault.jpg)](https://youtu.be/_P7Kp50mX14?si=l9Qfi7xZtBQxgCpZ)


## ✨ Features

- **DLL Injection** – Load custom DLLs into a remote process.
- **Shellcode Injection** – Inject and execute raw shellcode.
- **APC Injection** – Queue shellcode execution in target process threads.
- **Process Hollowing** – Replace the code of a legitimate process with a malicious payload.

---

## 🚀 Techniques & Usage

### 🔹 DLL Injection
Injects a DLL into the specified process using the LoadLibrary technique.

```
ghostrunner.exe dll <PID> <DLL_PATH>
```
### 🔹 Shellcode Injection
Injects raw shellcode into the specified process and executes it.
```
ghostrunner.exe shellcode <PID> <SHELLCODE_PATH>
```
### 🔹 APC Injection
Uses Asynchronous Procedure Calls (APC) to inject shellcode into threads of the target process.
```
ghostrunner.exe apc <PID> <SHELLCODE_PATH>
```
### 🔹 Process Hollowing
Launches a legitimate process in a suspended state, replaces its memory with a malicious executable, and resumes execution.
```
ghostrunner.exe hollow <TARGET_EXE> <PAYLOAD_EXE>
```
---

## 📥 Download

You can download the latest release of GhostRunner from the releases page:

➡️ [GhostRunner Release Page](https://github.com/hiiamyash/GhostRunner/releases/tag/malware)

---

## ⚖️ Legal Notice

This tool is intended strictly for:

- Red Team assessments  
- Security research  
- Educational demonstrations in authorized labs  

Do **NOT** use GhostRunner for malicious activity. The authors and contributors are **not responsible** for any misuse or damage caused by this tool.

---
