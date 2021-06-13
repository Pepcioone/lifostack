/*
    STOS LIFO
    - tablica dynamiczna
    - lista
    - embedded
    ONP
    - string
    - input
    Damian MAŁY
    WSTI 2IO_II
*/
#include <iostream>
#include <sstream>
#include <time.h>
#include <cstdlib>
#include <stack>
#include <iomanip>
#include <math.h>
using namespace std;

// #define WINDOWS /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <windows.h>
#define ASleep Sleep(1000)
#define CLR "cls"
#else
#include <unistd.h>
#define ASleep sleep(1)
#define CLR "clear"
#endif //WINDOWS

// ---------------------
// ------ GLOBAL -------
// ---------------------
const int STACK_NOSIZE = 1;
const int STACK_NOMEMORY = 2;
clock_t start, stop;

// ---------------------
// -- KLASY,PROCEDURY --
// ---------------------

// stackARRAY
template <class myT>
class stackARRAY
{
protected:
    long max;
    long top;
    myT *arr = NULL;
    string msg;
    bool show;

public:
    stackARRAY(long size = 0, bool show = false)
    {
        max = size;
        top = 0;
        this->show = show;
        if (size > 0)
        {
            try
            {
                arr = new myT[size];
            }
            catch (...)
            {
                msg = "*Stack initial failed (no memory)";
                showMsg();
                throw STACK_NOMEMORY;
            }
            long rozm = sizeof(myT);
            long sizeT = size * rozm;
            msg = "*Stack initiated (size " + to_string(size) + " * " + to_string(rozm) + " = " + to_string(sizeT) + " bytes)";
        }
        else
        {
            msg = "*Stack initial failed";
            showMsg();
            throw STACK_NOSIZE;
        }
        showMsg();
    }

    ~stackARRAY()
    {
        show = false;
        clear();
    }

    bool isEmpty()
    {
        return (top == 0);
    }

    bool isFull()
    {
        return (top == max);
    }

    void push(myT value)
    {
        if (isFull())
        {
            msg = "---Push: " + to_string(value) + " (Overflow)";
        }
        else
        {
            arr[top] = value;
            top++;
            msg = "---Push: " + to_string(value);
        }
        showMsg();
    }

    myT pop()
    {
        myT value;
        if (isEmpty())
        {
            value = -1;
            msg = "---Pop: (Underflow)";
        }
        else
        {
            top--;
            value = arr[top];
            arr[top] = 0;
            msg = "---Pop: " + to_string(value);
        }
        showMsg();
        return value;
    }

    myT peek() // topValue
    {
        myT value;
        if (isEmpty())
        {
            value = -1;
            msg = "---Peek: (No item to return)";
        }
        else
        {
            value = arr[top - 1];
            msg = "---Peek: " + to_string(value);
        }
        showMsg();
        return value;
    }

    int maxSize()
    {
        return max;
    }

    int topValue()
    {
        return top;
    }

    void clear()
    {
        if (arr)
        {
            delete[] arr;
            arr = NULL; //UWAGA, windows nie czysci pointerow.
            max = 0;
            top = 0;
            msg = "*Stack cleared";
        }
        else
        {
            msg = "*Stack not found";
        }
        showMsg();
    }

    void showContent()
    {
        msg = "Content of stack (maxSize=" + to_string(maxSize()) + ",topValue=" + to_string(topValue()) + "): ";

        if (isEmpty())
        {
            msg += "empty";
        }
        else
        {
            for (int i = max - 1; i >= 0; i--)
            {
                msg += to_string(arr[i]) + ",";
            }
        }
        bool temp = show;
        show = true;
        showMsg();
        show = temp;
    }

    void showMsg()
    {
        if (show)
            cout << msg << endl;
    }
};

// stackLIST
template <class myT>
class stackLIST
{
protected:
    struct Node
    {
        myT data;
        Node *next;
    };
    Node *item;
    Node *temp;
    long max;
    long top;
    string msg;
    bool show;

public:
    stackLIST(long size = 0, bool show = false)
    {
        max = size;
        top = 0;
        item = nullptr;
        temp = nullptr;
        this->show = show;
        if (size > 0)
        {
            long rozm = sizeof(Node);
            long sizeT = size * rozm;
            msg = "*Stack initiated (size " + to_string(size) + " * " + to_string(rozm) + " = " + to_string(sizeT) + " bytes)";
        }
        else
        {
            msg = "*Stack initial failed";
            showMsg();
            throw STACK_NOSIZE;
        }
        showMsg();
    }

