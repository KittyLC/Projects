#include<iostream>

using namespace std;

int *findMissing(int arr[], int n, int &resArrSize){

    int *p = new int[n];
    for (int i = 0; i<n; i++){
        p[i] = i;
    }

    int count = n;
    for (int i = 0; i<n; i++){
        if (arr[i] < n){
            if (p[arr[i]] != 'x'){
                p[arr[i]] = 'x';
                count--;
            }
        }
    }

    int *d = new int[count];
    int j = 0;
    for (int i = 0; i<n; i++){
        if (p[i] != 'x'){
            d[j] = p[i];
            j++;
        }
    }

    resArrSize = count;
    return d;
}

int main(){

    int arr[] = { 3,1,3,0,6,4};
    int *r;
    int c;

    r = findMissing(arr,6,c);

    for (int i=0; i<c; i++)
        cout << r[i] << " ";
    cout << endl;

    return 0;
}


