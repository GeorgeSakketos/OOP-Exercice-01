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
        int last_customer, curr_serving, K, M, N, L, openCashiers;

        Cashiers* cashiersArray;

    public:
        Bank(int, int, int, int);
        void enter();
        void serve();
        void exit();
        bool check_to_open(int);
        bool check_to_close(int);
        void open(int);
        void close(int);
        void waiting_customers();
        void open_cashiers();
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

void Cashiers::free(int L, int cashierNum)
{
    serving_flag = false;
    customers_served++;

    if (customers_served == L)
    {
        close();
        cout << "[INFO] Cashier no " << cashierNum << " over worked. Closing cashier!" << "\n";
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
    openCashiers++;
    last_customer = 1;
}

void Bank::enter()
{
    // Find if there are available cashiers to serv
    int runs = 0, lastOpenCashier;
    if (check_to_open(K))
    {
        bool foundCashier = false, prevCashier, nextCashier;
        int curCashier = 0;
        while(!foundCashier && runs < 5)
        {   
            prevCashier = cashiersArray[curCashier++].is_open();

            if (curCashier == 5)
                curCashier = 0;

            nextCashier = cashiersArray[curCashier].is_open();

            if (prevCashier && !nextCashier)
            {
                open(curCashier);
                foundCashier = true;
            }
            runs++;
        }
    }
    
    // If everyone is busy, tell the customer
    if (runs == 4)
        cout << "Sorry you cannot enter until some customers are served!" << "\n";
    else
        curr_serving++;    
}

void Bank::serve()
{
    if (openCashiers == 0)
        open(1);
    
    for (int curCashier = 0; curCashier < 5; curCashier++)
    {
        bool prevCashier = cashiersArray[curCashier].is_open() && cashiersArray[curCashier].is_free();
        bool nextCashier;
        if (curCashier == 4)
            nextCashier = cashiersArray[0].is_open() && cashiersArray[0].is_free();
        else
            nextCashier = cashiersArray[curCashier + 1].is_open() && cashiersArray[curCashier + 1].is_free();

        if (!prevCashier && nextCashier)
        {
            cout << "Customer no: " << curr_serving << " by cashier no: " << nextCashier + 1 << "\n";
            cashiersArray[nextCashier].serve();
            cashiersArray[nextCashier].free(L, nextCashier);
            exit();
        }
    }
}

void Bank::exit()
{
    curr_serving++;
    if (check_to_close(K))
        for (int curCashier = 0; curCashier < 5; curCashier++)
            if (cashiersArray[curCashier].is_open())
            {
                close(curCashier + 1);
                curCashier = 5;
            }
}

bool Bank::check_to_open(int K)
{
    if ((last_customer - curr_serving) > (openCashiers * K))
        return true;
    return false;
}

bool Bank::check_to_close(int K)
{
    if ((last_customer - curr_serving) <= ((openCashiers - 1) * K))
        return true;
    return false;
}

void Bank::open(int cashier)
{
    cashiersArray[cashier - 1].open();
    cout << "Cashier no: " << cashier << " just opened" << "\n"; 
}

void Bank::close(int cashier)
{
    cashiersArray[cashier].close();
    cout << "Cashier no: " << cashier << " just closed" << "\n"; 
}

void Bank::waiting_customers()
{
    cout << "Waiting Customers: " << last_customer - curr_serving << "\n";
}

void Bank::open_cashiers()
{
    cout << "Open Cashiers: " << openCashiers << "\n";
}
