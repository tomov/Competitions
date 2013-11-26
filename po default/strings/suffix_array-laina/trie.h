#include "definitions.h"
#define BUCKET_SIZE ('z' - 'a' + 1 + 'Z' - 'A' + 1)
#define CALC_BUCKET(c) (c <= 'Z' ? c -'A' + 'z' - 'a' + 1  : c - 'a')
#define IS_LETTER(c) (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) 

struct TrieNode
{
	int start, end;
	TrieNode* next[BUCKET_SIZE];
	TrieNode* second;
	__int64 positionsCount;
};

int currentBucket;
TrieNode* root;

TrieNode* createNode(int start, int end)
{
	TrieNode* node = new TrieNode;

	node->start = start;
	node->end = end;
	node->positionsCount = 0;
	node->second = NULL;
	for (int i=0; i<BUCKET_SIZE; i++)
	{
		(node->next)[i] = NULL;
	}

	return node;
}

void initializeTrie()
{
	root = createNode(0, 0);
}

void addWordToTrie(char* inputBuffer, int start, int end, int position)
{
//	for (int i=0; i<len; i++) printf("%c", word[i]); printf(" ");
	TrieNode *currentNode = root;
	char c;
	char* word = &inputBuffer[start];
	int bucket;

	for (int i=start; i<=end;)
	{
		c = *word; 
		
		bucket = CALC_BUCKET(c);

		if (currentNode->next[bucket] == NULL)
		{
			TrieNode* temp = createNode(start, end);
			temp->positionsCount = position;
			currentNode->next[bucket] = temp;
			return;//currentNode = currentNode->next[bucket];
		}
		else 
		{
			TrieNode* tempNode = currentNode->next[bucket];
			
			for (int j=tempNode->start; j<=tempNode->end; j++)
			{			
				if (i > end)
				{
					TrieNode* newNode = createNode(tempNode->start, j-1);
					tempNode->start = j;
					newNode->next[CALC_BUCKET(inputBuffer[j])] = tempNode;
					currentNode->next[bucket] = newNode;
					newNode->positionsCount = position;
					return;
				}

				if (inputBuffer[j] != c)
				{
					TrieNode* newNode2 = createNode(start, end);
					TrieNode* newNode = createNode(tempNode->start, j-1);
					tempNode->start = j;
					newNode->next[CALC_BUCKET(inputBuffer[j])] = tempNode;
					currentNode->next[bucket] = newNode;
					newNode2->positionsCount = position;
					newNode->next[CALC_BUCKET(c)] = newNode2;
					return;
				}
				word++;
				start++;
				i++;

				// new word is a part of other word
				c = *word;
			}
			currentNode = tempNode;
		}
	}

	currentNode->positionsCount += position;
}

__int64 searchForWordInTrie(char* inputBuffer, char *word, int len)
{
	TrieNode* currentNode = root;
	TrieNode* temp;
	char c;
	int bucket;

	for (int i=0; i<len;)
	{
		c = *word; 
		if (!IS_LETTER(c)) return 0;
		bucket = CALC_BUCKET(c);
		temp = currentNode->next[bucket];

		if (temp == NULL) return 0;

		for (int j=temp->start; j<=temp->end; j++)
		{
			if (inputBuffer[j] != c) return 0;
			word++;
			i++;
			c = *word; 
		}
		currentNode = temp;
	}

	return currentNode->positionsCount;
}