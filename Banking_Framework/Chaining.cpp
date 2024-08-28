#include "Chaining.h"
#include"vector"
using namespace std;

void Chaining::maintainsize(int t){
    if(bankStorage2d.size()<t){
        while(bankStorage2d.size()<=t){
            bankStorage2d.push_back({});
        }
    }
}

void Chaining::createAccount(std::string id, int count) {
    int idx=hash(id);
    maintainsize(idx);
    Account acc;
    acc.balance=count;
    acc.id=id;
    bankStorage2d[idx].push_back(acc);
    sixe++;
}

std::vector<int> Chaining::getTopK(int k) {
    vector<int>balances;
    for(int i=0;i<bankStorage2d.size();i++){
        if(bankStorage2d[i].size()!=0){
            for(int j=0;j<bankStorage2d[i].size();j++){
                balances.push_back(bankStorage2d[i][j].balance);
            }
        }
    }
    bool swap;
    int n = balances.size();
    for (int i = 0; i < n-1 ; i++)
    {
        swap = false;
        for (int j = 0; j < n - i - 1; j++){
            if (balances[j] < balances[j + 1])
            {
                int temp = balances[j];
                balances[j] = balances[j + 1];
                balances[j + 1] = temp;
                swap = true;
            }
        }if(swap==false){
            break;
        }
    }
    vector<int> finalcopy;
    for (int i = 0; i <k && i<n; i++)
    {
        finalcopy.push_back(balances[i]);
    }
    return finalcopy;
}

int Chaining::getBalance(std::string id) {
    if(doesExist(id)){
        int t=hash(id);
        int i=0;
        while(i<bankStorage2d[t].size()){
            if(bankStorage2d[t][i].id==id){
                return bankStorage2d[t][i].balance;
                break;
            }
            i++;
        }
    }
    return -1;   
}

void Chaining::addTransaction(std::string id, int count) {
    if(doesExist(id)){
        int t=hash(id);
        int i=0;
        while(i<bankStorage2d[t].size()){
            if(bankStorage2d[t][i].id==id){
                bankStorage2d[t][i].balance=bankStorage2d[t][i].balance+count;
                break;
            }
            i++;
        }
    }else{
        createAccount(id,count);
    }
}

bool Chaining::doesExist(std::string id) {
    int t=hash(id);
    if(bankStorage2d.size()>=t){
        int i=0;
        while(i<bankStorage2d[t].size()){
            if(bankStorage2d[t][i].id==id){
                return true;
                break;
            }
            i++;
        }
    }
    return false; 
}

bool Chaining::deleteAccount(std::string id) {
    int t=hash(id);
    if(bankStorage2d.size()>t){
        int i=0;
        while(i<bankStorage2d[t].size()){
            if(bankStorage2d[t][i].id==id){
                sixe--;
                bankStorage2d[t].erase(bankStorage2d[t].begin()+i);
                return true;
                break;
            }
            i++;
        }
    }
    return false; 
}

int Chaining::databaseSize() {
    return sixe;
}

int Chaining::hash(std::string id) {
    double i=0;
    for(int j=0;j<id.size();j++){
        i=i+0.71*j*id[j];
    }
    double mp=i*0.61803297;
    int k=100000*(mp-int(mp));
    return k%99991;
}

/*
#include <cassert>
void testDatabase(BaseClass *db)
{
    Chaining lb;
    cout << lb.hash("Alice");
    cout << "k";
    db->createAccount("Alice", 1000);
    cout << "l";

    db->createAccount("Bob", 1500);
    db->createAccount("Charlie", 2000);
    cout << "l"<<endl;
    cout<<db->getBalance("Alice")<<endl;

    assert(db->getBalance("Alice") == 1000);
    cout << "l";
    assert(db->getBalance("Bob") == 1500);
    assert(db->getBalance("Charlie") == 2000);
    cout << "l";

    db->addTransaction("Alice", -200);
    db->addTransaction("Bob", 300);
    db->addTransaction("Charlie", -400);
    cout << "l";

    assert(db->getBalance("Alice") == 800);
    assert(db->getBalance("Bob") == 1800);
    assert(db->getBalance("Charlie") == 1600);
    cout << "u";

    std::vector<int> topBalances = db->getTopK(2);
    cout << "t";
    assert(topBalances.size() == 2);
    cout<<"2";
    assert(topBalances[0] == 1800);
    assert(topBalances[1] == 1600);
    cout << "m";

    assert(db->databaseSize() == 3);

    assert(db->doesExist("Alice"));
    assert(!db->doesExist("Eve"));
    
}
int main()
{
      Chaining chainingDB;
      std::cout << "Testing Chaining:" << std::endl;
    
    
      testDatabase(&chainingDB);
    
    
      cout << "succes ";
    /*Chaining raman;
    raman.createAccount("raman",20000);
    raman.createAccount("hemant",79246);
    raman.createAccount("kamal",563784);
    cout<<raman.doesExist("raman")<<endl;
    cout<<raman.getBalance("raman")<<endl;
    cout<<raman.doesExist("hemant")<<endl;
    cout<<raman.getBalance("hemant")<<endl;
    cout<<raman.doesExist("kamal")<<endl;
    cout<<raman.getBalance("kamal")<<endl;
    cout<<raman.databaseSize()<<endl;
    std::vector<int> outputVector = raman.getTopK(2);

    // Print the elements of the vector
    for (int i : outputVector) {
        std::cout << i << " ";
    }

    std::cout << std::endl;

    cout<<"complete";

    return 0;*/



