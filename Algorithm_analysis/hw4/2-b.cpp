#include <bits/stdc++.h>

using namespace std;

#define endl "\n"

int main() {
    int count[128];
    priority_queue<int, vector<int>, greater<int>> pq;
    queue<int> q;

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
        if(count[i] > 0) {
            pq.push(count[i]);
        }
    }
    
    while(pq.size() > 1) {
        int first = pq.top();
        pq.pop();
        int second = pq.top();
        pq.pop();

        q.push(first + second);
        pq.push(first + second);
    }

    int result = 0;
    while(!q.empty()) {
        result += q.front();
        q.pop();
    }

    cout << "compressed bit : " << result << endl;

    return 0;
}