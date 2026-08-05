#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Returns the kth word in the mth sentence of the nth paragraph
char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    Reset

// Returns the kth paragraph
char*** kth_paragraph(char**** document, int k) {
    return document[k - 1];
}

// Parses the text document and creates the 4D pointer representation (char****)
char**** get_document(char* text) {
    char**** doc = NULL;
    int p_count = 0, s_count = 0, w_count = 0;
    
    // Allocate space for the first paragraph, first sentence, and first word
    doc = (char****)malloc(sizeof(char***));
    doc[0] = (char***)malloc(sizeof(char**));
    doc[0][0] = (char**)malloc(sizeof(char*));
    
    char* start_of_word = text;
    
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == ' ') {
         
            start_of_word = &text[i + 1];
        }
    }            // End of word found: terminate the string and save its pointer
            text[i] = '\0';
            doc[p_count][s_count][w_count++] = start_of_word;
            
            // Reallocate to add space for the next word pointer
            doc[p_count][s_count] = (char**)realloc(doc[p_count][s_count], (w_count + 1) * sizeof(char*));
            start_of_word = &text[i + 1];
        } 
        else if (text[i] == '.') {
            // End of sentence found: terminate the final word of the sentence
            text[i] = '\0';
            doc[p_count][s_count][w_count++] = start_of_word;
            
            s_count++;
            w_count = 0; // Reset word count for the next sentence
            
            // Reallocate to add space for the next sentence pointer
            doc[p_count] = (char***)realloc(doc[p_count], (s_count + 1) * sizeof(char**));
            doc[p_count][s_count] = (char**)malloc(sizeof(char*));
            
            start_of_word = &text[i + 1];
        } 
        else if (text[i] == '\n') {
            // End of paragraph found: reset sentence count
            s_count = 0;
            p_count++;
            
            // Reallocate to add space for the next paragraph pointer
            doc = (char****)realloc(doc, (p_count + 1) * sizeof(char***));
            doc[p_count] = (char***)malloc(sizeof(char**));
            doc[p_count][0] = (char**)malloc(sizeof(char*));
   
    return doc;
}


char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}
