#include "bookcart.h"
#define max 3

struct book
{
    string bookTitle;
    string fullAuthorsName;
    long int ISBN;
};

string strings[max];

int len(string str)  
{  
    int length = 0;  
    for (int i = 0; str[i] != '\0'; i++)  
    {  
        length++;  
          
    }  
    return length;     
}  

void split (string str, char seperator)  
{  
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= len(str))  
    {  
        if (str[i] == seperator || i == len(str))  
        {  
            endIndex = i;  
            string subStr = "";  
            subStr.append(str, startIndex, endIndex - startIndex);  
            strings[currIndex] = subStr;  
            currIndex += 1;  
            startIndex = endIndex + 1;  
        }  
        i++;  
        }     
}  

book randomBook()
{
    ifstream file("books.txt");
    book* bookArray = new book[100];
    int skipped_pos = max;

    for (int i = 0; i < 100; i++)
    {
        char seperator = '|';
        string line;
        getline(file, line);
        split(line, seperator);

        if (!strings[0].empty() == true)
        {
            book Book;
            Book.bookTitle = strings[0];
            Book.fullAuthorsName = strings[1];
            Book.ISBN = stoi(strings[2]);

            bookArray[i] = Book;
            skipped_pos--;
        }
    }

    int randomNum = rand() % (max - skipped_pos);

    return bookArray[randomNum];
}
