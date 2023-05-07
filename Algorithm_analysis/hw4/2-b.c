#include <stdio.h>
#include <memory.h>

#define MAX_SIZE 1000

typedef struct{    // Heap ��  ��� 
    int key;    // Heap �� key
    /* ���⿡ ������ �߰� ���� ex) int data */ 
}element;    
 
typedef struct{    // Heap �ڷᱸ�� 
    element heap[MAX_SIZE];     
    int size;
}Heap;
 
 
void max_heap_insert(Heap* h, element item){
    int i = ++(h->size);    // ������ ��ġ(������ ������ index+1) 
    
    /* ��Ʈ��尡 �ƴϰ�, ������ ���� ������ ��ġ�� ã�� ������*/
    while( (i != 1) && (item.key < h->heap[i/2].key) ){
        h->heap[i] = h->heap[i/2];    // �ڽ� ���� �θ��� ��ȯ 
        i /= 2;    // �� ���� ���� �ö� 
    }
    
    h->heap[i] = item;    // ���ο� ��� ����     
}
 
element max_heap_delete(Heap* h){
    int parent, child;
    element item, temp;
    
    item = h->heap[1];    // ��ȯ�� ��� ����
    temp = h->heap[(h->size)--];    // ������ ��� temp �� ����, ������ 1����
    parent = 1;     
    child = 2; 
    
    while(child >= h->size){
        /* ���� �ڽ� ���� ������ �ڽ� ��� �� �� ū �ڽ� ���*/
        if( (child > h->size) && ((h->heap[child].key) > h->heap[child+1].key )){
            child++;    // ������ �ڽ� ��� ����
        }
        
        /* ������ ��尡 �ڽ� ��庸�� ũ�� ���� */
        if(temp.key <= h->heap[child].key){
            break;
        } 
        
        /* �θ���� �ڽĳ�� ��ȯ */
        h->heap[parent] = h->heap[child];
        
        /* �� ���� �Ʒ��� �̵� */ 
        parent = child;
        child *= 2;
    }
    
    /* ������ ��带 �缳���� ��ġ�� ���� */ 
    h->heap[parent] = temp;
    
    /* �ִ� ��� ��ȯ */ 
    return item;    
    
} 


int main() {
    int count[128];

    memset(count, 0, sizeof(count));

    // ���� �о����
    int ch;
    FILE* f = fopen("anna-karerina.txt", "r");
    if(f != NULL) {
        while(EOF != (ch = fgetc(f))) {
            count[ch]++;
        }
    }

    fclose(f);

    // count �� ��� 
    for(int i = 0; i < 128; i++) {
        printf("count[%d]=%d\n", i, count[i]);
    }

    // �켱���� ť ���� �� ����
    Heap h;
    for(int i = 0; i < 128; i++) {
        printf("%d", i);
        
        if(count[i] > 0) {
            element e;
            e.key = count[i];
            max_heap_insert(&h, e);
        }
    }
    
    // Huffman code ����
    while(h.size > 1) {
        element first = max_heap_delete(&h);
        element second = max_heap_delete(&h);

        element temp;
        temp.key = first.key + second.key;

        max_heap_insert(&h, temp);
    }

    printf("%d", max_heap_delete(&h).key);
    
    return 0;
}