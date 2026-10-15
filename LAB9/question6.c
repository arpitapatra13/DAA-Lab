#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char ch;
    int freq;
} CharFreq;

int main() {
    char S[1000];
    int K;
    if (scanf("%s %d", S, &K) != 2) return 0;

    int n = strlen(S);
    int count[256] = {0};

    for (int i = 0; i < n; i++) {
        count[(unsigned char)S[i]]++;
    }

    CharFreq heap[256];
    int heap_size = 0;

    for (int i = 0; i < 256; i++) {
        if (count[i] > 0) {
            heap[heap_size].ch = (char)i;
            heap[heap_size].freq = count[i];
            heap_size++;
        }
    }

    char result[1000];
    int res_len = 0;

    CharFreq queue[1000];
    int q_head = 0, q_tail = 0;

    while (heap_size > 0) {
        int max_idx = 0;
        for (int i = 1; i < heap_size; i++) {
            if (heap[i].freq > heap[max_idx].freq) {
                max_idx = i;
            }
        }

        CharFreq top = heap[max_idx];
        heap[max_idx] = heap[heap_size - 1];
        heap_size--;

        result[res_len++] = top.ch;
        top.freq--;

        queue[q_tail++] = top;

        if (q_tail - q_head >= K) {
            CharFreq front = queue[q_head++];
            if (front.freq > 0) {
                heap[heap_size++] = front;
            }
        }
    }

    result[res_len] = '\0';

    if (res_len == n) {
        printf("Reorganized String = %s\n", result);
    } else {
        printf("Reorganized String = \"\" (Impossible)\n");
    }

    return 0;
}
