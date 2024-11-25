#include<iostream>
#include<string>
using namespace std;
int main(){
string inputString="aaabbbab";
cout << "The string to check whether it belongs to the given grammar or not is 'aaabbbab' "<<endl;

if(inputString[0]!='a'||inputString[inputString.size()-1]!='b'){
cout<<"The string does not belong to the grammar."<<endl;
return 0;
}
int i=0;
while(inputString[i]!='b'){
i++;
}
while(i<inputString.size()&&inputString[i]=='b'){
i++;
}
if(i<inputString.size()&&inputString[i]=='a')
cout<<"The string does not belong to the grammar."<<endl;
else
cout<<"The string belongs to the grammar."<<endl;
return 0;
}