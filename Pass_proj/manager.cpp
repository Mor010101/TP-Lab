#include<string>
#include<iostream>
#include<fstream>
#include<list>

#include"hash.h"

struct user{
    std :: string name, salt;
    hash hex;
};

std :: string salty(){

}


class manager{
    std ::  list<user> stored_users;

    public:
        manager(){}


    

    friend void addUser(std :: string username, std :: string pass);

    bool tryUser(std :: string username, std :: string pass){

    }
    
};

void addUser(std :: string username, std :: string pass){
        struct user tmp;
        try{
        tmp.name = username;
        tmp.salt = salty();
        tmp.hex = hash(pass,tmp.salt); 
        
        stored_users.push_back(tmp);

        }catch(std :: exception& e){
            std :: cout<<e.what();
        }
    }