/*
   CHARLIE NORGAARD
   12/5/22

   trie implements a trie, made of trieNodes. This includes
   code to build, search, and delete a trie
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

/* ----- HELPER FUNCTIONS ----- */

// Takes a character and returns the corresponding t9 number
int get_char_code(char c) {
    int charCodeTable[26] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3,
                            4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7};
    int charCodeIndex = c - 97;
    int charCode = charCodeTable[charCodeIndex];
    return charCode;
}

// Creates an empty trie node
trieNode* create_node() {
    trieNode* node = (trieNode*) malloc(sizeof(trieNode));
    for (int i = 0; i < BRANCHES; i++) {
        node -> branches[i] = NULL;
    }
    return node;
}

// Inserts a word into the trie
trieNode* insert_word(trieNode* root, char *word) {
    trieNode* temp = root;
    // creates a new node for the each letter in the word
    for (int i = 0; word[i] != '\0'; i++) {
        int branchNum = get_char_code(word[i]);
        if (temp -> branches[branchNum] == NULL) {
            temp -> branches[branchNum] = create_node();
        }
        temp = temp -> branches[branchNum];
    }
    // logic to add words that have the same T9 code
    while (temp -> word != NULL) {
        if (temp -> branches[8] == NULL) {
            temp -> branches[8] = create_node();
        }
        temp = temp -> branches[8];
    }
    temp -> word = malloc(strlen(word) + 1);
    strncpy(temp -> word, word, strlen(word)+1);
    return root;
}


/* ----- PRIMARY FUNCTIONS ----- */


// Given a word list (dictionary), builds a trie that holds
// each word.  Returns a pointer to the root node.
trieNode* build_tree(FILE *dict) {

    trieNode* root = create_node();

    char word[50];
    while (fgets(word, 50, dict)) {
        word[strcspn(word, "\n")] = 0;
        insert_word(root, word);
    }
    return root;
}

// Given a pattern, returns the word stored in the
// appropriate trieNode.
char* get_word(trieNode *root, char *pattern) {
    trieNode* temp = root;
    char* output = (char *) malloc(sizeof(char)*256);
    for (int i = 0; pattern[i] != '\0'; i++) {
        int branchNum;
        if (pattern[i] == '#') {
            branchNum = 8;
            if (temp -> branches[branchNum] == NULL) {
                output = "There are no more T9onyms.";
                return output;
            }
            temp = temp -> branches[branchNum];
        } else {
            branchNum = pattern[i] - 50;
            // if the trie path doesn't exist
            if (temp -> branches[branchNum] == NULL) {
                output = "Not found in current dictionary.";
                return output;
            }
            temp = temp -> branches[branchNum];
        }
    }
    // if the trie path exists, but no word is stored at the node
    if (temp -> word == NULL) {
        output = "Not found in current dictionary.";
        return output;
    }
    free(output);
    return temp -> word;
}

// Deletes the entire tree branching from root
void free_tree(trieNode* node) {
    for(int i=0; i<BRANCHES; i++) {
        if (node->branches[i] != NULL) {
            free_tree(node->branches[i]);
        }
        else {
            continue;
        }
    }
    free(node);
}
