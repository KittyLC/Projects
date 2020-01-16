#include <iostream>
#include <vector>
using namespace std;

class values {
public:
    int max, min;
};

class values findMinMax(vector<int> &a, int low, int high) {

    if(low < high) {

        int mid = (low + high) / 2;
        class values left = findMinMax(a, low, mid);
        class values right = findMinMax(a, mid+1, high);

        class values val;

        val.min = min(left.min, right.min);
        val.max = max(left.max, right.max);

        return val;

    } else {

        class values onlyVal;
        onlyVal.min = onlyVal.max = a[low];
        return onlyVal;
    }
}

int main() {

    int arr[] = {1, 2, 21, 19, 35};
    int size = sizeof(arr)/sizeof(arr[0]);

    vector<int> sample (arr, arr + size);
    class values res = findMinMax(sample, 0, size-1);
    cout<<"Min : " << res.min << "\nMax : " << res.max<<endl;

    return 0;

}

