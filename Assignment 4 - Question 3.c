#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);


int hash1(int key);
int hash2(int key);

int main()
{
    int opt;
    int i;
    int key;
    int comparison;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].indicator = EMPTY;
        hashTable[i].key = 0;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Delete a key from the hash table|\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");
    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            comparison = HashInsert(key,hashTable);
            if(comparison <0)
                printf("Duplicate key\n");
            else if(comparison < TABLESIZE)
                printf("Insert: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Key Comparisons: %d. Table is full.\n",comparison);
            break;
        case 2:
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            comparison = HashDelete(key,hashTable);
            if(comparison <0)
                printf("%d does not exist.\n", key);
            else if(comparison <= TABLESIZE)
                printf("Delete: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Error\n");
            break;
        case 3:
            for(i=0;i<TABLESIZE;i++) printf("%d: %d %c\n",i, hashTable[i].key,hashTable[i].indicator==DELETED?'*':' ');
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int hash1(int key)
{
    return (key % TABLESIZE);
}

int hash2(int key)
{
    return (key % PRIME) + 1;
}

int HashInsert(int key, HashSlot hashTable[])
{
int index = 0, comparison = 0, i = 0;
int hash = hash1(key);
int insert_index = 0;

while (hashTable[hash].indicator == USED && hashTable[hash].key != key && i<TABLESIZE){
        hash = (hash + hash2(key))%TABLESIZE;
        i++;
        comparison++;
}

if (i>=TABLESIZE)return comparison;

insert_index = hash;

while (hashTable[hash].indicator != EMPTY && i<TABLESIZE){
    if (hashTable[hash].indicator == USED ){
        comparison++;
        if (hashTable[hash].key == key)return -1;
    }
    hash = (hash + hash2(key))%TABLESIZE;
    i++;
}

hashTable[insert_index].key = key;
hashTable[insert_index].indicator = USED;
return comparison;
}

int HashDelete(int key, HashSlot hashTable[])
{
   int Hashvalue = hash1(key);
   int comparisions = 0;

   int count = 0;
   while(count < TABLESIZE){
    int index = (Hashvalue + count*hash2(key))%TABLESIZE;
    comparisions++;

    if (hashTable[index].indicator == USED && hashTable[index].key == key){
        hashTable[index].indicator = DELETED;
        return comparisions;
    }else if (hashTable[index].indicator == EMPTY || hashTable[index].indicator == DELETED)return -1;
    count++;
   }
   return -1;
}
