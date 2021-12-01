#include <iostream>
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

void Cashiers::open()
{
    open_flag = true;
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
        cout << "\n" << "Cashier " << cashierNum << " overworked! Now closing." << "\n";
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

class Bank
{
        int last_customer, curr_serving, lastServ;
        int K = 0, L = 0;
        Cashiers* cashiersArray;

        bool check_to_open(int);
        bool check_to_close(int);
        void open(int);
        void close(int);
        int waiting_customers();
        int open_cashiers();

    public:
        Bank(int, int);
        ~Bank();
        bool enter();
        void serve();
        void exit();
};

Bank::Bank(int k, int l)
{   
    K = k;
    L = l;

    cashiersArray = new Cashiers[5];

    open(1);
    last_customer = 1;
    curr_serving = 1;
    lastServ = 0;
}

Bank::~Bank()
{
    delete [] cashiersArray;
}

bool Bank::enter()
{   
    if (check_to_open(K))
    {
        for (int curCashier = 0; curCashier < 5; curCashier++)
        {
            if (!cashiersArray[curCashier].is_open())
            {
                open(curCashier + 1);
                curCashier = 4;
            }
            else if (curCashier == 4)
            {
                cout << "\n" << "Sorry you cannot enter until some customers are served!" << "\n";
                return false;
            }
        }
    }
    last_customer++;
    return true;
}   

void Bank::serve()
{
    int chosenCashier = 1;
    if (open_cashiers() > 0)
    {
        if (lastServ > 4)
            lastServ = 0;
        
        int nextCashier = lastServ + 1;
        for (int curCashier = 0; curCashier < 5; curCashier++)
        {
            if (nextCashier == 6)
                nextCashier = 1;
            if (cashiersArray[nextCashier - 1].is_open() && cashiersArray[nextCashier - 1].is_free())
            {
                chosenCashier = nextCashier;
                lastServ++;
                curCashier = 4;
            }
            else
                nextCashier++;
        }
    }
    else
    {
        open(chosenCashier);
        lastServ = chosenCashier;
    }

    cout << "\n" << "Customer no: " << curr_serving << " by cashier no: " << chosenCashier << "\n";
    cashiersArray[chosenCashier - 1].serve();
    cashiersArray[chosenCashier - 1].free(L, chosenCashier);
    exit();
}

void Bank::exit()
{
    curr_serving++;
    if (check_to_close(K)) 
    {
        for (int curCashier = 0; curCashier < 5; curCashier++)
            if (cashiersArray[curCashier].is_open())
            {
                close(curCashier + 1);
                curCashier = 4;
            }
    }
}

bool Bank::check_to_open(int K)
{
    return waiting_customers() > (open_cashiers() * K);
}

bool Bank::check_to_close(int K)
{
    return waiting_customers() <= ((open_cashiers() - 1) * K);
}

void Bank::open(int Cashier)
{
    cashiersArray[Cashier - 1].open();
    cout << "\n" << "Cashier " << Cashier << " now open!" << "\n";
}

void Bank::close(int Cashier)
{
    cashiersArray[Cashier - 1].close();
    cout << "\n" << "Cashier " << Cashier << " now closed!" << "\n";
}

int Bank::waiting_customers()
{
    return last_customer - curr_serving;
}

int Bank::open_cashiers()
{
    int openCashiers = 0;
    for (int curCashier = 0; curCashier < 5; curCashier++)
    {
        if (cashiersArray[curCashier].is_open())
            openCashiers++;
    }
    return openCashiers;
}

int main(int argc, char** argv)
{
    if (argc != 5)
    {
        cout << "[ERROR] Insufficient Arguments! Give 4 arguments (K, M, N, L)" << "\n";
        exit(0);
    }

    int K = atoi(argv[1]);
    int M = atoi(argv[2]);
    int N = atoi(argv[3]);
    int L = atoi(argv[4]);

    Bank bank(K, L);
    int customersNotServed = 0;

    for (int newCustomers = 0; newCustomers < M; newCustomers++)
    {
        int customersToServe = N;
        if (N > (K * 5))
            customersToServe = (K * 5);

        customersNotServed = N;
        
        for (int addCustomers = 0; addCustomers < (N / (K * 5)); addCustomers++)
        {
            for (int curCustomer = 0; curCustomer < customersToServe; curCustomer++)
                bank.enter();
            for (int curCustomer = 0; curCustomer < customersToServe; curCustomer++)
            {
                bank.serve();
                customersNotServed--;
            }
        }

        while (customersNotServed > 0)
        {
            customersToServe = customersNotServed;
            if (customersNotServed > K * 5)
                customersToServe = K * 5;

            for (int curCustomer = 0; curCustomer < customersToServe; curCustomer++)
                bank.enter();
            for (int curCustomer = 0; curCustomer < customersToServe; curCustomer++)
                bank.serve();
            customersNotServed -= customersToServe;
        }
    }
}