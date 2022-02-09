#include<iostream>
#include<chrono>
#include<thread>
#include<time.h>
int main()
{
    char ch[4] = {'|', '/', '\\'};
    int i = 0;
    while(true){
        std :: cout<<ch[i]<<"\n";
        if(i == 2)
            i=0;
        else 
            i++;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std :: cout << "\x1b[1A"<<"\x1b[2K";
        
        
    }
}