    ~stackLIST()
    {
        show = false;
        clear();
        delete temp;
    }

    bool isEmpty()
    {
        return (top == 0);
    }

    bool isFull()
    {
        return (top == max);
    }

    void push(myT value)
    {
        if (isFull())
        {
            msg = "---Push: " + to_string(value) + " (Overflow)";
        }
        else
        {
            try
            {
                Node *newNode = new Node;
                newNode->data = value;
                if (isEmpty())
                {
                    newNode->next = nullptr;
                    msg = "---Push: " + to_string(value) + " (First)";
                }
                else
                {
                    newNode->next = item;
                    msg = "---Push: " + to_string(value);
                }
                item = newNode;
                top++;
            }
            catch (...)
            {
                msg = "*---Push: failed (no memory)";
                showMsg();
                throw STACK_NOMEMORY;
            }
        }
        showMsg();
    }

    myT pop()
    {
        myT value;
        if (isEmpty())
        {
            value = -1;
            msg = "---Pop: (Underflow)";
        }
        else
        {
            temp = item;
            value = item->data;
            item = temp->next;
            top--;
            msg = "---Pop: " + to_string(value);
        }
        showMsg();
        return value;
    }

    myT peek() // topValue
    {
        myT value;
        if (isEmpty())
        {
            value = -1;
            msg = "---Peek: (No item to return)";
        }
        else
        {
            value = item->data;
            msg = "---Peek: " + to_string(value);
        }
        showMsg();
        return value;
    }

    int maxSize()
    {
        return max;
    }

    int topValue()
    {
        return top;
    }

    void clear()
    {
        while (!isEmpty())
            pop();
        msg = "*Stack cleared";
        showMsg();
    }

    void showContent()
    {
        msg = "Content of stack (maxSize=" + to_string(maxSize()) + ",topValue=" + to_string(topValue()) + "): ";

        if (isEmpty())
        {
            msg += "empty";
        }
        else
        {
            temp = item;
            for (int i = max - 1; i >= 0; i--)
            {
                if (i < top)
                {
                    msg += to_string(temp->data) + ",";
                    temp = temp->next;
                }
                else
                {
                    msg += "0,";
                }
            }
        }
        bool tempb = show;
        show = true;
        showMsg();
        show = tempb;
    }

    void showMsg()
    {
        if (show)
            cout << msg << endl;
    }
};

// stack embedded
void showstack(stack<int> s)
{
    string msg = "Content of stack (topValue=" + to_string(s.size()) + "): ";
    while (!s.empty())
    {
        msg += to_string(s.top()) + ",";
        s.pop();
    }
    cout << msg << endl;
}

// procedure
double czas(string pomiar = "")
{
    if (pomiar == "start")
    {
        start = clock();
        return 0;
    }
    if (pomiar == "stop")
    {
        stop = clock();
        return 0;
    }
    return (double)(stop - start) / CLOCKS_PER_SEC;
}

float wylicz_mnoznik(bool status, float mnoznik, long *MAX, long *MAXtemp)
{
    // Automat dobierajacy wartosc alokowanej pamieci
    // tak aby jak najblizej zblizyc sie do wartosci granicznej
    // w jak najkrotszym czasie
    const float PRECISION = 1.0001;
    ASleep;
    if (status)
    {
        if (mnoznik < PRECISION)
            return -1;
        else
        {
            *MAXtemp = *MAX;
            *MAX = (long)(*MAX * mnoznik);
        }
    }
    else
    {
        if (mnoznik < 2.0)
        {
            mnoznik = 1 + ((mnoznik - 1) / 2);
        }
        else
        {
            mnoznik /= 2;
        }
        if (mnoznik < PRECISION)
            return -1;
        *MAX = (long)(*MAXtemp * mnoznik);
    }

    cout.precision(9);
    cout << "MAX = " << *MAX << ", mnoznik = " << mnoznik << endl;
    return mnoznik;
}

int priorytet(string oper);

