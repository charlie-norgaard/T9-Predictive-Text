/*
   CHARLIE NORGAARD
   12/5/22

   tnine is a program that drives a trie / t9 program.  This code
   will build a trie, according to trienode.  It will also run
   an interactive session where the user can retrieve words using
   t9 sequences.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

// run_session runs the on-going decoding interaction with the
// user.  It requires a previously build wordTrie to work.
void run_session(trieNode *wordTrie) {
    printf("Enter \"exit\" to quit.\n");
    while (1) {
        char* input = (char *) malloc(sizeof(char)*256);
        if (input == NULL) {
            fprintf(stderr, "Error: memory not allocated for input.\n");
            return;
        }
        printf("Enter Key Sequence (or \"#\" for next word):\n");
        printf("> ");
        scanf("%s", input);
        if (strcmp(input, "exit") == 0) {
            break;
        } else {
            input[strcspn(input, "\n")] = 0;
            printf("%s\n", get_word(wordTrie, input));
        }
        free(input);
    }
}

int main(int argc, char **argv) {
    FILE *dictionary = NULL;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [DICTIONARY]\n", argv[0]);
        return EXIT_FAILURE;
    } else {
        dictionary = fopen(argv[1], "r");
        if (!dictionary) {
            fprintf(stderr, "Error: Cannot open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    // build the trie
    trieNode* wordTrie = build_tree(dictionary);
    fclose(dictionary);

    // run interactive session
    run_session(wordTrie);

    // free the trie
    free_tree(wordTrie);

    return(EXIT_SUCCESS);
}
