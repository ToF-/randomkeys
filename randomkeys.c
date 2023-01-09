#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>


const int MAX_LENGTH = 50;
const int MAX_WORD = 60000;
char *Words[MAX_WORD];

int main(int argc, char *argv[]) {
    const char *ukwords_path = getenv("UKWORDS");
    if(!ukwords_path) {
        fprintf(stderr, "UKWORDS var undefined. (export UKWORDS=path/to/ukwords.txt)\n");
        return -1;
    }
    FILE *file = fopen(ukwords_path, "r");

    char word[MAX_LENGTH];
    int max_word = 0;
    while(fgets(word, 50, file) && max_word < MAX_WORD) {
        int l = strcspn(word, "\n");
        word[l] = '\0';
        Words[max_word++] = strdup(word);
    }
    srand(time(NULL));
    bool upper = false;
    int letters = 2;
    int size = 10;
    int c;
    while((c = getopt(argc, argv, "ul:hs:")) != -1) {
        switch(c) {
            case 'u': upper = true; break;
            case 'l': letters = atoi(optarg); break;
            case 'h': printf("randomkeys -u : upper\n\t   -l <#letters>\n\t   -s <size>");
                      exit(0);
            case 's': size = atoi(optarg); break;
        }
    }
    if(argc > 1 && !strcmp(argv[1],"-u"))
        upper = true;
    while(true) {
        int j = rand() % max_word;
        memset(word, 0, MAX_LENGTH);
        strcpy(word, Words[j]);
        if(strlen(word) > size || strlen(word) > letters) {
            continue;
        }
        if(upper)
            for(int c=0; c<strlen(word); c++) {
                word[c] = toupper(word[c]);
            }
        for(int c=strlen(word); c<size; c++) {
            word[c] = (rand() % 10) + '0';
        }
        printf("%s\n", word);
    }
    for(int i=0; i < max_word; i++) {
        free(Words[i]);
    }
}