// ---------------------
// ------- MAIN --------
// ---------------------
int main(int argc, char *argv[])
{

    //sysctl vm.overcommit_memory=2
    //sysctl vm.overcommit_ratio=100
    //echo "vm.overcommit_memory=2" >> /etc/sysctl.conf
    //echo "vm.overcommit_ratio=100" >> /etc/sysctl.conf
    //system linux, wylaczenie zabezpieczenia przed killowaniem
    //aplikacji zasobozernych, na potrzeby hard testow

    system(CLR);
    int wybor = 0;
    if (argc > 1)
        wybor = stoi(argv[1]);
    if (wybor < 0 or wybor > 8)
        wybor = 0;

    cout << "MAIN MENU:" << endl;
    cout << "------------------------------------------" << endl;
    cout << "1. LIFO - dynamic array method - simple" << endl;
    cout << "2. LIFO - dynamic array method - hard" << endl;
    cout << "3. LIFO - list method - simple" << endl;
    cout << "4. LIFO - list method - hard" << endl;
    cout << "5. LIFO - embedded method - simple" << endl;
    cout << "6. LIFO - embedded method - hard" << endl;
    cout << "7. ONP  - string example" << endl;
    cout << "8. ONP  - input example" << endl;

    cout << "0. Exit" << endl;
    cout << "------------------------------------------" << endl;
    cout << "Choice: ";

    cin.clear();
    bool arg = true;
    if (wybor == 0)
    {
        cin >> wybor;
        arg = true;
    }
    else
    {
        cout << wybor << endl;
        arg = false;
    }

    if (wybor == 1)
    { //Stack dynamic array implementation
        cout << "---------------------" << endl;
        cout << "Stack dynamic array implementation : simple test" << endl;
        cout << endl;
        long stosSize = 3;
        // stackARRAY *stos = new stackARRAY(stosSize, true);
        // stackARRAY<int> stos(stosSize, true);
        stackARRAY<int> *stos = new stackARRAY<int>(stosSize, true);

        stos->showContent();
        stos->push(5);
        stos->showContent();
        stos->push(3);
        stos->showContent();
        stos->push(4);
        stos->showContent();
        stos->push(7);
        stos->showContent();
        stos->pop();
        stos->showContent();
        stos->peek();
        stos->showContent();
        stos->pop();
        stos->showContent();
        stos->pop();
        stos->showContent();
        stos->pop();
        stos->showContent();
        stos->peek();
        stos->showContent();
        stos->clear();
        stos->showContent();
        delete stos;

        cout << endl;
        cout << "Test ended : simple" << endl;
        cout << "-------------------" << endl;
        cout << endl;
    } //END

    if (wybor == 2)
    { //Stack dynamic array implementation
        cout << "-------------------" << endl;
        cout << "Stack dynamic array implementation : hard test" << endl;
        cout << endl;

        // long MAX = 1000000000;
        long MAX = 1;
        long MAXtemp = MAX;
        float mnoznik = 10;
        do
        {
            try
            {
                do
                {
                    czas("start");
                    stackARRAY<int> *stos = new stackARRAY<int>(MAX, false);
                    czas("stop");
                    cout << "Allocated stack size : " << MAX << ", Time: " << czas() << " [s]" << endl;

                    czas("start");
                    for (long wartosc = 1; wartosc <= MAX; wartosc++)
                    {
                        stos->push(wartosc);
                        // cout << "\rPush: " << wartosc << " " << flush;
                        // ASleep;
                    }
                    czas("stop");
                    cout << "--> Pushed on stack : " << MAX << ", Time: " << czas() << " [s]" << endl;

                    czas("start");
                    delete stos;
                    czas("stop");
                    cout << "DeAllocated stack size : " << MAX << ", Time: " << czas() << " [s]" << endl;
                    cout << endl;

                    if (wylicz_mnoznik(true, mnoznik, &MAX, &MAXtemp) == -1)
                        break;
                } while (true);
                break;
            }
            catch (...)
            {
                mnoznik = wylicz_mnoznik(false, mnoznik, &MAX, &MAXtemp);
                if (mnoznik == -1)
                    break;
            }

        } while (true);

        cout << endl;
        cout << "Test ended : hard" << endl;
        cout << "-----------------" << endl;
    } //END

    if (wybor == 3)
    { //Stack linked list implementation
        cout << "---------------------" << endl;
        cout << "Stack linked list implementation : simple test" << endl;
        cout << endl;

        long stosSize = 3;
        stackLIST<int> *stos = new stackLIST<int>(stosSize, true);

        stos->showContent();
        stos->push(5);
        stos->showContent();
        stos->push(3);
        stos->showContent();
        stos->push(4);
        stos->showContent();
        stos->push(7);
        stos->showContent();
        stos->pop();
        stos->showContent();
        stos->peek();
        stos->showContent();
        stos->pop();
        stos->showContent();
        stos->pop();
        stos->showContent();
        stos->pop();
        stos->showContent();
        stos->peek();
        stos->showContent();
        stos->clear();
        stos->showContent();
        delete stos;

        cout << endl;
        cout << "Test ended : simple" << endl;
        cout << "-------------------" << endl;
        cout << endl;
    } //END

    if (wybor == 4)
    { //Stack linked list implementation
        cout << "-------------------" << endl;
        cout << "Stack linked list implementation : hard test" << endl;
        cout << endl;

        long MAX = 1;
        long MAXtemp = MAX;
        float mnoznik = 10;
        do
        {
            try
            {
                do
                {
                    czas("start");
                    stackLIST<int> *stos = new stackLIST<int>(MAX, false);
                    czas("stop");
                    cout << "Allocated stack size : " << MAX << ", Time: " << czas() << " [s]" << endl;

                    czas("start");
                    for (long wartosc = 1; wartosc <= MAX; wartosc++)
                    {
                        stos->push(wartosc);
                        // cout << "\rPush: " << wartosc << " " << flush;
                        // ASleep;
                    }
                    czas("stop");
                    cout << "--> Pushed on stack : " << MAX << ", Time: " << czas() << " [s]" << endl;

                    czas("start");
                    delete stos;
                    czas("stop");
                    cout << "DeAllocated stack size : " << MAX << ", Time: " << czas() << " [s]" << endl;
                    cout << endl;

                    if (wylicz_mnoznik(true, mnoznik, &MAX, &MAXtemp) == -1)
                        break;
                } while (true);
                break;
            }
            catch (...)
            {
                mnoznik = wylicz_mnoznik(false, mnoznik, &MAX, &MAXtemp);
                if (mnoznik == -1)
                    break;
            }

        } while (true);

        cout << endl;
        cout << "Test ended : hard" << endl;
        cout << "-----------------" << endl;
    } //END

    if (wybor == 5)
    { //Stack embedded implementation
        cout << "---------------------" << endl;
        cout << "Stack embedded implementation : simple test" << endl;
        cout << endl;

        int value = 0;
        stack<int> stos;

        showstack(stos);
        value = 5;
        cout << "---Push: " << value << endl;
        stos.push(value);
        showstack(stos);
        value = 3;
        cout << "---Push: " << value << endl;
        stos.push(value);
        showstack(stos);
        value = 4;
        cout << "---Push: " << value << endl;
        stos.push(value);
        showstack(stos);
        value = 7;
        cout << "---Push: " << value << endl;
        stos.push(value);
        showstack(stos);
        cout << "---Pop: " << endl;
        stos.pop();
        showstack(stos);
        cout << "---Peek: " << endl;
        stos.top();
        showstack(stos);
        cout << "---Pop: " << endl;
        stos.pop();
        showstack(stos);
        cout << "---Pop: " << endl;
        stos.pop();
        showstack(stos);
        cout << "---Pop: " << endl;
        stos.pop();
        showstack(stos);
        cout << "---Peek: " << endl;
        stos.top();
        showstack(stos);
        cout << "---Empty: " << endl;
        stos.empty();
        showstack(stos);

        cout << endl;
        cout << "Test ended : simple" << endl;
        cout << "-------------------" << endl;
        cout << endl;
    } //END

    if (wybor == 6)
    { //Stack embedded implementation
        cout << "-------------------" << endl;
        cout << "Stack embedded implementation : hard test" << endl;
        cout << endl;

        long MAX = 1;
        long MAXtemp = MAX;
        float mnoznik = 10;
        do
        {
            try
            {
                do
                {
                    czas("start");
                    stack<int> stos;
                    czas("stop");
                    cout << "Allocated stack size : " << MAX << ", Time: " << czas() << " [s]" << endl;

                    czas("start");
                    for (long wartosc = 1; wartosc <= MAX; wartosc++)
                    {
                        stos.push(wartosc);
                        // cout << "\rPush: " << wartosc << " " << flush;
                        // ASleep;
                    }
                    czas("stop");
                    cout << "--> Pushed on stack : " << MAX << ", Time: " << czas() << " [s]" << endl;

                    czas("start");
                    stos.empty();
                    czas("stop");
                    cout << "DeAllocated stack size : " << MAX << ", Time: " << czas() << " [s]" << endl;
                    cout << endl;

                    if (wylicz_mnoznik(true, mnoznik, &MAX, &MAXtemp) == -1)
                        break;
                } while (true);
                break;
            }
            catch (...)
            {
                mnoznik = wylicz_mnoznik(false, mnoznik, &MAX, &MAXtemp);
                if (mnoznik == -1)
                    break;
            }

        } while (true);

        cout << endl;
        cout << "Test ended : hard" << endl;
        cout << "-----------------" << endl;
    } //END

    if (wybor == 7 or wybor == 8)
    { //ONP
        cout << "-------------------" << endl;
        cout << "ONP : test (+,-,*,/,^,sin,cos,tan,ctan,pi,e,log,sqrt,ln,.)" << endl;
        string example = "(2+ 31 ) * 5*sin(3+4)+pi^1.2+cos(2)+e^2+log(10)+sqrt(16)+ln(e)-100=";
        cout << "Example : " + example << endl;
        cout << endl;

        //String or Input
        string sONP = "";
        if (wybor == 7)
            sONP = example;
        else
        {
            cout << "Input expression : ";
            if (arg)
            {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            getline(cin, sONP, '\n');
        }
        if ( sONP == "" )
        {
            cout << "Expression : empty" << endl;
            return 0;
        }

        cout << "Expression : " << sONP << endl;

        //Parser String to Array lines
        int dl = sONP.length();
        string pONP[dl + 1];

        int i = 0;
        int nrlinii = 0;
        int typ = 0;
        bool bfunc = false;
        bool bstale = false;
        string stale = "$pi$e$";
        string funkcje = "#sin#cos#tan#ctan#log#ln#sqrt#";
        string temp = "";

        while (true)
        {
            if (bfunc = (funkcje.find("#" + pONP[nrlinii] + "#") != std::string::npos))
                temp = "#" + pONP[nrlinii];

            if (bstale = (stale.find("$" + pONP[nrlinii] + "$") != std::string::npos))
                temp = "$" + pONP[nrlinii];

            if (i == dl)
            {
                switch (typ)
                {
                case 1:
                    nrlinii++;
                    break;
                case 2:
                    if (bfunc or bstale)
                    {
                        pONP[nrlinii] = temp;
                        nrlinii++;
                    }
                    break;
                }
                pONP[nrlinii++] = "=";
                break;
            }

            switch (sONP[i])
            {
            case '(':
            case ')':
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
            case '=':
                switch (typ)
                {
                case 1:
                    nrlinii++;
                    break;
                case 2:
                    if (bfunc or bstale)
                    {
                        pONP[nrlinii] = temp;
                        nrlinii++;
                    }
                    break;
                }
                typ = 0;
                pONP[nrlinii++] = sONP[i];
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
                switch (typ)
                {
                case 0:
                    pONP[nrlinii] = "";
                    break;
                case 2:
                    if (bfunc or bstale)
                    {
                        pONP[nrlinii] = temp;
                        nrlinii++;
                    }
                    pONP[nrlinii] = "";
                    break;
                }
                typ = 1;
                pONP[nrlinii] += sONP[i];
                break;
            default:
                switch (typ)
                {
                case 0:
                    pONP[nrlinii] = "";
                    break;
                case 1:
                    nrlinii++;
                    pONP[nrlinii] = "";
                    break;
                }
                typ = 2;
                pONP[nrlinii] += sONP[i];
                break;
            }
            if (sONP[i] == '=')
                break;
            else
                i++;
        }

        //Convert Array lines to ONP Array lines
        //pONP -> array lines
        //pONPconv -> ONP array lines
        //nrlinii -> amount of array lines
        long stosSize = nrlinii;
        stack<string> stos; //embedded version
        string pONPconv[dl + 1];

        int nr = 0;
        for (i = 0; i < nrlinii; i++)
        {
            switch (pONP[i][0])
            {
            case '$':
                pONPconv[nr++] = pONP[i];
                break;
            case '#':
            case '(':
                stos.push(pONP[i]);
                break;
            case ')':
                while (stos.top() != "(")
                {
                    pONPconv[nr++] = stos.top();
                    stos.pop();
                }
                stos.pop(); //pobranie ze stosu nawiasu otwierajacego "("
                if (!stos.empty())
                {
                    if (stos.top()[0] == '#') //sprawdzenie czy nie ma jeszcze funkcji
                    {
                        pONPconv[nr++] = stos.top();
                        stos.pop();
                    }
                }
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                while (!stos.empty())
                {
                    // Wyskakujemy z iteracji jeżeli priorytet odczytanego operatora
                    // jest wyższy lub równy od operatora ze szczytu stosu
                    if (priorytet(pONP[i]) >= priorytet(stos.top()))
                        break;
                    // Zdejmujemy operatory o wyższych priorytetach
                    pONPconv[nr++] = stos.top();
                    stos.pop();
                }
                stos.push(pONP[i]);
                break;
            case '=':
                while (!stos.empty())
                {
                    pONPconv[nr++] = stos.top();
                    stos.pop();
                }
                pONPconv[nr++] = pONP[i];
                break;
            default:
                pONPconv[nr++] = pONP[i];
                break;
            }
        }

        //Show Array and ONP array lines
        cout << setw(3) << "LP" << setw(14) << "Array" << setw(14) << "ONP Array" << endl;
        for (i = 0; i < nrlinii; i++)
        {
            cout << setw(3) << i << "= " << setw(14) << pONP[i] << setw(14) << pONPconv[i] << endl;
        }

        //Calculate ONP
        double wynik = 0.0;
        double pierwsza = 0.0;
        double druga = 0.0;
        string param = "";
        for (i = 0; i < nr; i++)
        {
            switch (pONPconv[i][0])
            {
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                druga = stod(stos.top());
                stos.pop();
                pierwsza = stod(stos.top());
                stos.pop();
                switch (pONPconv[i][0])
                {
                case '+':
                    wynik = pierwsza + druga;
                    break;
                case '-':
                    wynik = pierwsza - druga;
                    break;
                case '*':
                    wynik = pierwsza * druga;
                    break;
                case '/':
                    wynik = pierwsza / druga;
                    break;
                case '^':
                    wynik = pow(pierwsza, druga);
                    break;
                default:
                    wynik = 0.0;
                    break;
                }
                stos.push(to_string(wynik));
                break;
            case '$': //stale
                param = pONPconv[i];
                wynik = 0.0;
                if (bstale = (stale.find(param) != std::string::npos))
                {
                    if (param == "$pi")
                        wynik = M_PI;
                    if (param == "$e")
                        wynik = exp(1);
                }
                stos.push(to_string(wynik));
                break;
            case '#': //funkcje
                param = pONPconv[i];
                wynik = 0.0;
                if (bfunc = (funkcje.find(param) != std::string::npos))
                {
                    pierwsza = stod(stos.top());
                    stos.pop();
                    if (param == "#sin")
                        wynik = sin(pierwsza);
                    if (param == "#cos")
                        wynik = cos(pierwsza);
                    if (param == "#tan")
                        wynik = tan(pierwsza);
                    if (param == "#ctan")
                        wynik = 1 / tan(pierwsza); //moze byc zero!
                    if (param == "#log")
                        wynik = log10(pierwsza);
                    if (param == "#ln")
                        wynik = log(pierwsza);
                    if (param == "#sqrt")
                        wynik = sqrt(pierwsza); //moze być ujemna
                }
                stos.push(to_string(wynik));
                break;
            case '=':
                break;
            default:
                stos.push(pONPconv[i]);
                break;
            }
        }
        string result = stos.top();
        stos.pop();
        cout << endl << "ONP result : " << result << endl;

        cout << endl;
        cout << "Test ended : ONP" << endl;
        cout << "-----------------" << endl;
    } //END

    cout << "Thanks for watching (Damian Maly)" << endl;
    return 0;
}

// Function for ONP
int priorytet(string oper)
{
    switch (oper[0])
    {
    case '+':
    case '-':
        return 1;
        break;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
        break;
    }
    return 0;
}