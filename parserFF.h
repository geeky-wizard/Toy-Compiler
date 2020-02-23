#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NTSIZE 	35
#define TSIZE	20
#define BUFF_SIZE 150
#define MAX_NON_TERMINALS 100
#define MAX_TERMINALS 100
#define MAX_FIRST 15
#define MAX_FOLLOW 15


char buffer[BUFF_SIZE];

char tempFirsts[MAX_FIRST][TSIZE]; // Contains Firsts
int tempFirstsSize = 0;

char tempFollows[MAX_FOLLOW][TSIZE];  // Contains Follows
int tempFollowsSize = 0;


char nonterminals[MAX_NON_TERMINALS][NTSIZE];
char terminals[MAX_TERMINALS][TSIZE];

int numNT = 0;
int numT = 0;

int currentFirstFollowCompute = 0;

struct ruleToken* CurrentRuleTokenGlobal;

struct ruleToken{
    int tag; // Non-terminal(0) or terminal(1)
    char tnt[NTSIZE];
    struct ruleToken* next;
};

struct ntRules{
    char nt[NTSIZE];
    int numRules;
    struct ruleToken heads[10];
};

struct ntfirstFollow{
    char nt[NTSIZE];

    char firsts[MAX_FIRST][TSIZE]; // firsts consists only of terminals
    int numFirsts;

    char follows[MAX_FOLLOW][TSIZE]; // follows consists only of terminals
    int numFollows;

    int status;
    /*  
        0 - No firsts or follows computed
        1 - Only Firsts Computed
        2 - Both Firsts and Follows computed
    */
};

struct ntRules grammar[MAX_NON_TERMINALS];
int grammarLength = 0;

struct ntfirstFollow FirstFollowSets[MAX_NON_TERMINALS];


// Functionns

void addRuleToGrammer(char* rule);

// First And Follow Functions

void computeFirstAndFollow();

void computeFirstAllSets();

void computeFirstForSingleNT(int indexNT);

void computeFirstRecursive(int indexNT,int ruleNum);

void addFirsts(int i);

void computeFollowAllSets();

void computeFollowForSingleNT(int indexNT);

void computeFollowRecursive(char* strNT,int lineNo,int ruleNo);

void computeFollowRecursive2(struct ruleToken* rulePointer,struct ntRules* startToken);

void getFirstsForFollows(int indexNT,struct ruleToken* rulePointer,struct ntRules* startToken);

void addFollows(int i);


// miscellaneous

bool isEpsilon(char* str);

int getIndexOfTerminal(char *bufferToken);

int getIndexOfNonTerminal(char *bufferToken);

int findRHSPositions(char* str,int* rhsNT,int* rhsNTRulePos);

bool checkIfFollowAlreadyPresent(char* str);

bool checkIfFirstAlreadyPresent(char* str);

// Print Functions
void printAllGrammar();

void printRuleGrammarStruct(int i);

void printAllTerminals();

void printAllNonTerminals();

void printAllFirstSets();

void printAllFollowSets();