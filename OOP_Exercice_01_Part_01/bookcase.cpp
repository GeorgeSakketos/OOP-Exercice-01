#include <iostream>
#include <string>
using namespace std;

struct book
{
    string bookTitle;
    string fullAuthorsName;
    long int ISBN;
};

class Bookcase
{
        int N_Max, K1, K2, L;
        static const int shelvesInBookcase = 5;
        book** baseArray;
        int booksOnShelve [5] = {0, 0, 0, 0, 0};
        void placeOnShelve(int, book);
        void placeOnCabinet(int, book);
        void takeFromShelve(int);
        void takeFromCabinet(int);
        void destroyShelves();
        void destroyCabinet();

    public:
        void initBookcase(int, int, int, int);
        bool place_book(int, book);
        bool take_book(int);
        void print_book(book);
        void print_Shelve(int);
        void print_Cabinet_Shelve(int);
        void print_Bookcase();
        void destroyShelve(int);
        void destroyCabinetShelve(int);
        void destroyBookcase();
};

void Bookcase::initBookcase(int n_max, int l, int k1, int k2)
{
    cout << "[BOOKCASE STATUS] Creating Bookcase" << "\n";

    N_Max = n_max;
    L = l; 
    
    cout << "[BOOKCASE STATUS] Creating the Base" << "\n";

    // Creating a 2D Array of Structs
    baseArray = new book*[shelvesInBookcase];
    for(int posInArray = 0; posInArray < shelvesInBookcase; posInArray++)
    {
        if (posInArray == 0)
            cout << "[BOOKCASE STATUS] Creating the Shelves" << "\n";
        else if (posInArray == shelvesInBookcase - 2)
            cout << "[BOOKCASE STATUS] Creating the Cabinet" << "\n";

        book* row = new book[N_Max];
        baseArray[posInArray] = row;
    }
}

void Bookcase::print_book(book Book)
{
    cout << "|Book name: " << Book.bookTitle << "| Authors name: " << Book.fullAuthorsName << "| ISBN: " << Book.ISBN << "|\n";
}

bool Bookcase::place_book(int Shelve, book Book)
{
    if (booksOnShelve[Shelve - 1] == N_Max)
        return false;
    // Where should we place the book (A Shelves or The Cabinet)?
    if (Shelve < 4)
        placeOnShelve(Shelve, Book);
    else if (Shelve < 6)
        placeOnCabinet(Shelve, Book);
    return true;
}

void Bookcase::placeOnShelve(int Shelve, book Book)
{
    if (Shelve == 1)
        cout << "\n" << "[BOOKCASE ACTION] Placing book on the top Shelve of the Bookcase" << "\n";
    else if (Shelve == 2)
        cout << "\n" << "[BOOKCASE ACTION] Placing book on the middle Shelve of the Bookcase" << "\n";
    else if (Shelve == 3)
        cout << "\n" << "[BOOKCASE ACTION] Placing book on the bottom Shelve of the Bookcase" << "\n";
    print_book(Book);

    if (Shelve < 4)
        booksOnShelve[Shelve - 1]++;
        // Place book on corresponding Shelve
        for(int pos = 0; pos < booksOnShelve[Shelve - 1]; pos++)
        {
            // Look for an empty spot
            if (baseArray[Shelve - 1][pos].bookTitle.empty() == true)
            {
                baseArray[Shelve - 1][pos] = Book;
                pos = booksOnShelve[Shelve - 1];
            }
        }
}

void Bookcase::placeOnCabinet(int Shelve, book Book)
{
    if (Shelve == 4)
        cout << "\n" << "[BOOKCASE ACTION] Placing book on the top Shelve of the Cabinet" << "\n";
    else if (Shelve == 5)
        cout << "\n" << "[BOOKCASE ACTION] Placing book on the bottom Shelve of the Cabinet" << "\n";
    print_book(Book);

    if (Shelve < 6)
        booksOnShelve[Shelve - 1]++;
        // Place book on corresponding Cabient Shelve
        for(int pos = 0; pos < booksOnShelve[Shelve - 1]; pos++)
        {
            // Look for an empty spot
            if (baseArray[Shelve - 1][pos].bookTitle.empty() == true)
            {
                baseArray[Shelve - 1][pos] = Book;
                pos = booksOnShelve[Shelve - 1];
            }
        }
}   

