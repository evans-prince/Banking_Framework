#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include "BaseClass.h"
#include <iostream>

class LinearProbing : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    int finalidx(std::string id);
    LinearProbing()

    {
        bankStorage1d.resize(k);
        for (int i = 0; i < k; i++)
        {
            bankStorage1d[i].balance = -1;
            bankStorage1d[i].id="0";
        }
    }
    void resixe(int k);
    void Swapp(int& a,int& b);
private:
    int size=0;
    const int k = 7;
    std::vector<int>balanceamount;
};

#endif // LINEARPROBING_H
