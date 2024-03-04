#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


struct listNode{
    char* data;
    struct listNode* prev;
    struct listNode* next;
};




void deleteNode(struct listNode* head, int deletedNode){
    struct listNode* current = head;
    for(int i=0;i<deletedNode;i++){
        current = current->next;
        if(current==NULL) return;
    }
    free(current->data);
    current->prev->next = current->next;
    current->next->prev = current->prev;
    current->next = NULL;
    current->prev = NULL;
    free(current);
}


void freeMemory(struct listNode* head) {
    struct listNode* curr = head->next;
    struct listNode* next;

    while (curr != NULL) {
        next = curr->next; 
        free(curr->data); 
        free(curr); 
        curr = next;
    }
    head->next = NULL;
    free(head);
}
void printOut(struct listNode* head){
    struct listNode* current = head;
    while(current != NULL){
        printf("%s", current->data);
        current = current->next;
    }
}

struct listNode* insert(struct listNode* head, char* temporaryBuffer){
	struct listNode* newNode = head->next;
    
    if(newNode == NULL){
        newNode = (struct listNode*)malloc(sizeof(struct listNode));
        newNode->data = (char*)malloc(strlen(temporaryBuffer));
        strcpy(newNode->data, temporaryBuffer);
        newNode->prev = head;
        newNode->next = NULL;
    }
    else{
        if(strcmp(newNode->data,temporaryBuffer)>0){
            newNode->next = insert(newNode, temporaryBuffer);
        }        
        else{
            
            newNode->prev = (struct listNode*)malloc(sizeof(struct listNode));
            newNode = newNode->prev;
            newNode->data = (char*)malloc(strlen(temporaryBuffer));
            strcpy(newNode->data, temporaryBuffer);
            newNode->prev = head;
            newNode->next = head->next;
        }

    }

    return newNode;
}

int main(){
    int deletedNode, ongoing = 1;
    size_t stringLength, newLength;
	int choice;
    struct listNode* head = (struct listNode*)malloc(sizeof(struct listNode));
    head->next = NULL;
    head->prev = NULL;
    while(ongoing){
        scanf("%d", &choice);
        switch(choice){
            case 1:
                stringLength = 100;
	            char* temporaryBuffer = (char*)malloc(stringLength*sizeof(char));
                newLength = getline(&temporaryBuffer, &stringLength, stdin);
                head->next = insert(head, temporaryBuffer);
                free(temporaryBuffer);
                break;
            case 2:
                scanf("%d",&deletedNode);
                deleteNode(head,deletedNode);
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
