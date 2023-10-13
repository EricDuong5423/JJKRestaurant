#include "main.h"

class imp_res : public Restaurant
{
    private:
        customer*customerX; //TODO:Lưu khách mới được thay đổi gần đây
        int sizeCusInDesk; //TODO: Biến đếm số lượng khách ở bàn

        customer*customerQueueTail; //TODO:Lưu những vị Khách ở hàng đợi để làm iterator
        customer*customerQueueHead;//TODO:Lưu người đầu tiên trong hàng đợi để dễ dàng làm việc
        int sizeCusInQueue;//TODO:Biến đếm số lượng khách ở trong hàng đợi

    public:
        class customerTime{ //TODO:Class lưu lại thứ tự khách được cho vào bàn ăn
        public:
            customer*data;
            customerTime*next;
            customerTime*pre;
            bool inDesk;
        public:
            customerTime(customer * data, bool inDesk){
                this->data = data;
                this->inDesk = inDesk;
                next = pre = nullptr;
            }//TODO:constructor class customerTime
            ~customerTime(){delete data;}//TODO:deconstructor class customerTime
        };//TODO:Class lưu timeline của các vị khách cho vào bàn ăn
    public:
        imp_res()
        {
            customerX = nullptr;
            sizeCusInDesk = 0;

            customerQueueTail = customerQueueHead = nullptr;
            sizeCusInQueue = 0;

            CustomerTimeHead = CustomerTimeTail = nullptr;
        }

