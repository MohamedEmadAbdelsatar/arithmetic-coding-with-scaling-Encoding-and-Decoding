#include<bits/stdc++.h>

using namespace std;

int n;  // No. of
int seq; // input sequence
int Set = 0;    // x of CDF
char s[10];  // array of symbols
float f[10];  // array of CDF

void rescale1 (float& l , float& u){
    l = 2*l;
    u = 2*u;
}

void rescale2 (float& l , float& u){
    l = 2*(l-0.5);
    u = 2*(u-0.5);
}

void calc(int seq){
    stack <int> q;
    while(seq >10){
        int c = seq %10;
        q.push(c);
        seq=seq/10;
    }
    q.push(seq);

    queue <int> output;
    float L0 = 0;
    float U0 = 1;
    while(!q.empty()){
        Set = q.top();
        float L = L0 +(U0-L0)*f[Set - 1];
        float U = L0 +(U0-L0)*f[Set];

        bool flag = true;
        while(flag){
          if(L >= 0 && U <= 0.5){
            output.push(0);
            rescale1(L , U);
          }
          else if(L >= 0.5 && U<= 1.0){
            output.push(1);
            rescale2(L , U);
          }
          else
            flag = false;
            cout<<"L : "<<L<<endl;
            cout<<"U : "<<U<<endl;
        }
        L0 = L;
        U0 = U;
        q.pop();
    }
    while(!output.empty()){
        int z = output.front();
        cout<<z;
        output.pop();
    }
}

void seqInLetters(int seq){
    stack <int> q;
    while(seq >10){
        int c = seq %10;
        q.push(c);
        seq=seq/10;
    }
    q.push(seq);
    while(!q.empty()){
        int val = q.top();
        switch(val){
            case 1:
                cout<<s[0];
                break;
            case 2:
                cout<<s[1];
                break;
            case 3:
                cout<<s[2];
                break;
        }
        q.pop();
    }
}

int main()
{
    // Encoding for 4 digits sequence
    cout<<"Enter the no. of symbols you want to use :"<<endl;
    cin>>n;
    cout<<"========================================"<<endl;

    for(int i=0 ; i<n ; i++){
        cout<<"Enter the "<< i+1 << " symbol :"<<endl;
        cin>> s[i];
    }
    cout<<"========================================"<<endl;
    float p[n+1];   // array of probability for each symbol -- n + 1 to set p[0] = zero
    p[0] = 0.0;
    for(int i=1 ; i<n+1 ; i++){
        cout<<"Enter the Probability of each symbol :"<<endl;
        cin>>p[i];
    }
    cout<<"========================================"<<endl;
    cout<<"The C.D.F. for each symbol f(x):"<<endl;

    for(int i=0; i<n+1; i++){
        if(i == 0){
            f[0]=p[0];
        }
        else{
            f[i]=p[i]+f[i-1];
            cout<<f[i]<<endl;
        }
    }
    cout<<"========================================"<<endl;
    cout<<"Enter the sequence you want in numbers :"<<endl;
    cin>>seq;
    cout<<"========================================"<<endl;

    cout<<"The final tag of the sequence ";
    seqInLetters(seq);
    cout<<" is ";
    calc(seq);
    cout<<"\n========================================"<<endl;
    return 0;
}
