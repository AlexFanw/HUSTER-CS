#include <iostream>
using namespace std;
const int N=5e4+10;
int fir[N];
int sec[N];
int main(){
    int first,second;
    cin >> first;
    for(int i = 0;i< first ;i++){
        scanf("%d",fir+i);
    }
    cin >> second;
    for(int i = 0;i< second ;i++){
        scanf("%d",sec+i);
        sec[i] = 10000 - sec[i];
    }
    for(int i = 0;i< first;i++){
        int flag = 0;
        for(int j = flag;j< second;j++){
            if (fir[i] == sec[j]){
                cout << "YES" << endl;
                return 1;
            }
            if (sec[j] > fir[i]) {
                flag = j-1;
                break;
                }
    }
    }
    cout << "NO" << endl;
    return 1;
}