    private:
        customerTime *CustomerTimeTail;//TODO:Lưu thứ tự các vị khách được cho vào bàn ăn
        customerTime *CustomerTimeHead;//TODO:Lưu người đầu tiên trong timeline vào bàn ăn
    //TODO:Hàm dành cho RED
    public:
        bool checkDuplicate(string name);//TODO:check "thiên thượng thiên hạ, duy chỉ độc tôn", nếu có trùng trả về true không thì ngược lại
        void appendQueue(customer*cus);//TODO:cho vị khách vào hàng chờ
        void appendTimeline(customerTime * newTimeline);//TODO:cho vị khách vào time line mỗi khi add
        customer *findHighRES(customer *cus);//TODO:Tìm vị trí có RES cao nhất để trả về
        void addLeft(customer*cus);//TODO:thêm vị khách theo chiều thuận kim đồng hồ của customerX
        void addRight(customer*cus);//TODO:thêm vị khách theo chiều ngược kim đồng hồ của customerX
    //TODO:Hàm dành cho BLUE
    public:
        customerTime*findKickingCustomer();//TODO:hàm trả về customer cần bị kick trong bàn tròn.
        void kickCustomer(customerTime*kickingCus);//TODO:hàm đuổi khách đã được xác định
        void invitefromQueue();//TODO:Mời những vị khách trong hàng chờ vào nhà hàng và xóa vị khách đó ra khỏi hàng chờ
        void addinDesk(customer*Customer);//TODO:Add lại vào trong nhà hàng
    //TODO:Hàm dành cho DOMAIN EXPASION
    public:
        void kickSoccerer();//TODO:kick hết chú thuật sư
        void kickEvilSpirit();//TODO: kick hết oán linh
        void kickinQueue(customerTime*kickingCus);//TODO: kick trong hàng chờ
    public:
        void RED(string name, int energy)
        {
            if (energy == 0)return;//TODO:Đuổi khách khi khách không phải oán linh hoặc thuật sư
            else if (sizeCusInDesk >= MAXSIZE && sizeCusInQueue >= MAXSIZE)return;//TODO:Đuổi khách khi quá tải cả ở bàn và trong hàng đợi
            else{
                if (checkDuplicate(name) == true)return;
            }//TODO:Đuổi khách khi tên trùng với ai đó ở bàn ăn hoặc hàng đợi

            //TODO:Sau khi check xem có đuổi khách hay không thì tiếp tục check xem khách được vào bàn hay vào hàng đợi
            customer* newCus = new customer(name,energy, nullptr, nullptr);//TODO:tạo một customer là khách mới vào

            //TODO:check xem khách có bị đưa vào hàng chờ không ?
            if (sizeCusInDesk == MAXSIZE){
                appendQueue(newCus);
                customerTime*newTimeline = new customerTime(newCus,false);
                appendTimeline(newTimeline);
                return;
            }//TODO:nếu trên có số lượng vượt ra khỏi qui định MAXSIZE thì add vào hàng đợi

                //TODO:nếu không vào hàng chờ thì khách sẽ được đưa vào bàn là link list tròn đôi
            else if (sizeCusInDesk == 0){
                customerX = newCus;
                newCus->prev = customerX;
                newCus->next = customerX;
                sizeCusInDesk++;
                customerTime*newTimeline = new customerTime(customerX,true);
                appendTimeline(newTimeline);
                return;
            }//TODO:Nếu là vị khách đầu tiên thì prev với next bằng chính nó và customerX sẽ cập nhật
            else if (sizeCusInDesk >= MAXSIZE/2){
                customerX = findHighRES(newCus);//Đi tìm vị trí có RES cao nhất và gán nó cho customerX
                if (newCus->energy - customerX->energy >= 0)addLeft(newCus);//nếu hiệu energy của newCus và customerX dương thì add left, không thì ngược lại
                else addRight(newCus);
                sizeCusInDesk++;
                customerTime *newTimeLine = new customerTime(newCus,true);
                appendTimeline(newTimeLine);
                customerX = newCus;
                return;
            }//TODO:Khi số lượng >= MAXSIZE/2 thì phải tìm vị trí HighRES rồi add
            else{
                if (newCus->energy >= customerX->energy)addLeft(newCus);//TODO:Nếu energy lớn hơn customerX thì add chiều kim đồng hồ, không thì ngược lại
                else addRight(newCus);
                sizeCusInDesk++;
                customerTime*newTimeline = new customerTime(newCus,true);
                appendTimeline(newTimeline);
                customerX = newCus;
                return;
            }//TODO:Trường hợp tổng quát
        }
        void BLUE(int num)
        {
            if (sizeCusInDesk == 0)return;//TODO:nếu không có khách trên bàn thì không xóa.
            if (num > sizeCusInDesk)num=sizeCusInDesk;//TODO:Chặn trường hợp num chạy quá số lượng khách trên bàn ăn.
            for(int i = 0; i < num; i++)
            {
                customerTime*deleteCus = findKickingCustomer();
                kickCustomer(deleteCus);
            }//TODO:Xóa khách num lần và xóa luôn thứ tự trong timeLine
            invitefromQueue();
            return;
        }
        void PURPLE()
        {

        }
        void REVERSAL()
        {

        }
        void UNLIMITED_VOID()
        {

        }
        void DOMAIN_EXPANSION()
        {
            if(sizeCusInDesk == 0 && sizeCusInQueue == 0)return;
            int SoccererEnergy = 0, EvilSpiritEnergy = 0;
            customerTime*run = CustomerTimeHead;
            while(run != nullptr){
                if (run->data->energy > 0){
                    SoccererEnergy += run->data->energy;
                }
                else{
                    EvilSpiritEnergy += run->data->energy;
                }
                run = run->next;
            }
            EvilSpiritEnergy = abs(EvilSpiritEnergy);
            run = nullptr;
            if (SoccererEnergy == 0 || EvilSpiritEnergy == 0)return;
            if(SoccererEnergy >= EvilSpiritEnergy){
                kickEvilSpirit();
            }
            else{
                kickSoccerer();
            }
            invitefromQueue();
        }
        void LIGHT(int num)
        {
            if (num == 0 && sizeCusInQueue != 0){
                customer*print = customerQueueHead;
                if(print == nullptr)return;
                while(print != nullptr)
                {
                    print->print();
                    print = print->next;
                }
                return;
            }//TODO:nếu num == 0 thì in hết tất cả trong hàng chờ
            else if (num > 0){
                customer*print = customerX;
                if(print == nullptr)return;
                for(int i = 0; i < sizeCusInDesk; i++)
                {
                    print->print();
                    print = print->next;
                }
                return;
            }//TODO:in thuận chiều kim đồng hồ nếu mà num dương
            else if (num < 0){
                customer*print = customerX;
                if(print == nullptr)return;
                for(int i = 0; i < sizeCusInDesk; i++)
                {
                    print->print();
                    print = print->prev;
                }
                return;
            }//TODO:in ngược chiều kim đồng hồ nếu mà num âm
        }
};

