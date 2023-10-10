#include <iostream>
using namespace std;

bool samecolor();
void flip(int i);
bool b_tree(int i);
int getTimes();
void search();

int tf[16] ;
int sq[4][4];
int times = -1;

int main(){
    char temp;
    for (int i = 0;i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cin >> temp;
			if (temp == 'b')
				sq[i][j] = 1;
			else
				sq[i][j] = 0;
		}
	}
    
    search();
    if (times == -1)
	{
		cout << "Impossible" << endl;
	}
    else
	{
		cout << times << endl;
	}

}

void search()
{
	tf[0] = 0;
	flip(0);
	b_tree(1);

	tf[0] = 1;
	flip(0);
	b_tree(1);
}

int getTimes(){
    int curtime = 0;
    for(int i=0;i<16;i++){
        if(tf[i] == 0){
            curtime +=1;
        }
    }
    return curtime;
}

bool b_tree(int i){//i为搜索层数
    if (i == 16)
	{
		if (samecolor())
		{
			if (times == -1)
				times = getTimes();
			else
			{
				int tempTime = getTimes();
				times = tempTime < times ? tempTime:times;
			}
			return true;
		}
        else
			return true;
	}

	tf[i] = 0;
	flip(i);
	b_tree(i+1);
	tf[i] = 1;
	flip(i);
	b_tree(i+1);
    return 1;
}

void flip(int i){
    int n = i/4;
    int m = i%4;
    sq[n][m] = (sq[n][m] ==1)? 0:1;
    if (m != 0){
        sq[n][m-1] = (sq[n][m-1] ==1)? 0:1;
    }
    if (n != 0){
        sq[n-1][m] = (sq[n-1][m] == 1)? 0:1;
    }
    if (m != 3){
        sq[n][m+1] = (sq[n][m+1] ==1)? 0:1;
    }
    if (n != 3){
        sq[n+1][m] = (sq[n+1][m] == 1)? 0:1;
    }
}

bool samecolor(){
    for(int i = 0;i <= 3;i++){
        for(int j = 0;j <= 3;j++){
            if(sq[i][j] != sq[0][0]) return false;
        }
    }
    return true;
}