#include <stdio.h>
#include <string.h>

#define N 209 //The 1000th Fibonacci number has 209 decimal digits.

// 전역변수 선언
int check = 0;
char aa[N], bb[N];

void print_digits(char d[N])
{
    int i = 0;
    
    // after loop, i is the first "non-zero" place
    while(d[i] == 0) {
        i++;
    }

    while(i < N) {
        printf("%d", d[i++]); // "%d" instead of "%c"
    }   
}

// Add aa and bb and store the result in bb.
// aa is assumed to be always larger.
void add_digits(char aa[N], char bb[N])
{
    int i = 0;
    int carry = 0;
    int j, s;

    while(aa[i] == 0) {
        i++;
    } // after loop, i is the first "non-zero" place

    for(j = N - 1; j >= i - 1; j--) { // the sum can have non-zero at (i-1)th place
        if((s = carry + aa[j] + bb[j]) > 9) {
            bb[j] = s - 10;
            carry = 1;
        }
        else {
            bb[j] = s;
            carry = 0;
        }
    }
}

int main()
{
    // Write Your Program Here!

    // memoization 적용
    memset(aa, 0, sizeof(aa));
    memset(bb, 0, sizeof(bb));

    aa[N - 1] = 1;
    bb[N - 1] = 1;
    for(int i = 2; i < 1001; i++) {
        if(check == 0) {
            add_digits(aa, bb);
            check = 1;
        }
        else {
            add_digits(bb, aa);
            check = 0;
        }
    }

    // Output
    if(check == 0) {
        print_digits(aa);
    }
    else {
        print_digits(bb);
    }
    
}