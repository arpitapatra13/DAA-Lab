#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 200003 // Prime number > 2 * 10^5 for low collision rate

// Node structure for Hash Table with separate chaining
typedef struct Node {
    char word[12];
    int dist; // Distance from source word A (-1 if unvisited)
    struct Node* next;
} Node;

// Hash Table Structure
typedef struct {
    Node* buckets[TABLE_SIZE];
} HashTable;

// DJB2 String Hash Function
unsigned int hash_string(const char* str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % TABLE_SIZE;
}

HashTable* create_table() {
    return (HashTable*)calloc(1, sizeof(HashTable));
}

// Insert word into Hash Table if not present; return node pointer
Node* insert_or_find(HashTable* ht, const char* word) {
    unsigned int idx = hash_string(word);
    Node* cur = ht->buckets[idx];
    while (cur) {
        if (strcmp(cur->word, word) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->word, word);
    new_node->dist = -1;
    new_node->next = ht->buckets[idx];
    ht->buckets[idx] = new_node;
    return new_node;
}

// Search word in Hash Table
Node* find(HashTable* ht, const char* word) {
    unsigned int idx = hash_string(word);
    Node* cur = ht->buckets[idx];
    while (cur) {
        if (strcmp(cur->word, word) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// Free Hash Table memory
void free_table(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* cur = ht->buckets[i];
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(ht);
}

// Compute Minimum Word Mutations
int min_mutations(const char* start, const char* target, char** dict, int dict_size, int L) {
    HashTable* ht = create_table();

    // 1. Load dictionary words into Hash Set
    for (int i = 0; i < dict_size; i++) {
        insert_or_find(ht, dict[i]);
    }

    // 2. Rule Check: Target word B MUST exist in dictionary D
    Node* target_node = find(ht, target);
    if (!target_node) {
        free_table(ht);
        return -1; // Target B not reachable
    }

    // 3. Insert Start word A into lookup structure
    Node* start_node = insert_or_find(ht, start);

    // If start == target, 0 mutations needed
    if (strcmp(start, target) == 0) {
        free_table(ht);
        return 0;
    }

    // 4. Initialize BFS Queue
    Node** queue = (Node**)malloc((dict_size + 2) * sizeof(Node*));
    int front = 0, rear = 0;

    start_node->dist = 0;
    queue[rear++] = start_node;

    char temp_word[12];
    int result_mutations = -1;

    // 5. Run BFS Traversal
    while (front < rear) {
        Node* cur = queue[front++];
        
        if (strcmp(cur->word, target) == 0) {
            result_mutations = cur->dist;
            break;
        }

        strcpy(temp_word, cur->word);

        // Generate all valid 1-character mutations
        for (int i = 0; i < L; i++) {
            char orig_char = temp_word[i];
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == orig_char) continue;
                temp_word[i] = c;

                Node* neighbor = find(ht, temp_word);
                if (neighbor && neighbor->dist == -1) {
                    neighbor->dist = cur->dist + 1;
                    queue[rear++] = neighbor;
                }
            }
            temp_word[i] = orig_char; // Restore position
        }
    }

    free(queue);
    free_table(ht);
    return result_mutations;
}

int main() {
    char* dict[] = {"cat", "hat", "dot", "dog", "cog", "hot", "dat"};
    int dict_size = 7;
    int L = 3;
    const char* start = "cat";
    const char* target = "cog";

    int k = min_mutations(start, target, dict, dict_size, L);

    printf("Start Word : %s\n", start);
    printf("Target Word: %s\n", target);
    if (k != -1) {
        printf("Minimum Mutations (k): %d\n", k);
    } else {
        printf("No valid transformation sequence exists (-1).\n");
    }

    return 0;
}
