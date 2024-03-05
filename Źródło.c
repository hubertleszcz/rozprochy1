#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


struct listNode {
    char* data;
    struct listNode* prev;
    struct listNode* next;
};
size_t getline(char** lineptr, size_t* n, FILE* stream) {
    char* bufptr = NULL;
    char* p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while (c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}

struct listNode* insert(struct listNode* head, char* temporaryBuffer) {
    struct listNode* newNode = head->next;

    if (newNode == NULL) {
        newNode = (struct listNode*)malloc(sizeof(struct listNode));
        newNode->data = (char*)malloc((strlen(temporaryBuffer) + 1) * sizeof(char));
        strcpy(newNode->data, temporaryBuffer);
        newNode->prev = head;
        newNode->next = NULL;
    }
    else {
        if (strcmp(newNode->data, temporaryBuffer) > 0) {
            newNode->next = insert(newNode, temporaryBuffer);
        }
        else {
            newNode->prev = (struct listNode*)malloc(sizeof(struct listNode));
            newNode = newNode->prev;
            newNode->data = (char*)malloc((strlen(temporaryBuffer)+1) * sizeof(char));
            strcpy(newNode->data, temporaryBuffer);
            newNode->prev = head;
            newNode->next = head->next;
        }

    }

    return newNode;
}

void deleteNode(struct listNode* head, int deletedNode) {
    struct listNode* current = head;
    for (int i = 0; i < deletedNode; i++) {
        current = current->next;
        if (current == NULL) return;
    }
    free(current->data);
    current->prev->next = current->next;
    current->next->prev = current->prev;
    current->next = NULL;
    current->prev = NULL;
    free(current);
}






void freeMemory(struct listNode* head) {
    struct listNode* nextNode;
    struct listNode* current = head->next;
    while (current != NULL) {
        nextNode = current->next;
        free(current->data); 
        free(current);
        current = nextNode; 
    }

    free(head);
}

void printOut(struct listNode* head) {
    struct listNode* current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}


int main() {
    //lista 2kierunkowa
    //napisy
    //jak dodajesz to alfabetycznie malejaco    
    // insert i delete
    //max 100 znakow
    int deletedNode, ongoing = 1;
    size_t stringLength, newLength;
    int choice;
    struct listNode* head = (struct listNode*)malloc(sizeof(struct listNode));
    head->next = NULL;
    head->prev = NULL;
    while (ongoing) {
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            stringLength = 100;
            char* temporaryBuffer = (char*)malloc(stringLength * sizeof(char));
            newLength = getline(&temporaryBuffer, &stringLength, stdin);
            head->next = insert(head, temporaryBuffer);
            free(temporaryBuffer);
            break;
        case 2:
            scanf("%d", &deletedNode);
            deleteNode(head, deletedNode);
            break;
        case 3:
            printOut(head->next);
            break;
        case 0:
            ongoing = 0;
            break;
        }
    }

    freeMemory(head);
    return 0;
}