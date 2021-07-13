#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;

vector<int> ans;
int fail[1000020];
void calculate_fail(char* arr) {
    int length = strlen(arr);
    fail[0] = 0;
    for(int i=1, j=0; i<length; i++) {
        while(j>0 && arr[i]!=arr[j])
            j = fail[j-1];
        if(arr[i] == arr[j])
            fail[i] = ++j;
    }
}
void KMP(char *A, char *B) {
    // find B from A
    int pt1 = 0, pt2 = 0, lenA = strlen(A), lenB = strlen(B);
    for(pt1 = 0; pt1 < lenA; pt1++) {
        while(pt2 > 0 && A[pt1]!=B[pt2])
            pt2 = fail[pt2-1];
        if(A[pt1]==B[pt2]) {
            if(pt2 == lenB-1) {
                ans.push_back(pt1-lenB+2);
                pt2 = fail[pt2];
            }
            else {
                pt2++;
            }
        }
    }
}