#include <stdio.h>
#include <memory.h>

int main() {
    int count[128];

    memset(count, 0, sizeof(count));

    // 파일 읽어오기
    int ch;
    FILE* f = fopen("anna-karerina.txt", "r");
    if(f != NULL) {
        while(EOF != (ch = fgetc(f))) {
            count[ch]++;
        }
    }

    fclose(f);

    // count 값 출력
    for(int i = 0; i < 128; i++) {
        printf("count[%d]=%d\n", i, count[i]);
    }

    return 0;
}