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
        bool inDesk;
    public:
        customerTime(customer * data, bool inDesk) {
            this->data = new customer(data->name, data->energy, nullptr, nullptr);
            this->next = nullptr;
            this->inDesk = inDesk;
        }//TODO:constructor class customerTime
        ~customerTime(){
            this->next = nullptr;
            delete next;
        }//TODO:deconstructor class customerTime
    };//TODO:Class lưu timeline của các vị khách cho vào bàn ăn

public:
    imp_res()
    {
        customerX = nullptr;
        sizeCusInDesk = 0;

        customerQueueTail = customerQueueHead = nullptr;
        sizeCusInQueue = 0;

        CustomerTimeHead = CustomerTimeTail = nullptr;

        listofSoccerer = listofCursedSpirit = nullptr;
    }
    ~imp_res(){
        customerX = customerQueueHead = customerQueueTail = nullptr;
        CustomerTimeHead = CustomerTimeTail = listofCursedSpirit = listofSoccerer = nullptr;
        sizeCusInDesk = sizeCusInQueue = 0;
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
    customer*findKickingCustomer();//TODO:hàm trả về customer cần bị kick trong bàn tròn.
    void kickCustomer(customer*kickingCus);//TODO:hàm đuổi khách đã được xác định
    void popfirstCusDesk();//TODO:Xóa phần tử khách trong bàn vào đầu tiên
    void invitefromQueue();//TODO:Mời những vị khách trong hàng chờ vào nhà hàng và xóa vị khách đó ra khỏi hàng chờ
    void changeStatus(string name);//TODO:Đổi trạng thái của khách trong timeLine
    //TODO:Hàm dành cho domain expansion
public:
    customerTime*listofSoccerer;//TODO:Danh sách chú thuật sư trong nhà hàng
    customerTime*listofCursedSpirit;//TODO:Danh sách các oán linh trong nhà hàng
    int countEnergySoccerer();//TODO:Trả về tổng năng lượng của các chú thuật sư trong nhà hàng và đưa các chú thuật sư vào list
    int countEnergyCursedSpirit();//TODO:Trả về tổng năng lượng của oán linh trong nhà hàng và đưa các oán linh vào list
    void appendSoccerer(customerTime*Soccerer);//TODO:Thêm một chú thuật sư vào list
    void appendCursedSpirit(customerTime*CursedSpirit);//TODO:Thêm một oán linh vào list
    void kickallSoccerer();//TODO:Đuổi hết các chú thuật sư
    void kickallCursedSpirit();//TODO:Đuổi hết các oán linh
    customer*findinDesk(string name);//TODO:Tìm khách cần bị đuổi trong nhà hàng
    void popTimeline(string name);//TODO:Xóa một vị khách trong Timeline
    void kickinQueue(string name);//TODO:Đuổi một vị khách trong hàng đợi về
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
            customerTime*clone = new customerTime(newCus, false);
            appendTimeline(clone);
            appendQueue(newCus);
            return;
        }//TODO:nếu trên có số lượng vượt ra khỏi qui định MAXSIZE thì add vào hàng đợi

            //TODO:nếu không vào hàng chờ thì khách sẽ được đưa vào bàn là link list tròn đôi
        else if (sizeCusInDesk == 0){
            customerX = newCus;
            newCus->prev = customerX;
            newCus->next = customerX;
            sizeCusInDesk++;
            customerTime*newTimeline = new customerTime(customerX, true);
            appendTimeline(newTimeline);
            return;
        }//TODO:Nếu là vị khách đầu tiên thì prev với next bằng chính nó và customerX sẽ cập nhật
        else if (sizeCusInDesk >= MAXSIZE/2){
            customerX = findHighRES(newCus);//Đi tìm vị trí có RES cao nhất và gán nó cho customerX
            if (newCus->energy - customerX->energy >= 0)addLeft(newCus);//nếu hiệu energy của newCus và customerX dương thì add left, không thì ngược lại
            else addRight(newCus);
            sizeCusInDesk++;
            customerTime *newTimeLine = new customerTime(newCus, true);
            appendTimeline(newTimeLine);
            return;
        }//TODO:Khi số lượng >= MAXSIZE/2 thì phải tìm vị trí HighRES rồi add
        else{
            if (newCus->energy >= customerX->energy)addLeft(newCus);//TODO:Nếu energy lớn hơn customerX thì add chiều kim đồng hồ, không thì ngược lại
            else addRight(newCus);
            sizeCusInDesk++;
            customerTime*newTimeline = new customerTime(newCus, true);
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
            customer*Kicking = findKickingCustomer();
            kickCustomer(Kicking);
            popfirstCusDesk();
        }//TODO:Xóa khách num lần và xóa luôn thứ tự trong timeLine
        while(sizeCusInQueue != 0 && sizeCusInDesk != MAXSIZE){
            invitefromQueue();
        }//TODO:cho khách từ hàng chờ lên bàn ăn.
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
    void DOMAIN_EXPANSION(){
        int SoccererEnergy = countEnergySoccerer();
        int CursedSpiritEnergy = countEnergyCursedSpirit();
        if (SoccererEnergy >= CursedSpiritEnergy){
            kickallCursedSpirit();
            delete listofSoccerer,listofCursedSpirit;
            listofSoccerer = listofCursedSpirit = nullptr;
        }
        else{
            kickallSoccerer();
            delete listofSoccerer,listofCursedSpirit;
            listofSoccerer = listofCursedSpirit = nullptr;
        }
        while(sizeCusInQueue != 0 && sizeCusInDesk != MAXSIZE){
            invitefromQueue();
        }//TODO:cho khách từ hàng chờ lên bàn ăn.
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
bool imp_res::checkDuplicate(std::string name) {
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
        CustomerTimeTail = newTimeline;
        CustomerTimeHead = newTimeline;
    }//TODO:nếu là người đầu tiên thì lưu vào đầu timeLine
    else{
        CustomerTimeTail->next = newTimeline;
        CustomerTimeTail = CustomerTimeTail->next;
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
Restaurant::customer*imp_res::findKickingCustomer() {
    customer*run = customerX;
    customerTime*findfirstCusDesk = CustomerTimeHead;
    while(findfirstCusDesk->inDesk != true)findfirstCusDesk = findfirstCusDesk->next;
    do
    {
        if (run->name == findfirstCusDesk->data->name)
        {
            findfirstCusDesk = nullptr;
            delete findfirstCusDesk;
            return run;
        }
        run = run->next;
    }while(run != customerX);
    return nullptr;
}
void imp_res::kickCustomer(Restaurant::customer *kickingCus) {
    sizeCusInDesk--;
    if(sizeCusInDesk != 0){
        customer*nextCustomer = kickingCus->next;
        customer*preCustomer = kickingCus->prev;
        if(kickingCus->energy > 0)customerX = nextCustomer;
        else customerX = preCustomer;
        preCustomer->next = nextCustomer;
        nextCustomer->prev = preCustomer;
        kickingCus->next = kickingCus->prev = nullptr;
        kickingCus = nullptr;
        preCustomer = nullptr;
        nextCustomer = nullptr;
        delete kickingCus;
        delete preCustomer, nextCustomer;
    }//TODO:TH nếu số lượng khách sau khi đá != 0
    else{
        customerX = nullptr;
    }//TODO:TH nếu số lượng khách sau khi đá == 0
}
void imp_res::popfirstCusDesk() {
    if (CustomerTimeHead->inDesk == true){
        customerTime*temp = CustomerTimeHead;
        if (temp->next == nullptr){
            delete CustomerTimeHead,CustomerTimeTail,temp;
            CustomerTimeHead = CustomerTimeTail = nullptr;
        }
        else{
            CustomerTimeHead = CustomerTimeHead->next;
            temp->next = nullptr;
            delete temp;
        }
    }
    else{
        customerTime*temp = CustomerTimeHead;
        if(temp->next != nullptr){
            customerTime*run = CustomerTimeHead->next;
            while(run->inDesk != true){
                temp = run;
                run = run->next;
            }
            if(run == CustomerTimeTail)CustomerTimeTail = temp;
            temp->next = run->next;
            run->next = nullptr;
            delete run;
        }
        else{
            delete CustomerTimeHead, CustomerTimeTail;
            CustomerTimeHead = CustomerTimeTail = nullptr;
        }

    }
}
void imp_res::invitefromQueue() {
    sizeCusInQueue--;
    string name = customerQueueHead->name;
    int energy = customerQueueHead->energy;
    if (sizeCusInQueue != 0) {
        customer *temp = customerQueueHead;
        customerQueueHead = customerQueueHead->next;
        temp->next = nullptr;
        temp = nullptr;
        delete temp;
    } else customerQueueHead = customerQueueTail = nullptr;

    //TODO:Add các vị khách mới vào
    customer *newCus = new customer(name, energy, nullptr, nullptr);
    changeStatus(name);
    if (sizeCusInDesk == 0) {
        customerX = newCus;
        newCus->prev = customerX;
        newCus->next = customerX;
        sizeCusInDesk++;
        return;
    }//TODO:Nếu là vị khách đầu tiên thì prev với next bằng chính nó và customerX sẽ cập nhật
    else if (sizeCusInDesk >= MAXSIZE / 2) {
        customerX = findHighRES(newCus);//Đi tìm vị trí có RES cao nhất và gán nó cho customerX
        if (newCus->energy - customerX->energy >= 0)
            addLeft(newCus);//nếu hiệu energy của newCus và customerX dương thì add left, không thì ngược lại
        else addRight(newCus);
        sizeCusInDesk++;
        customerX = newCus;
        return;
    }//TODO:Khi số lượng >= MAXSIZE/2 thì phải tìm vị trí HighRES rồi add
    else {
        if (newCus->energy >= customerX->energy)addLeft(newCus);//TODO:Nếu energy lớn hơn customerX thì add chiều kim đồng hồ, không thì ngược lại
        else addRight(newCus);
        sizeCusInDesk++;
        customerX = newCus;
        return;
    }//TODO:Trường hợp tổng quát
}
void imp_res::changeStatus(string name) {
    customerTime*run = CustomerTimeHead;
    while(run->data->name != name)run = run->next;
    run->inDesk = true;
    run = nullptr;
}

//DOMAIN EXPANSION
int imp_res::countEnergySoccerer(){
    int result = 0;
    customerTime*run = CustomerTimeHead;
    while(run != nullptr){
        if (run->data->energy > 0)
        {
            result += run->data->energy;
            appendSoccerer(run);
        }
        run = run->next;
    }
    return result;
}
int imp_res::countEnergyCursedSpirit(){
    int result = 0;
    customerTime*run = CustomerTimeHead;
    while(run != nullptr){
        if (run->data->energy < 0)
        {
            result += run->data->energy;
            appendCursedSpirit(run);
        }
        run = run->next;
    }
    result = abs(result);
    return result;
}
void imp_res::appendSoccerer(imp_res::customerTime *Soccerer){
    customerTime*clone = new customerTime(Soccerer->data,Soccerer->inDesk);
    if(listofSoccerer == nullptr){
        listofSoccerer = clone;
    }//TODO: Nếu là phần tử đầu tiên thì gán listofSoccere bằng Soccerer luôn
    else{
        clone->next = listofSoccerer;
        listofSoccerer = clone;
    }//TODO: Không thì add vào đầu
}
void imp_res::appendCursedSpirit(imp_res::customerTime *CursedSpirit) {
    customerTime*clone = new customerTime(CursedSpirit->data,CursedSpirit->inDesk);
    if(listofCursedSpirit == nullptr){
        listofCursedSpirit = clone;
    }//TODO: Nếu là phần tử đầu tiên thì gán listofCursedSpirit bằng CursedSpirit luôn
    else{
        clone->next = listofCursedSpirit;
        listofCursedSpirit = clone;
    }//TODO: Không thì add vào đầu
}
void imp_res::kickallSoccerer() {
    customerTime*run = listofSoccerer;
    while(run != nullptr){
        if (run->inDesk == true){
            run->data->print();
            kickCustomer(findinDesk(run->data->name));
            popTimeline(run->data->name);
        }//TODO:Nếu vị khách đó đang trên bàn
        else{
            run->data->print();
            kickinQueue(run->data->name);
            popTimeline(run->data->name);
        }//TODO:Nếu vị khách đó đang trong hàng đợi
        run = run->next;
    }
}
void imp_res::kickallCursedSpirit() {
    customerTime*run = listofCursedSpirit;
    while(run != nullptr){
        if (run->inDesk == true){
            run->data->print();
            kickCustomer(findinDesk(run->data->name));
            popTimeline(run->data->name);
        }//TODO:Nếu vị khách đó đang trên bàn
        else{
            run->data->print();
            kickinQueue(run->data->name);
            popTimeline(run->data->name);
        }//TODO:Nếu vị khách đó đang trong hàng đợi
        run = run->next;
    }
}
Restaurant::customer*imp_res::findinDesk(std::string name) {
    customer*run = customerX;
    while(run->name != name)run = run->next;
    return run;
}
void imp_res::popTimeline(string name) {
    if (CustomerTimeHead == CustomerTimeTail){
        delete CustomerTimeHead,CustomerTimeTail;
        CustomerTimeHead = CustomerTimeTail = nullptr;
    }
    else{
        if (CustomerTimeHead->data->name == name){
            customerTime*temp = CustomerTimeHead;
            CustomerTimeHead = CustomerTimeHead->next;
            temp->next = nullptr;
            delete temp;
        }
        else{
            customerTime*temp = CustomerTimeHead;
            customerTime*run = temp->next;
            while(run->data->name != name){
                temp = run;
                run = run->next;
            }
            if(run == CustomerTimeTail)CustomerTimeTail = temp;
            temp->next = run->next;
            run->next = nullptr;
            delete run;
        }
    }
}
void imp_res::kickinQueue(string name) {
    if(customerQueueHead == customerQueueTail){
        delete customerQueueHead,customerQueueTail;
        customerQueueHead = customerQueueTail;
    }
    else{
        if(customerQueueHead->name == name){
            customer*temp = customerQueueHead;
            customerQueueHead = customerQueueHead->next;
            temp->next = nullptr;
            delete temp;
        }else{
            customer*temp = customerQueueHead;
            customer*run = temp->next;
            while(run->name != name){
                temp = run;
                run = run->next;
            }
            if(run == customerQueueTail)customerQueueTail = temp;
            temp->next = run->next;
            run->next = nullptr;
            delete run;
        }
    }
    sizeCusInQueue--;
}