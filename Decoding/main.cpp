#include<bits/stdc++.h>
#include <string>
#include <bitset>

using namespace std;

int n = 0;  // No. of symbols
int num = 0;  // Length of sequence
char syms[10];  // array of symbols
float f[10];  // array of CDF

string y = "";
float tag = 0;
//float f[4]={0.0,0.8,0.82,1.0};
//char syms[3] = {'a','b','c'};

void rescale1 (float& l , float& u){
    l = 2*l;
    u = 2*u;
}

void rescale2 (float& l , float& u){
    l = 2*(l-0.5);
    u = 2*(u-0.5);
}

void shift_tag(string& s){
  s.push_back('0');
  s.erase(0, 1);
}

float calc_tag(string s){
    float tag = 0;
    for(int i=1; i<=s.length(); i++){
      char x = s[i-1];
      int y = x-'0';
      tag += (y*(pow(2,-i)));
    }
   return tag;
}
void decode(string s){
   queue <int> output;
    float L0 = 0;
    float U0 = 1;

    for(int i=0; i<num; i++){  // Given that the sequence is 4 digits
        float L = (U0-L0);

        for(int j=1; j<=n; j++){  // for 3 symbols A,B,C

            float LF = L*f[j-1] + L0;
            float UF = L*f[j] + L0;

            if(tag >= LF && tag <= UF){   // if this is true, so LF <= tag <= UF ( We found the right interval ! )
                output.push(j);
                bool v = false;
                while (v == false ){
                    if(LF > 0 && UF < 0.5){   //first range
                        shift_tag(y);
                        rescale1(LF,UF);
                    }
                    else if (LF > 0.5 && UF < 1.0){
                        shift_tag(y);
                        rescale2(LF,UF);
                    }
                    else{
                        v= true;
                        L0 = LF;
                        U0 = UF;
                        tag = calc_tag(y);
                    }
                } // End of while
            }
        } // End of inner for
    } // End of outer for

    while (!output.empty()){
      int z= output.front();
      switch(z){
            case 1:
                cout<<" 1"<<" >> "<<syms[0]<<endl;
                break;
            case 2:
                cout<<" 2"<<" >> "<<syms[1]<<endl;
                break;
            case 3:
                cout<<" 3"<<" >> "<<syms[2]<<endl;
                break;
        }

      output.pop();
    }

}
int main()
{
    cout<<"Enter the no. of symbols you want to use :"<<endl;
    cin>>n;
    cout<<"========================================"<<endl;
    for(int i=0 ; i<n ; i++){
        cout<<"Enter the "<< i+1 << " symbol :"<<endl;
        cin>> syms[i];
    }
    cout<<"========================================"<<endl;
    float p[n+1];   // array of probability for each symbol -- n + 1 to set p[0] = zero
    for(int i=1 ; i<n+1 ; i++){
        p[0] = 0.0;
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
    cout<<"Enter the number of digits in sequence :"<<endl;
    cin>>num;
    cout<<"========================================"<<endl;
    cout<<"Enter the binary tag :"<<endl;
    cin>>y;
    cout<<"========================================"<<endl;
    cout<<"The tag is : "<<calc_tag(y)<<endl;
    cout<<"\nThe sequence is :"<<endl;
    decode(y);
    return 0;
}