//RED
bool imp_res::checkDuplicate(string name) {
    customer*checkTable = customerX;
    customer*checkQueue = customerQueueHead;
    if (sizeCusInDesk != 0){
        do {
            if (checkTable->name == name)
            {
                return true;
            }
            checkTable = checkTable->next;
        }while(checkTable != customerX); //TODO:vì trên bàn là circle double link list nên chỉ chạy tới thằng customerX để tránh bị vòng lặp vô tận
    }//TODO:nếu số lượng khách ở bàn == 0 thì bỏ qua ko cần check

    if (sizeCusInQueue != 0){
        while(checkQueue != nullptr){
            if (checkQueue->name == name)
            {
                return true;
            }
            checkQueue = checkQueue->next;
        }
    }//TODO:nếu số lượng khách ở hàng đợi == 0 thì bỏ qua mà return false luôn
    checkTable = nullptr;
    checkQueue = nullptr;
    delete checkTable;
    delete checkQueue;
    return false;
}
void imp_res::appendQueue(Restaurant::customer *cus){
    if (sizeCusInQueue == 0){
        customerQueueTail = cus;
        customerQueueHead = cus;
    }//TODO:nếu là người đầu tiên thì cho vào đầu hàng chờ
    else{
        customerQueueTail->next = cus;
        customerQueueTail = cus;
    }//TODO:bằng không thì add ra sau cùng hàng chờ
    sizeCusInQueue++;
}
void imp_res::appendTimeline(imp_res::customerTime *newTimeline) {
    if (CustomerTimeTail == nullptr){
        CustomerTimeHead = CustomerTimeTail = newTimeline;
    }//TODO:nếu là người đầu tiên thì lưu vào đầu timeLine
    else{
        CustomerTimeTail->next = newTimeline;
        newTimeline->pre = CustomerTimeTail;
        CustomerTimeTail = newTimeline;
    }//TODO:Không thì add sau liên kết
}
Restaurant::customer* imp_res::findHighRES(customer *cus)
{
    customer*run = customerX;
    customer*result = run;
    int max = -1;
    for(int i = 0; i < sizeCusInDesk; i++)
    {
        int absSub = abs(cus->energy - run->energy);
        if (absSub > max)
        {
            max = absSub;
            result = run;
        }
        run = run->next;
    }
    run = nullptr;
    delete run;
    return result;
}
void imp_res::addLeft(Restaurant::customer *cus) {
    customer*temp = customerX->next;
    temp->prev = cus;
    cus->next = temp;
    customerX->next = cus;
    cus->prev = customerX;
    customerX = cus;
    temp = nullptr;
    delete temp;
}
void imp_res::addRight(Restaurant::customer *cus) {
    customer*temp = customerX->prev;
    temp->next = cus;
    cus->prev = temp;
    customerX->prev = cus;
    cus->next = customerX;
    customerX = cus;
    temp = nullptr;
    delete temp;
}

