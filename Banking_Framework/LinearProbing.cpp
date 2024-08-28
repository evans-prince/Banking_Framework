#include "LinearProbing.h"
using namespace std;
int LinearProbing::hash(string id){
    // cout<<"inhash:"<<id<<endl;
    unsigned long long int hash=4173;
    for (int j=0;j<id.size();j++){
        hash=hash<<(j%3+4)+hash+id[j];
    }
    return hash%100019;
}

void LinearProbing::Swapp(int& a,int& b )
{
    int temp = a;
    a = b;
    b = temp;
}

int LinearProbing::finalidx(string id){
    
    // cout<<"final:"<<id<<endl;
    
    int i=hash(id);
    resixe(i);
    while(bankStorage1d[i].balance!=-1){
        i++;
    }
    return i;
}

void LinearProbing::resixe(int idx){
        // cout<<"resize:"<<endl;

    int k=bankStorage1d.size();
    if(idx>0.7*k){
        bankStorage1d.resize(2*idx);
        for(k;k<2*idx;k++){
            bankStorage1d[k].id="0";
            bankStorage1d[k].balance=-1;
        }
    }
}

void LinearProbing::createAccount(std::string id, int count) {
        // cout<<"creatacc:"<<id<<endl;

    int idx=finalidx(id);
    resixe(idx);
    bankStorage1d[idx].id=id;
    bankStorage1d[idx].balance=count;
    balanceamount.push_back(count);
    size++;
}

std::vector<int> LinearProbing::getTopK(int k) {
    // cout<<"gettop:"<<endl;

    vector<int> mycopy;
    for (int i = 0; i < bankStorage1d.size(); i++)
    {
        if (bankStorage1d[i].balance != -1)
        {
            mycopy.push_back(bankStorage1d[i].balance);
        }
    }
    // for(int i=0;i<mycopy.size();i++){
    //     cout<<mycopy[i]<<" ";
    // }
    bool swap;
    int n = mycopy.size();
    for (int i = 0; i < n-1 && i<k ; i++)
    {
        swap = false;
        for (int j = 0; j < n-i - 1; j++){
            if (mycopy[j] > mycopy[j + 1])
            {
                Swapp(mycopy[j],mycopy[j+1]);
                swap = true;
            }
        }if(swap==false){
            break;
        }
    }
    vector<int> finalcopy;
    for (int i = 0; i <k && i<n; i++)
    {
        finalcopy.push_back(mycopy[n-1-i]);
    }
    return finalcopy;
    

}

int LinearProbing::getBalance(std::string id) {
        // cout<<"getblance:"<<id<<endl;

    int i = hash(id);
    for(i;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id==id || bankStorage1d[i].id=="0"){
            if(bankStorage1d[i].id==id){
                return bankStorage1d[i].balance;
            }else{
                return -1;
            }
        }
    }
    return -1;    
}

bool LinearProbing::doesExist(std::string id) {
        // cout<<"doesexits:"<<id<<endl;

    int i=hash(id);
    for(i;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id==id || bankStorage1d[i].id=="0"){
            if(bankStorage1d[i].id==id){
                return true;
            }else{
                return false;
            }
        }
    }
    return false;
}

void LinearProbing::addTransaction(std::string id, int count) {
    
        // cout<<"addtransaction:"<<id<<endl;
    int i = hash(id);
    bool done = false;
    for (i; i < bankStorage1d.size(); i++) {
        if (bankStorage1d[i].id == id || bankStorage1d[i].id=="0") {
            if(bankStorage1d[i].id==id){
                done = true;
                int originalBalance = bankStorage1d[i].balance;
                bankStorage1d[i].balance = originalBalance + count;
                for (int j = 0; j < balanceamount.size(); j++) {
                    if (balanceamount[j] == originalBalance) {
                        balanceamount[j] = bankStorage1d[i].balance;
                        break;
                    }
                }
            }
            break;            
        }
    }
    if (!done) {
        createAccount(id, count);
    }
}

bool LinearProbing::deleteAccount(std::string id) {
        // cout<<"deleteacc:"<<id<<endl;

    int i = hash(id);
    for (i; i < bankStorage1d.size(); i++) {
        if (bankStorage1d[i].id == id || bankStorage1d[i].id=="0") {
            if(bankStorage1d[i].id==id){
                int deletedBalance = bankStorage1d[i].balance;
                bankStorage1d[i].id="1";
                bankStorage1d[i].balance=-1;
                size--;
                // Update balanceamount vector by removing the deleted balance
                for (int j = 0; j < balanceamount.size(); j++) {
                    if (balanceamount[j] == deletedBalance) {
                        balanceamount.erase(balanceamount.begin() + j);
                        return true;
                        break;
                    }
                }
                return true;
            }else{
                return false;
            }
        }
    }
    return false;
}

int LinearProbing::databaseSize() {
    return size;
}
