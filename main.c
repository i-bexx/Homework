#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

// Baðlý liste düðümü
typedef struct LogNode {
    char message[MAX_LINE];
    struct LogNode* next;
} LogNode;

// Yeni bir log düðümü oluþturur
LogNode* createNode(char* message) {
    LogNode* newNode = (LogNode*)malloc(sizeof(LogNode)); // Bellekten yeni bir düðüm için yer ayýrýr
    if (!newNode) {
        perror("Bellek tahsisi baþarýsýz");
        exit(EXIT_FAILURE);
    }
    strncpy(newNode->message, message, MAX_LINE); // Mesajý düðüme kopyalar
    newNode->next = NULL; // Yeni düðümün baðlantýsýný baþta boþ býrakýr
    return newNode;
}

// Loglarý baðlý listeye ekler
void addLog(LogNode** head, char* message) {
    LogNode* newNode = createNode(message);
    newNode->next = *head;
    *head = newNode;
}

// Loglarý ekrana yazdýrýr
void printLogs(LogNode* head) {
    LogNode* temp = head;
    while (temp) {
        printf("%s", temp->message);
        temp = temp->next;
    }
}

// Hafýzayý temizler (malloc ile ayrýlan belleði serbest býrakýr)
void freeList(LogNode* head) {
    LogNode* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp); // Düðümleri serbest býrakýr
    }
}

int main() {
    FILE* file = fopen("/var/log/syslog", "r"); // Syslog dosyasýný okumak için açar
    if (!file) {
        perror("Dosya açýlamadý");
        return EXIT_FAILURE;
    }

    LogNode* logList = NULL;
    char line[MAX_LINE];

    while (fgets(line, MAX_LINE, file)) { // Dosyadan satýr satýr okur
        addLog(&logList, line);
    }

    fclose(file); // Dosyayý kapatýr

    printf("=== SYSLOG KAYITLARI ===\n");
    printLogs(logList);

    freeList(logList); // Baðlý listedeki düðümleri ve belleði temizler

    return 0;
}

