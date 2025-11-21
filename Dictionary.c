#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORD_SIZE 50
#define MEANING_SIZE 200

struct Dictionary {
    char word[WORD_SIZE];
    char meaning[MEANING_SIZE];
};

void addWord();
void searchWord();
void viewAll();

int main() {
    int choice;

    while(1) {
        printf("\n===== DICTIONARY / WORD LOOKUP =====\n");
        printf("1. Add New Word\n");
        printf("2. Search Word\n");
        printf("3. View All Words\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();
        switch(choice) {
            case 1: addWord(); break;
            case 2: searchWord(); break;
            case 3: viewAll(); break;
            case 4: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}

void addWord() {
    FILE *fp = fopen("dictionary.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Dictionary d;

    printf("Enter Word: ");
    fgets(d.word, WORD_SIZE, stdin);
    d.word[strcspn(d.word, "\n")] = '\0';

    printf("Enter Meaning: ");
    fgets(d.meaning, MEANING_SIZE, stdin);
    d.meaning[strcspn(d.meaning, "\n")] = '\0';

    fprintf(fp, "%s|%s\n", d.word, d.meaning);

    fclose(fp);
    printf("Word added successfully!\n");
}

void searchWord() {
    FILE *fp = fopen("dictionary.txt", "r");
    if (fp == NULL) {
        printf("No words found! Add some first.\n");
        return;
    }

    char searchWord[WORD_SIZE];
    char line[300];
    int found = 0;

    printf("Enter word to search: ");
    fgets(searchWord, WORD_SIZE, stdin);
    searchWord[strcspn(searchWord, "\n")] = '\0';

    struct Dictionary d;

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^|]|%[^\n]", d.word, d.meaning);

        if (strcmp(d.word, searchWord) == 0) {
            printf("\nMeaning of '%s': %s\n", d.word, d.meaning);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Word not found!\n");

    fclose(fp);
}

void viewAll() {
    FILE *fp = fopen("dictionary.txt", "r");
    if (fp == NULL) {
        printf("No words found!\n");
        return;
    }

    char line[300];
    struct Dictionary d;

    printf("\n===== ALL WORDS =====\n");

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^|]|%[^\n]", d.word, d.meaning);
        printf("%s → %s\n", d.word, d.meaning);
    }

    fclose(fp);
}
