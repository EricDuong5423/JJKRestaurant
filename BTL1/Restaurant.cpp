#include "main.h"

class Red: public Restaurant::customer
{
    public:
    Red();
    static void addLeft(customer *cus, customer *X) {
        customer*temp = X->next;
        temp->prev = cus;
        cus->next = temp;
        cus->prev = X;
        X->next = cus;
    }
    static void addRight(customer *cus, customer *X){
        customer*temp = X->prev;
        temp->next = cus;
        cus->prev = temp;
        cus->next = X;
        X->prev = cus;
    }
    static bool checkDup(customer *cus, customer *headR, customer *waitingLine, int countR, int countLine){
        if (countR == 0)return false;
        customer*run = headR;
        if(run->name == cus->name)
        {
            return true;
        }
        run = run->next;
        while(run != headR && run != NULL)
        {
            if (run->name == cus->name)
            {
                return true;
            }
            run = run->next;
        }
        if (countLine == 0)return false;
        run = waitingLine;
        if(run->name == cus->name)
        {
            return true;
        }
        run = run->next;
        while(run != NULL)
        {
            if(run->name == cus->name)
            {
                return true;
            }
        }
        return false;
    }
    static customer* findHighRes(customer *cus, customer *headR)
    {
        customer*run = headR;
        customer*highRes = run;
        int subabs, max = -1;
        do {
            subabs = abs(cus->energy - run->energy);
            if (subabs > max)
            {
                max = subabs;
                highRes = run;
            }
            run = run->next;
        }while (run != headR);
        return highRes;
    }
    static void addwaitLine(customer *cus, customer* waitingLine, customer* endLine, int &countLine)
    {
        if (countLine < MAXSIZE)
        {
            if (countLine == 0)
            {
                waitingLine = cus;
                endLine = cus;
            }
            else
            {
                waitingLine->prev = cus;
                cus->next = waitingLine;
                waitingLine = cus;
            }
            countLine++;
        }
    }
};

class Print:public Restaurant::customer
{
    public:
    static void toStringRestaurant(customer* headR)
    {
        customer*run = headR;
        cout << "Restaurant:";
        do {
            if (run->next == headR)
            {
                cout << "[" << run->name << "," << run->energy << "]";
            }
            else
            {
                cout << "[" << run->name << "," << run->energy << "] <=> ";
            }
            run=run->next;
        }while (run != headR);
        cout << endl;
    }
    static void toStringLine(customer* waitingLine)
    {
        customer*run = waitingLine;
        cout << "Line:";
        while(run != NULL)
        {
            if (run->next == NULL)
            {
                cout << "[" << run->name << "," << run->energy << "]";
            }
            else
            {
                cout << "[" << run->name << "," << run->energy << "] => ";
            }
        }
    }
};

class imp_res : public Restaurant
{
    public:
    customer*headR;
    customer*X;
    customer*endLine;
    customer*waitingLine;
    int countR;
    int countLine;
	public:	
		imp_res() {
            headR = nullptr;
            X = nullptr;
            endLine = nullptr;
            waitingLine = nullptr;
            countR = 0;
            countLine = 0;
        };
		void RED(string name, int energy)
		{
			cout << name << " " << energy << endl;
			customer *cus = new customer (name, energy, nullptr, nullptr);
            if (energy != 0)
            {
                if (Red::checkDup(cus, headR, waitingLine, countR, countLine) == true)return;
                if (headR == nullptr){
                    headR = X = cus;
                    cus->next = headR;
                    cus->prev = headR;
                    countR++;
                }
                else if (countR == MAXSIZE){
                    Red::addwaitLine(cus, waitingLine, endLine, countLine);
                }
                else if (countR < MAXSIZE/2){
                    if (energy >= X->energy)Red::addLeft(cus, X), X = cus;
                    else Red::addRight(cus,X), X = cus;
                    countR++;
                }
                else if (countR >= MAXSIZE/2){
                    customer*highRes = Red::findHighRes(cus, headR);
                    if (cus->energy - highRes->energy > 0)Red::addLeft(cus,highRes);
                    else Red::addRight(cus,highRes), X = cus;
                    countR++;
                }
            }
		}
		void BLUE(int num)
		{
			cout << "blue "<< num << endl;
		}
		void PURPLE()
		{
			cout << "purple"<< endl;
		}
		void REVERSAL()
		{
			cout << "reversal" << endl;
		}
		void UNLIMITED_VOID()
		{
			cout << "unlimited_void" << endl;
		}
		void DOMAIN_EXPANSION()
		{
			cout << "domain_expansion" << endl;
		}
		void LIGHT(int num)
		{
			cout << "light " << num << endl;
		}
};