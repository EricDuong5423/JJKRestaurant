#include "main.h"

class imp_res : public Restaurant
{
    public:
    customer*headR = nullptr;
    customer*waitingLine = nullptr;
    customer*X = nullptr;
    customer*endLine = nullptr;
    customer*FIFOHead = nullptr;
    customer*firstKick = nullptr;
    int countR = 0;
    int countLine = 0;
    int countFIFO = 0;
    void    addRight(customer *cus);
    void    addLeft(customer *cus);
    void    findhighRES(customer *cus);
    bool    checkDuplicate(customer*cus);
    void    addwaitingLine(customer*cus);
    void    addtoFIFO(customer *cus);
    void    kickCus();
    void    addfromLine();
    //Lúc nộp nhớ xóa mấy hàm toString();
    void    toStringRestaurant();
    void    toStringLine();
    void    toStringFIFO();
	public:	
		imp_res() {};
		void RED(string name, int energy)
		{
			cout << name << " " << energy << endl;
			customer *cus = new customer (name, energy, nullptr, nullptr);
            if (energy != 0)
            {
                if (checkDuplicate(cus) == true)return;
                if (headR == nullptr)
                {
                    headR = X = cus;
                    cus->next = headR;
                    cus->prev = headR;
                    addtoFIFO(cus);
                    countR++;
                }
                else if (countR == MAXSIZE)
                {
                    addwaitingLine(cus);
                }
                else if (countR < MAXSIZE/2)
                {
                    if (energy >= X->energy)
                    {
                        addLeft(cus);
                        countR++;
                    }
                    else
                    {
                        addRight(cus);
                        countR++;
                    }
                    addtoFIFO(cus);
                }
                else if (countR >= MAXSIZE/2)
                {
                    findhighRES(cus);
                    addtoFIFO(cus);
                    countR++;
                }
            }
		}
		void BLUE(int num)
		{
			cout << "blue "<< num << endl;
            kickCus();
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

void imp_res::addLeft(Restaurant::customer *cus) {
    customer*temp = X->next;
    temp->prev = cus;
    cus->next = temp;
    cus->prev = X;
    X->next = cus;
    X = cus;
}
void imp_res::addRight(Restaurant::customer *cus) {
    customer*temp = X->prev;
    temp->next = cus;
    cus->prev = temp;
    cus->next = X;
    X->prev = cus;
    X = cus;
}
bool imp_res::checkDuplicate(Restaurant::customer *cus) {
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
void imp_res::findhighRES(Restaurant::customer *cus) {
    customer*run = headR;
    int subabs = abs(cus->energy - run->energy), max = subabs, sub = cus->energy - run->energy;
    run = run->next;
    while(run != headR)
    {
        subabs = abs(cus->energy - run->energy);
        sub = cus->energy - run->energy;
        if (subabs > max)
        {
            max = subabs;
            X = run;
        }
        run=run->next;
    }
    if (sub < 0)
    {
        addRight(cus);
    }
    else
    {
        addLeft(cus);
    }
}
void imp_res::addwaitingLine(Restaurant::customer *cus) {
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
void imp_res::addtoFIFO(Restaurant::customer *cus) {
    customer*clone = new customer(cus->name, cus->energy, nullptr, nullptr);
    if (countFIFO == 0)
    {
        FIFOHead = clone;
        firstKick = clone;
    }
    else
    {
        clone->next = FIFOHead;
        FIFOHead->prev = clone;
        FIFOHead = clone;
    }
    countFIFO++;
}
void imp_res::kickCus() {
    customer*run = headR;
    customer*next;
    customer*pre;
    while(run->name != firstKick->name)
    {
        run=run->next;
    }
    if (run->energy > 0)X=run->next;
    else X = run->prev;
    next = run->next;
    pre = run->prev;
    pre->next = next;
    next->prev = pre;
    countR--;
    countFIFO--;
    if (countFIFO != 0)
    {
        customer*temp = firstKick;
        firstKick = firstKick->prev;
        firstKick->next = nullptr;
        temp->prev = nullptr;
        temp->next = nullptr;
        delete temp;
        headR = next;
        run->prev = nullptr;
        run->next = nullptr;
        delete run;
    }else firstKick = headR = X = nullptr;
}
void imp_res::addfromLine() {

}


void imp_res::toStringRestaurant() {
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
}
void imp_res::toStringLine() {
    customer*run = waitingLine;
    cout << "Line:";
    while (run != NULL)
    {
        if (run->next == NULL)
        {
            cout << "[" << run->name << "," << run->energy << "]";
        }
        else
        {
            cout << "[" << run->name << "," << run->energy << "] => ";
        }
        run=run->next;
    }
}
void imp_res::toStringFIFO() {
    customer*run = FIFOHead;
    cout << "FIFO:";
    do
    {
        if (run->next == NULL)
        {
            cout << "[" << run->name << "," << run->energy << "]";
        }
        else
        {
            cout << "[" << run->name << "," << run->energy << "] => ";
        }
        run=run->next;
    }while(run != NULL);
}