bool Bookcase::take_book(int Shelve)
{
    if (booksOnShelve[Shelve - 1] == 0)
        return false;
    // Where should we take a book from (A Shelve or The Cabient)?
    if (Shelve < 4)
        takeFromShelve(Shelve);
    else if (Shelve < 6)
        takeFromCabinet(Shelve);
    return true;
}

void Bookcase::takeFromShelve(int Shelve)
{
    if (Shelve == 1)
        cout << "\n" << "[BOOKCASE ACTION] Taking book from the top Shelve of the Bookcase" << "\n";
    else if (Shelve == 2)
        cout << "\n" << "[BOOKCASE ACTION] Taking book from the middle Shelve of the Bookcase" << "\n";
    else if (Shelve == 3)
        cout << "\n" << "[BOOKCASE ACTION] Taking book from the bottom Shelve of the Bookcase" << "\n";

    // The book we want to remove should be a random book
    srand((unsigned) time(NULL));
    int randPos = (rand() % booksOnShelve[Shelve - 1]);

    baseArray[Shelve - 1][randPos].bookTitle.clear();
    baseArray[Shelve - 1][randPos].fullAuthorsName.clear();
    baseArray[Shelve - 1][randPos].ISBN = 0;
    booksOnShelve[Shelve - 1]--;
}

void Bookcase::takeFromCabinet(int Shelve)
{
    if (Shelve - 3 == 1)
        cout << "\n" << "[BOOKCASE ACTION] Taking book from the top Shelve of the Cabinet" << "\n";
    else if (Shelve - 3 == 2)
        cout << "\n" << "[BOOKCASE ACTION] Taking book from the bottom Shelve of the Cabinet" << "\n";

    // The book we want to remove should be a random book
    srand((unsigned) time(NULL));
    int randPos = (rand() % booksOnShelve[Shelve - 1]);
    while (randPos >= L)
        randPos = (rand() % booksOnShelve[Shelve - 1]);

    baseArray[Shelve - 1][randPos].bookTitle.clear();
    baseArray[Shelve - 1][randPos].fullAuthorsName.clear();
    baseArray[Shelve - 1][randPos].ISBN = 0;
    booksOnShelve[Shelve - 1]--;
}

void Bookcase::print_Shelve(int Shelve)
{
    if (booksOnShelve[Shelve - 1] > 0)
    {
        cout << "\n" << "[INFO] Shelve " << Shelve << " containes: " << "\n"; 
        int books = booksOnShelve[Shelve - 1];
        for(int posInShelve = 0; posInShelve < books; posInShelve++)
        {
            // We only read the books that exist inside the bookcase shelves (We can't read air)
            if (baseArray[Shelve - 1][posInShelve].bookTitle.empty() == true)
            {
                posInShelve++;
                books++;
            }
            cout << "|Book name: " << baseArray[Shelve - 1][posInShelve].bookTitle << "| Authors name: " << baseArray[Shelve - 1][posInShelve].fullAuthorsName << "| ISBN: " << baseArray[Shelve - 1][posInShelve].ISBN << "|\n";
        }
    }
    else
        cout << "\n" << "[INFO] Shelve " << Shelve << " is empty" << "\n";
}