//BLUE
imp_res::customerTime*imp_res::findKickingCustomer() {
    customerTime*run = CustomerTimeHead;
    while(run != nullptr){
        if(run->inDesk == true){
            return run;
        }
        run = run->next;
    }
    return nullptr;
}
void imp_res::kickCustomer(imp_res::customerTime *kickingCus){
    sizeCusInDesk--;
    if(sizeCusInDesk == 0){
        customerX = nullptr;
        if(sizeCusInQueue != 0){
            CustomerTimeHead = CustomerTimeHead->next;
            CustomerTimeHead->pre = nullptr;
        }
        else{
            delete CustomerTimeHead;
            CustomerTimeHead = CustomerTimeTail = nullptr;
        }
    }
    else{
        if(kickingCus->data->energy > 0)customerX=kickingCus->data->next;
        else customerX=kickingCus->data->prev;

        kickingCus->data->prev->next = kickingCus->data->next;
        kickingCus->data->next->prev = kickingCus->data->prev;
        if(kickingCus == CustomerTimeHead) {
            CustomerTimeHead = CustomerTimeHead->next;
            CustomerTimeHead->pre = nullptr;
        }
        else{
            kickingCus->pre->next = kickingCus->next;
            if(kickingCus == CustomerTimeTail){
                CustomerTimeTail = kickingCus->pre;
                CustomerTimeTail->next = nullptr;
            }
            else{
                kickingCus->next->pre = kickingCus->pre;
            }
        }
        delete kickingCus;
    }
}
void imp_res::invitefromQueue() {
    while(sizeCusInQueue != 0 && sizeCusInDesk != MAXSIZE){
        customerTime*temp = CustomerTimeHead;
        for(int i = 0;i < sizeCusInQueue + sizeCusInDesk; i++){
            if (temp->data == customerQueueHead){
                break;
            }
            else{
                temp = temp->next;
            }
        }
        if(temp->data == customerQueueTail){
            customerQueueHead = customerQueueTail = nullptr;
        }
        else{
            customerQueueHead = customerQueueHead->next;
        }
        temp->inDesk = true;
        addinDesk(temp->data);
        sizeCusInQueue--;
    }
}
void imp_res::addinDesk(customer*newCus){
    if (sizeCusInDesk == 0){
        customerX = newCus;
        newCus->prev = customerX;
        newCus->next = customerX;
        sizeCusInDesk++;
    }//TODO:Nếu là vị khách đầu tiên thì prev với next bằng chính nó và customerX sẽ cập nhật
    else if (sizeCusInDesk >= MAXSIZE/2){
        customerX = findHighRES(newCus);//Đi tìm vị trí có RES cao nhất và gán nó cho customerX
        if (newCus->energy - customerX->energy >= 0)addLeft(newCus);//nếu hiệu energy của newCus và customerX dương thì add left, không thì ngược lại
        else addRight(newCus);
        sizeCusInDesk++;
        customerX = newCus;
    }//TODO:Khi số lượng >= MAXSIZE/2 thì phải tìm vị trí HighRES rồi add
    else{
        if (newCus->energy >= customerX->energy)addLeft(newCus);//TODO:Nếu energy lớn hơn customerX thì add chiều kim đồng hồ, không thì ngược lại
        else addRight(newCus);
        sizeCusInDesk++;
        customerX = newCus;
    }//TODO:Trường hợp tổng quát
}

//DOMAIN_EXPASION
void imp_res::kickSoccerer() {
    customerTime*run = CustomerTimeTail;
    while(run != nullptr){
        if(run->data->energy > 0){
            if (run->inDesk == true){
                customerTime*temp = run;
                temp->data->print();
                run = run->pre;
                kickCustomer(temp);
            }
            else{
                customerTime*temp = run;
                temp->data->print();
                run = run->pre;
                kickinQueue(temp);
            }
        }
        else{
            run = run->pre;
        }
    }
}
void imp_res::kickEvilSpirit() {
    customerTime*run = CustomerTimeTail;
    while(run != nullptr){
        if(run->data->energy < 0){
            if (run->inDesk == true){
                customerTime*temp = run;
                temp->data->print();
                run = run->pre;
                kickCustomer(temp);
            }
            else{
                customerTime*temp = run;
                temp->data->print();
                run = run->pre;
                kickinQueue(temp);
            }
        }
        else{
            run = run->pre;
        }
    }
}
void imp_res::kickinQueue(imp_res::customerTime *kickingCus) {
    sizeCusInQueue--;
    if(sizeCusInQueue == 0){
        CustomerTimeTail = CustomerTimeTail->pre;
        CustomerTimeTail->next = nullptr;
        delete kickingCus;
    }
    else{
        if(kickingCus->data == customerQueueHead){
            customerQueueHead = customerQueueHead->next;
        }
        else{
            customer*temp = customerQueueHead;
            customer*run = temp->next;
            while(run != kickingCus->data){
                temp = run;
                run = run->next;
            }
            if(run == customerQueueTail)customerQueueTail = temp;
            temp->next = run->next;
            temp = nullptr;
        }
        kickingCus->pre->next = kickingCus->next;
        if(kickingCus == CustomerTimeTail){
            CustomerTimeTail = kickingCus->pre;
            CustomerTimeTail->next = nullptr;
        }
        else{
            kickingCus->next->pre = kickingCus->pre;
        }
        delete kickingCus;
    }
}