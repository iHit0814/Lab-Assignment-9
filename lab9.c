#include <stdio.h>

#define HASH_SIZE 100
// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order;
};

struct HashType
{
	struct RecordType *record;
	int count;
};

int hash(int x)
{
	return x % HASH_SIZE;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i, j;
    for (i = 0; i < hashSz; i++) {
        if (pHashArray[i].count > 0) {
            printf("Index %d -> ", i);
            for (j = 0; j < pHashArray[i].count; j++) {
                printf("%d, %c, %d -> ", pHashArray[i].record[j].id, pHashArray[i].record[j].name, pHashArray[i].record[j].order);
            }
            printf("\n");
        }
    }
}


int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;
	int i, index;
    struct HashType hashArray[HASH_SIZE];

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);

	// Initialize the array.
	for (i = 0; i < HASH_SIZE; i++) {
        hashArray[i].record = NULL;
        hashArray[i].count = 0;
    }

	// Add each record to the array.
    for (i = 0; i < recordSz; i++) {
        index = hash(pRecords[i].id);
        hashArray[index].count++;
        hashArray[index].record = (struct RecordType*)realloc(hashArray[index].record, sizeof(struct RecordType)*hashArray[index].count);
        hashArray[index].record[hashArray[index].count-1] = pRecords[i];
    }

	displayRecordsInHash(hashArray, HASH_SIZE);

	// Free all dynamically allocated memory.
	for (i = 0; i < HASH_SIZE; i++) {
        free(hashArray[i].record);
    }
    free(pRecords);

	return 0;
}
