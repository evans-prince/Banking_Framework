#include "CubicProbing.h"
using namespace std;
int CubicProbing::hash(string id){
    // cout<<"inhash:"<<id<<endl;
    int i=0;
    for(int j=0;j<id.size();j++){
        i=i+id[j];
    }
    return i;
}

void CubicProbing::Swapp(int& a,int& b )
{
    int temp = a;
    a = b;
    b = temp;
}

int CubicProbing::finalidx(string id){
    
    // cout<<"final:"<<id<<endl;
    
    int i=hash(id);
    int k=1;
    resixe(i);
    while(bankStorage1d[i].balance!=-1){
        i=i+1+k*k;
        k++;
        if(i>=bankStorage1d.size()){
            resixe(i);
        }
    }
    return i;
}

void CubicProbing::resixe(int idx){
        // cout<<"resize:"<<endl;

    int k=bankStorage1d.size();
    if(idx>0.7*k){
        bankStorage1d.resize(2*idx);
        for(k;k<2*idx;k++){
            bankStorage1d[k].balance=-1;
        }
    }
}

void CubicProbing::createAccount(std::string id, int count) {
        // cout<<"creatacc:"<<id<<endl;

    int idx=finalidx(id);
    resixe(idx);
    bankStorage1d[idx].id=id;
    bankStorage1d[idx].balance=count;
    balanceamount.push_back(count);
}

std::vector<int> CubicProbing::getTopK(int k) {
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

int CubicProbing::getBalance(std::string id) {
        // cout<<"getblance:"<<id<<endl;

    int i = hash(id);
    for(i;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id==id){
            return bankStorage1d[i].balance;
        }
    }
    return -1;
}

bool CubicProbing::doesExist(std::string id) {
        // cout<<"doesexits:"<<id<<endl;

    int i=hash(id);
    for(i;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id==id){
            return true;
        }
    }
    return false;
}

void CubicProbing::addTransaction(std::string id, int count) {
    
        // cout<<"addtransaction:"<<id<<endl;
int i = hash(id);
    bool done = false;
    for (i; i < bankStorage1d.size(); i++) {
        if (bankStorage1d[i].id == id) {
            done = true;
            int originalBalance = bankStorage1d[i].balance;
            bankStorage1d[i].balance = originalBalance + count;

            // Update balanceamount vector
            for (int j = 0; j < balanceamount.size(); j++) {
                if (balanceamount[j] == originalBalance) {
                    balanceamount[j] = bankStorage1d[i].balance;
                    break;
                }
            }
            break;
        }
    }
    if (!done) {
        createAccount(id, count);
    }
}

bool CubicProbing::deleteAccount(std::string id) {
        // cout<<"deleteacc:"<<id<<endl;

    int i = hash(id);
    for (i; i < bankStorage1d.size(); i++) {
        if (bankStorage1d[i].id == id) {
            int deletedBalance = bankStorage1d[i].balance;
                // bankStorage1d.erase(bankStorage1d.begin() + i);
            bankStorage1d[i].id="0";
            bankStorage1d[i].balance=-1;
            // Update balanceamount vector by removing the deleted balance
            for (int j = 0; j < balanceamount.size(); j++) {
                if (balanceamount[j] == deletedBalance) {
                    balanceamount.erase(balanceamount.begin() + j);
                    return true;
                    break;
                }
            }

            
        }
    }
    return false;
}

int CubicProbing::databaseSize() {
        // cout<<"databasesize:"<<endl;

    int i=0;
    for(int j=0;j<bankStorage1d.size();j++){
        if(bankStorage1d[j].balance!=-1){
            i++;
        }
    }
    return i;
}
   CubicProbing::       CubicProbing()

    {
        bankStorage1d.resize(k);
        for (int i = 0; i < k; i++)
        {
            bankStorage1d[i].balance = -1;
        }
    }