void Bookcase::print_Cabinet_Shelve(int Shelve)
{
    if (booksOnShelve[Shelve + 2] > 0)
    {
        cout << "\n" << "[INFO] Cabinet Shelve " << Shelve << " containes: " << "\n";
        int books = booksOnShelve[Shelve + 2];
        for(int posInShelve = 0; posInShelve < books; posInShelve++)
        {
            // We only read the books that exist inside the bookcase cabient (We can't read air)
            if (baseArray[Shelve + 2][posInShelve].bookTitle.empty() == true)
            {
                posInShelve++;
                books++;
            }
            cout << "|Book name: " << baseArray[Shelve + 2][posInShelve].bookTitle << "| Authors name: " << baseArray[Shelve + 2][posInShelve].fullAuthorsName << "| ISBN: " << baseArray[Shelve + 2][posInShelve].ISBN << "|\n";
        }
    }
    else
        cout << "\n" << "[INFO] Cabinet Shelve " << Shelve << " is empty" << "\n";
}

void Bookcase::print_Bookcase()
{
    for (int curShelve = 0; curShelve < shelvesInBookcase - 2; curShelve++)
        print_Shelve(curShelve + 1);
    for (int curShelve = 0; curShelve < shelvesInBookcase - 3; curShelve++)
        print_Cabinet_Shelve(curShelve + 1);
}

void Bookcase::destroyShelve(int Shelve)
{
    cout << "[BOOKCASE STATUS] Destroying Shelve " << Shelve <<"\n";
    delete [] baseArray[Shelve - 1];
}

void Bookcase::destroyShelves()
{
    cout << "[BOOKCASE STATUS] Destroying Shelves " <<"\n";
    delete [] baseArray[0];
    delete [] baseArray[1];
    delete [] baseArray[2];
}

void Bookcase::destroyCabinetShelve(int Shelve)
{
    cout << "[BOOKCASE STATUS] Destroying Cabinet Shelve " << Shelve <<"\n";
    delete [] baseArray[Shelve + 2];
}

void Bookcase::destroyCabinet()
{
    cout << "[BOOKCASE STATUS] Destroying Cabinet" << "\n";
    delete [] baseArray[3];
    delete [] baseArray[4];
}

void Bookcase::destroyBookcase()
{
    cout << "\n";
    destroyShelves();
    destroyCabinet();
    cout << "[BOOKCASE STATUS] Destroying Base" << "\n";
    cout << "[BOOKCASE STATUS] Destroying Bookcase" << "\n";
    int booksOnShelve[5] = {0, 0, 0, 0, 0};
    delete [] baseArray;
}

#include "bookcart.h"

int main(int argc, char** argv)
{
    Bookcase bookcase;
    
    if (argc != 5)
    {
        cout << "[ERROR] Insufficient Arguments! Give 4 arguments (N Max, L, K1, K2)" << "\n";
        exit(0);
    }

    int N_Max = atoi(argv[1]) * 5;
    int L = atoi(argv[2]);
    int K1 = atoi(argv[3]);
    int K2 = atoi(argv[4]);

    if (N_Max < L)
        L = N_Max;

    bookcase.initBookcase(N_Max, L, K1, K2);

    // Add L books inside the bookcase
    int curShelve = 1;
    for (int booksToInsert = 0; booksToInsert < (L - K1); booksToInsert++)
    {
        if (curShelve == 6)
            curShelve = 1;
        
        bookcase.place_book(curShelve++, randomBook());
    }

    // Add K1 books on random positions
    srand((unsigned) time(NULL));
    for (int randomBooks = 0; randomBooks < K1; randomBooks++)
    {
        int randShelve = 1 + (rand() % 5);
        bookcase.place_book(randShelve, randomBook());
    }

    // Remove K2 books from random positions
    srand((unsigned) time(NULL));

    // Make sure what we want to remove can be removed, else correct it
    if (K2 > L )
        K2 = L;
    
    for (int randomBooks = 0; randomBooks < K2; randomBooks++)
    {
        int randShelve = 1 + (rand() % 5);
        int foundBook = 0;
        while (bookcase.take_book(randShelve) != 1)
        {
            randShelve = 1 + (rand() % 5);
        }
    }

    bookcase.print_Bookcase();

    bookcase.destroyBookcase();

    return 0;
}