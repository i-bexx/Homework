#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

// Ba�l� liste d���m�
typedef struct LogNode {
    char message[MAX_LINE];
    struct LogNode* next;
} LogNode;

// Yeni bir log d���m� olu�turur
LogNode* createNode(char* message) {
    LogNode* newNode = (LogNode*)malloc(sizeof(LogNode)); // Bellekten yeni bir d���m i�in yer ay�r�r
    if (!newNode) {
        perror("Bellek tahsisi ba�ar�s�z");
        exit(EXIT_FAILURE);
    }
    strncpy(newNode->message, message, MAX_LINE); // Mesaj� d���me kopyalar
    newNode->next = NULL; // Yeni d���m�n ba�lant�s�n� ba�ta bo� b�rak�r
    return newNode;
}

// Loglar� ba�l� listeye ekler
void addLog(LogNode** head, char* message) {
    LogNode* newNode = createNode(message);
    newNode->next = *head;
    *head = newNode;
}

// Loglar� ekrana yazd�r�r
void printLogs(LogNode* head) {
    LogNode* temp = head;
    while (temp) {
        printf("%s", temp->message);
        temp = temp->next;
    }
}

// Haf�zay� temizler (malloc ile ayr�lan belle�i serbest b�rak�r)
void freeList(LogNode* head) {
    LogNode* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp); // D���mleri serbest b�rak�r
    }
}

int main() {
    FILE* file = fopen("/var/log/syslog", "r"); // Syslog dosyas�n� okumak i�in a�ar
    if (!file) {
        perror("Dosya a��lamad�");
        return EXIT_FAILURE;
    }

    LogNode* logList = NULL;
    char line[MAX_LINE];

    while (fgets(line, MAX_LINE, file)) { // Dosyadan sat�r sat�r okur
        addLog(&logList, line);
    }

    fclose(file); // Dosyay� kapat�r

    printf("=== SYSLOG KAYITLARI ===\n");
    printLogs(logList);

    freeList(logList); // Ba�l� listedeki d���mleri ve belle�i temizler

    return 0;
}

