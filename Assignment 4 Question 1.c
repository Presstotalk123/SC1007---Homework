#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED};

typedef struct _slot{
    int key;
    enum Marker indicator;
    int next;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashFind(int key, HashSlot hashTable[]);

int hash(int key)
{
    return (key % TABLESIZE);
}

int main()
{
    int opt;
    int i;
    int key;
    int index;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].next = -1;
        hashTable[i].key = 0;
        hashTable[i].indicator = EMPTY;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Search a key in the hash table  |\n");
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
            index = HashInsert(key,hashTable);
            if(index <0)
                printf("Duplicate key\n");
            else if(index < TABLESIZE)
                printf("Insert %d at index %d\n",key, index);
            else
                printf("Table is full.\n");
            break;
        case 2:
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            index = HashFind(key, hashTable);

            if(index!=-1)
                printf("%d is found at index %d.\n",key,index);
            else
                printf("%d is not found.\n",key);
            break;

        case 3:
            printf("index:\t key \t next\n");
            for(i=0;i<TABLESIZE;i++) printf("%d\t%d\t%d\n",i, hashTable[i].key,hashTable[i].next);
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int HashInsert(int key, HashSlot hashTable[])
{

if (HashFind(key,hashTable) != -1) return -1;

int i=0;
int insert_index = 0;

while (i<TABLESIZE){
    insert_index = hash(key+i);
    if (hashTable[insert_index].indicator == EMPTY){
        //insertion of key
        hashTable[insert_index].key = key;
        hashTable[insert_index].next = -1;
        hashTable[insert_index].indicator = USED;

        //reassigning hash values like a linked list if they are not the first hash
        if (insert_index != hash(key)){
            int cur = hash(key);
            while (hashTable[cur].next != -1) {
                cur = hashTable[cur].next;
            }
            hashTable[cur].next = insert_index;
        }

        //return and end insertion function if succesful
        return insert_index;
    }

    i++;
}
return i;
}

int HashFind(int key, HashSlot hashTable[])
{
 int cur = hash(key);
    while (cur != -1){
        if (hashTable[cur].key == key)return cur;
    cur = hashTable[cur].next;
    }
     return -1;

}
