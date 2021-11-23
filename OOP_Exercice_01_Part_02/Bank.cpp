#include <iostream>
#include <string>
using namespace std;

class Cashiers
{
        bool open_flag = false;
        bool serving_flag = false;
        int customers_served;

    public:
        void open();
        void close();
        void serve();
        void free(int, int);
        bool is_open();
        bool is_free();
};

class Bank
{
        int last_customer, curr_serving, K, M, N, L;

        Cashiers* cashiersArray;

    public:
        Bank(int, int, int, int);
        void enter();
        void serve();
        void exit();
};

// Cashiers Cashiers Cashiers Cashiers Cashiers Cashiers

void Cashiers::open()
{
    open_flag = true;
    serving_flag = false;
    customers_served = 0;
}

void Cashiers::close()
{
    open_flag = false;
}

void Cashiers::serve()
{
    serving_flag = true;
}

void Cashiers::free(int L, int tellerNum)
{
    serving_flag = false;
    customers_served++;

    if (customers_served == L)
    {
        close();
        cout << "[INFO] Cashier no " << tellerNum << " over worked. Closing cashier!" << "\n";
    }
}   

bool Cashiers::is_open()
{
    return open_flag;
}

bool Cashiers::is_free()
{
    return !serving_flag;
}

// BANK BANK BANK BANK BANK BANK BANK BANK BANK BANK
Bank::Bank(int k, int m, int n, int l)
{
    K = k;
    M = m;
    N = n;
    L = l;

    cashiersArray = new Cashiers[5];

    cashiersArray[0].open();
    last_customer = 1;
}

void Bank::enter()
{
    // Find if there are available tellers to serv
    int availableTeller = -1, busyTellers = 0, lastOpenTeller;
    for (int curCashier = 0; curCashier < 5; curCashier++)
    {
        if (cashiersArray[curCashier].is_open())
        {
            if (cashiersArray[curCashier].is_free())
            {
                availableTeller = curCashier;
                curCashier = 5;
            }
            else
                busyTellers++;
            lastOpenTeller = curCashier;
        }
    }

    // If there aren't any available tellers check if you can open another teller
    if (availableTeller != -1)
        curr_serving++;
    else if (busyTellers == 5)
        cout << "Sorry you cannot enter until some customers are served!" << "\n";
    else
    {
        lastOpenTeller++;
        for (int curCashier = 0; curCashier < 5; curCashier++)
        {
            if (curCashier + lastOpenTeller == 5)
                lastOpenTeller = 0;
            if (!cashiersArray[curCashier + lastOpenTeller].is_open())
            {
                cashiersArray[curCashier + lastOpenTeller].open();
                availableTeller = curCashier + lastOpenTeller;
                curCashier = 5;
            }
        }
    }
}

void Bank::serve()
{
    bool anyTellersOpen = false;
    int lastOpenTeller;
    for (int curCashier = 0; curCashier < 5; curCashier++)
    {
        anyTellersOpen = (anyTellersOpen || cashiersArray[curCashier].is_open());
        if (cashiersArray[curCashier].is_open())
            lastOpenTeller = curCashier;
    }

    int serving;
    if (!anyTellersOpen)
    {
        cashiersArray[0].open();
        serving = 0;
    }
    else
    {
        lastOpenTeller++;
        for (int curCashier = 0; curCashier < 5; curCashier++)
        {
            if (curCashier + lastOpenTeller == 5)
                lastOpenTeller = 0;
            if (!cashiersArray[curCashier + lastOpenTeller].is_open())
            {
                cashiersArray[curCashier + lastOpenTeller].open();
                serving = curCashier + lastOpenTeller;
                curCashier = 5;
            }
        }
    }
    cout << "Customer no: " << curr_serving << " by cashier no: " << serving << "\n";

    cashiersArray[serving].serve();
    cashiersArray[serving].free(L, serving);
}

void Bank::exit()
{
    curr_serving++;
    int notNeededCashiers = 5 - (last_customer - curr_serving);

    if (notNeededCashiers > 0)
        for (int curCashier = 0; curCashier < 5; curCashier++)
        {
            if (cashiersArray[curCashier].is_open() && cashiersArray[curCashier].is_free())
            {
                cashiersArray[curCashier].close();
                notNeededCashiers--;
            }
        }
}

int main()
{
    
}

