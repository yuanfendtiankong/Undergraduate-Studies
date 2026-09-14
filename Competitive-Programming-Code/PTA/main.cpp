
#include <bits/stdc++.h>

using namespace std;
const int N= 1e5+10;
typedef long long ll;
#define endl '\n'
int n;

int main()
{
    /*ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    */

    cin>>n;
    vector< pair<string,string>> arr;
    for(int i=0; i<n; i++)
    {
        string a,b;
        cin>>a>>b;
        arr.push_back({a,b});
    }
    int m;
    cin>>m;
    for(int i=0;i<m;i++)
    {
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        int x = rand()%3+1;
        if(x==1)
        {
            cout<<"Yes"<<endl;
        }
        else if(x==2)
        {
            cout<<"No"<<endl;
        }
        else
        {
            cout<<"Whatever"<<endl;
        }
    }






    return 0;
}

/*
7 5 3
7 6 1 3 2 5 4
3 1 5 4 2 6 7
7 6 5 4 3 2 1

YES
NO
NO
*/









