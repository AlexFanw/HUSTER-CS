#include <iostream>
#include <string>
using namespace std;
string wwf;  
int current;
int flag;
int taut(int i) {  
    char ch = wwf[current++];  
    if(ch=='p' || ch=='q'|| ch=='r' || ch=='s' || ch=='t'){
        return (i>>int (ch-'p'))&1;
    }  
    else if(ch=='K') return taut(i) & taut(i);  
    else if(ch=='A') return taut(i) | taut(i);  
    else if(ch=='N') return !taut(i);  
    else if(ch=='C') return (!taut(i)) | taut(i);  
    else if(ch=='E') return taut(i) == taut(i);  
    else return 0;  
}  
  
int main() {
    while(cin >> wwf && wwf[0]!='0') {  
        flag = 1;
        for(int i=0; i<32; i++) {  
            current = 0;  
            if(!taut(i)) {  
                flag = 0;  
                break; 
            } 
        }
        if(flag) cout << "tautology" << endl;  
        else cout << "not" << endl; 
    }

    return 0;  
}  