#include <stdio.h>
#include <stdlib.h>
#include "common.h"


void showMenu() {

    printf("   _____ _               _   _____                             \n");
    printf("  / ____| |             | | |  __ \\                            \n");
    printf(" | |  __| |__   ___  ___| |_| |__) |   _ _ __  _ __   ___ _ __ \n");
    printf(" | | |_ | '_ \\ / _ \\/ __| __|  _  / | | | '_ \\| '_ \\ / _ \\ '__|\n");
    printf(" | |__| | | | | (_) \\__ \\ |_| | \\ \\ |_| | | | | | | |  __/ |   \n");
    printf("  \\_____|_| |_|\\___/|___/\\__|_|  \\_\\__,_|_| |_|_| |_|\\___|_|   \n");
    printf("                                                               \n");
    printf("                                                               \n\n\n");

    printf("\nGhostRunner CLI Menu:\n\n");
    printf("Choose module to run:\n");
    printf("1. DLL Injection\n");
    printf("2. Process Hollowing\n");
    printf("3. Remote Thread Injection\n");
    printf("4. Token Stealing\n");
    printf("5. Anti-Debug/Stealth Checks\n");
    printf("6. HTA Loader\n");
    printf("7. Office Macro Dropper\n");
    printf("8. LNK Shortcut Creator\n");
    printf("9. Startup Folder Persistence\n");
    printf("10. Service Path Hijack\n");
    printf("11. USB Worm Dropper\n");
    printf("12. WebDAV/UNC Execution\n");
    printf("13. Exit\n");
    
}

int main() {
    int choice = 0;

    while (choice != 13) {
        showMenu();
        printf("[*] Choose an option: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            // case 1: run_dll_injection(); break;
            // case 2: run_process_hollowing(); break;
            // case 3: run_remote_thread(); break;
            // case 4: run_token_stealing(); break;
            // case 5: run_anti_debug(); break;
            case 13: printf("[*] Exiting GhostRunner...\n"); break;
            default: printf("[-] Invalid option.\n"); break;
        }
    }
    return 0;

}