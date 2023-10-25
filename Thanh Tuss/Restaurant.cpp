#include "main.h"

class imp_res : public Restaurant
{
    private:
        customer*customerX; //Lưu khách mới được thay đổi gần đây
        int sizeCusInDesk; //Biến đếm số lượng khách ở bàn

        customer*customerQueueTail; //Lưu những vị Khách ở hàng đợi để làm iterator
        customer*customerQueueHead;//Lưu người đầu tiên trong hàng đợi để dễ dàng làm việc
        int sizeCusInQueue;//Biến đếm số lượng khách ở trong hàng đợi

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
        };//Class lưu timeline của các vị khách cho vào bàn ăn
    public:
        imp_res()
        {
            customerX = nullptr;
            sizeCusInDesk = 0;

            customerQueueTail = customerQueueHead = nullptr;
            sizeCusInQueue = 0;

            CustomerTimeHead = CustomerTimeTail = nullptr;
        }
        ~imp_res(){
            customerTime*run = CustomerTimeHead;
            while(CustomerTimeHead != nullptr){
                CustomerTimeHead = CustomerTimeHead->next;
                delete run;
                run = CustomerTimeHead;
            }
        }
    private:
        customerTime *CustomerTimeTail;//Lưu thứ tự các vị khách được cho vào bàn ăn
        customerTime *CustomerTimeHead;//Lưu người đầu tiên trong timeline vào bàn ăn
    //Hàm dành cho RED
    public:
        bool checkDuplicate(string);//check "thiên thượng thiên hạ, duy chỉ độc tôn", nếu có trùng trả về true không thì ngược lại
        void appendQueue(customer*);//cho vị khách vào hàng chờ
        void appendTimeline(customerTime *);//cho vị khách vào time line mỗi khi add
        customer *findHighRES(customer *);//Tìm vị trí có RES cao nhất để trả về
        void addLeft(customer*);//thêm vị khách theo chiều thuận kim đồng hồ của customerX
        void addRight(customer*);//thêm vị khách theo chiều ngược kim đồng hồ của customerX
    //Hàm dành cho BLUE
    public:
        customerTime*findKickingCustomer();//hàm trả về customer cần bị kick trong bàn tròn.
        void kickCustomer(customerTime*);//hàm đuổi khách đã được xác định
        void invitefromQueue();//Mời những vị khách trong hàng chờ vào nhà hàng và xóa vị khách đó ra khỏi hàng chờ
        void addinDesk(customer*);//Add lại vào trong nhà hàng
    //Hàm dành cho REVERSAL
    public:
        void Reversal(int,int);//Dùng để đảo
        void Swap(customer*&, customer*&);//Hàm swap
        int countCurseSpirit();//Đếm số lượng oán linh
        int countSoccerer();//Đếm số lượng chú thuật sư
    //Hàm dành cho DOMAIN EXPASION
    public:
        void kickSoccerer();//kick hết chú thuật sư
        void kickEvilSpirit();//kick hết oán linh
        void kickinQueue(customerTime*);//kick trong hàng chờ
    //Hàm dành cho PURPLE
    public:
        customer* findHighestABS(int &);//tìm chú thuật sư có giá trị tuyệt đối Energy cao nhất.
        void shellSort(customer*&,int);//Shell sort
        customer*findAt(customer*,int);//đi tìm khách hàng tại index nào đó để tiện sort
        int insertionSort(customer*&, int, int);//insertion sort
        bool stableCheck(customer*,customer*);//check stable để tránh mất thứ tự vào của 2 phần tử ban đầu
        void swapQueue(customer*&,customer*&,customer*&);//Swap dành cho hàng chờ khách
    public:
        void RED(string name, int energy)
        {
            if (energy == 0)return;//Đuổi khách khi khách không phải oán linh hoặc thuật sư
            else if (sizeCusInDesk >= MAXSIZE && sizeCusInQueue >= MAXSIZE)return;//Đuổi khách khi quá tải cả ở bàn và trong hàng đợi
            else{
                if (checkDuplicate(name) == true)return;
            }//Đuổi khách khi tên trùng với ai đó ở bàn ăn hoặc hàng đợi

            //Sau khi check xem có đuổi khách hay không thì tiếp tục check xem khách được vào bàn hay vào hàng đợi
            customer* newCus = new customer(name,energy, nullptr, nullptr);//TODO:tạo một customer là khách mới vào

            //check xem khách có bị đưa vào hàng chờ không ?
            if (sizeCusInDesk == MAXSIZE){
                appendQueue(newCus);
                customerTime*newTimeline = new customerTime(newCus,false);
                appendTimeline(newTimeline);
                return;
            }//nếu trên có số lượng vượt ra khỏi qui định MAXSIZE thì add vào hàng đợi

                //nếu không vào hàng chờ thì khách sẽ được đưa vào bàn là link list tròn đôi
            else if (sizeCusInDesk == 0){
                customerX = newCus;
                newCus->prev = customerX;
                newCus->next = customerX;
                sizeCusInDesk++;
                customerTime*newTimeline = new customerTime(customerX,true);
                appendTimeline(newTimeline);
                return;
            }//Nếu là vị khách đầu tiên thì prev với next bằng chính nó và customerX sẽ cập nhật
            else if (sizeCusInDesk >= MAXSIZE/2){
                customerX = findHighRES(newCus);//Đi tìm vị trí có RES cao nhất và gán nó cho customerX
                if (newCus->energy - customerX->energy >= 0)addLeft(newCus);//nếu hiệu energy của newCus và customerX dương thì add left, không thì ngược lại
                else addRight(newCus);
                sizeCusInDesk++;
                customerTime *newTimeLine = new customerTime(newCus,true);
                appendTimeline(newTimeLine);
                customerX = newCus;
                return;
            }//Khi số lượng >= MAXSIZE/2 thì phải tìm vị trí HighRES rồi add
            else{
                if (newCus->energy >= customerX->energy)addLeft(newCus);//Nếu energy lớn hơn customerX thì add chiều kim đồng hồ, không thì ngược lại
                else addRight(newCus);
                sizeCusInDesk++;
                customerTime*newTimeline = new customerTime(newCus,true);
                appendTimeline(newTimeline);
                customerX = newCus;
                return;
            }//Trường hợp tổng quát
        }//DONE.
        void BLUE(int num)
        {
            if (sizeCusInDesk == 0)return;//nếu không có khách trên bàn thì không xóa.
            if (num > sizeCusInDesk)num=sizeCusInDesk;//Chặn trường hợp num chạy quá số lượng khách trên bàn ăn.
            for(int i = 0; i < num; i++)
            {
                customerTime*deleteCus = findKickingCustomer();
                kickCustomer(deleteCus);
            }//Xóa khách num lần và xóa luôn thứ tự trong timeLine
            invitefromQueue();//Mời khách trong hàng chờ vào bàn
            return;
        }//DONE.
        void PURPLE()
        {
            int size = 0;
            customer*tail =findHighestABS(size);//Tìm energy lớn nhất và coi nó là tail.
            if (tail == nullptr)return;//Nếu không có ai thì không cần swap làm gì cho cực
            shellSort(customerQueueHead,size);//Nếu có thì swap
        }//DONE
        void REVERSAL()
        {
            if (sizeCusInDesk <= 1)return;//Không có ai trên bàn ăn thì không đảo.
            int countS = countSoccerer(), countCS = countCurseSpirit();//Đếm số lượng của chú linh và chú thuật sư
            Reversal(countS, countCS);//Đảo tất cả
        }//DONE.
        void UNLIMITED_VOID(){
            if(sizeCusInDesk <= 3) return;

            int MinEnergy = 2147483647;
            customer* head = nullptr;
            int sizeMAX = 0;
            customer* Tempi = customerX;
            for(int i = 0; i < sizeCusInDesk; i++){
                int totalEnergy = 0;
                customer* Tempj = Tempi;
                for(int j = 0; j < sizeCusInDesk; j++){
                    totalEnergy +=  Tempj->energy;
                    if(j >= 3 && (MinEnergy > totalEnergy || MinEnergy == totalEnergy  && j + 1 >= sizeMAX)){
                        head = Tempi;
                        sizeMAX = j + 1;
                        MinEnergy = totalEnergy;
                    }
                    Tempj = Tempj->next;
                }
                Tempi = Tempi->next;
            }//Đi tìm mảng con với tổng energy nhỏ nhất

            customer* min = head;
            customer* temp = head;
            int sizeHeadToMin = 1;
            for(int i = 0; i < sizeMAX; i++)
            {
                if(min->energy > temp->energy)
                {
                    min = temp;
                    sizeHeadToMin = i + 1;
                }
                temp = temp->next;
            }//Đi tìm khách hàng có energy bé nhất trong dãy con vừa tìm.
            customer*print = min;
            for(int i = sizeHeadToMin; i <= sizeMAX; i++){
                print->print();
                print = print->next;
            }//In từ khách hàng bé nhất tới tail của dãy
            print = head;
            for(int i = 0; i < sizeHeadToMin - 1; i++){
                print->print();
                print = print->next;
            }//Rồi tiếp tục in từ đầu tới trước khách hàng bé nhất nếu còn
        }//DONE
        void DOMAIN_EXPANSION()
        {
            if(sizeCusInDesk == 0 && sizeCusInQueue == 0)return;//Không có ai trong bàn ăn lẫn hàng chờ sao mà kick
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
            }//Tính energy của cả oán linh và chú thuật sư
            if(SoccererEnergy >= abs(EvilSpiritEnergy)){
                kickEvilSpirit();
            }//Kick oán linh nếu chú thuật sư năng lượng manh hơn.
            else{
                kickSoccerer();
            }//Kick ngược lại đối với trường hợp ngược
            invitefromQueue();//Mời vào bàn ăn với các vị khách trong hàng chờ(nếu có)
        }//DONE.
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
            }//nếu num == 0 thì in hết tất cả trong hàng chờ
            else if (num > 0){
                customer*print = customerX;
                if(print == nullptr)return;
                for(int i = 0; i < sizeCusInDesk; i++)
                {
                    print->print();
                    print = print->next;
                }
                return;
            }//in thuận chiều kim đồng hồ nếu mà num dương
            else if (num < 0){
                customer*print = customerX;
                if(print == nullptr)return;
                for(int i = 0; i < sizeCusInDesk; i++)
                {
                    print->print();
                    print = print->prev;
                }
                return;
            }//in ngược chiều kim đồng hồ nếu mà num âm
        }//DONE.
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
        }while(checkTable != customerX); //vì trên bàn là circle double link list nên chỉ chạy tới thằng customerX để tránh bị vòng lặp vô tận
    }//nếu số lượng khách ở bàn == 0 thì bỏ qua ko cần check

    if (sizeCusInQueue != 0){
        while(checkQueue != nullptr){
            if (checkQueue->name == name)
            {
                return true;
            }
            checkQueue = checkQueue->next;
        }
    }//nếu số lượng khách ở hàng đợi == 0 thì bỏ qua mà return false luôn
    return false;
}
void imp_res::appendQueue(Restaurant::customer *cus){
    if (sizeCusInQueue == 0){
        customerQueueTail = cus;
        customerQueueHead = cus;
    }//nếu là người đầu tiên thì cho vào đầu hàng chờ
    else{
        customerQueueTail->next = cus;
        cus->prev = customerQueueTail;
        customerQueueTail = cus;
    }//bằng không thì add ra sau cùng hàng chờ
    sizeCusInQueue++;
}
void imp_res::appendTimeline(imp_res::customerTime *newTimeline){
    if (CustomerTimeTail == nullptr){
        CustomerTimeHead = CustomerTimeTail = newTimeline;
    }//nếu là người đầu tiên thì lưu vào đầu timeLine
    else{
        CustomerTimeTail->next = newTimeline;
        newTimeline->pre = CustomerTimeTail;
        CustomerTimeTail = newTimeline;
    }//Không thì add sau liên kết
}
Restaurant::customer* imp_res::findHighRES(customer *cus)
{
    customer*run = customerX;
    customer*result = run;
    int max = -1;
    for(int i = 0; i < sizeCusInDesk; i++){
        int absSub = abs(cus->energy - run->energy);
        if (absSub > max)
        {
            max = absSub;
            result = run;
        }
        run = run->next;
    }//Chạy từ đầu cho đến hết bàn ăn coi ai có RES cao nhất thì trả về địa chỉ đó.
    run = nullptr;
    return result;
}
void imp_res::addLeft(Restaurant::customer *cus) {
    /*Giả sử add AB vào bên trái AC trong AC->AD thì nó sẽ ra: AC->AB->AD*/
    customer*temp = customerX->next;
    temp->prev = cus;
    cus->next = temp;
    customerX->next = cus;
    cus->prev = customerX;
    customerX = cus;
    temp = nullptr;
}
void imp_res::addRight(Restaurant::customer *cus) {
    /*Giả sử add AB vào bên phải AC trong AE->AC thì nó sẽ ra: AE->AB->AC*/
    customer*temp = customerX->prev;
    temp->next = cus;
    cus->prev = temp;
    customerX->prev = cus;
    cus->next = customerX;
    customerX = cus;
    temp = nullptr;
}

//BLUE
imp_res::customerTime*imp_res::findKickingCustomer(){
    //Vì kick từ người đầu tiên vào bàn ăn nên đi tìm từ đầu timeline xuống.
    customerTime*run = CustomerTimeHead;
    while(run != nullptr){
        if(run->inDesk){
            return run;
        }
        run = run->next;
    }
    return nullptr;
}
void imp_res::kickCustomer(imp_res::customerTime *kickingCus){
    sizeCusInDesk--;
    if(sizeCusInDesk == 0){
        if(sizeCusInQueue == 0){
            CustomerTimeHead = CustomerTimeTail = nullptr;
        }//TH trong bàn ăn lẫn hàng chờ không còn ai
        else{
            if (kickingCus == CustomerTimeHead){
                CustomerTimeHead = CustomerTimeHead->next;
                CustomerTimeHead->pre = nullptr;
            }
            else if (kickingCus == CustomerTimeTail){
                CustomerTimeTail = CustomerTimeTail->pre;
                CustomerTimeTail->next = nullptr;
            }
            else{
                kickingCus->pre->next = kickingCus->next;
                kickingCus->next->pre = kickingCus->pre;
            }
        }//TH trong hàng vẫn còn người
    }//TH xóa hết trên bàn ăn
    else{
        if(kickingCus->data->energy > 0)customerX=kickingCus->data->next;
        else customerX=kickingCus->data->prev;
        kickingCus->data->next->prev = kickingCus->data->prev;
        kickingCus->data->prev->next = kickingCus->data->next;

        if (kickingCus == CustomerTimeHead){
            CustomerTimeHead = CustomerTimeHead->next;
            CustomerTimeHead->pre = nullptr;
        }
        else if (kickingCus == CustomerTimeTail){
            CustomerTimeTail = CustomerTimeTail->pre;
            CustomerTimeTail->next = nullptr;
        }
        else{
            kickingCus->pre->next = kickingCus->next;
            kickingCus->next->pre = kickingCus->pre;
        }
    }//TH trong bàn ăn còn người
    delete kickingCus;
}
void imp_res::invitefromQueue(){
    //Điều kiện dừng là khách trong hàng chờ = 0 hoặc khách trong bàn ăn bằng MAXSIZE
    while(sizeCusInQueue != 0 && sizeCusInDesk != MAXSIZE){
        customerTime*temp = CustomerTimeHead;
        for(int i = 0;i < sizeCusInQueue + sizeCusInDesk; i++){
            if (temp->data == customerQueueHead){
                break;
            }
            else{
                temp = temp->next;
            }//Đi tìm đầu danh sách thời gian để tìm ra người đứng đầu trong hàng chờ.
        }
        if(temp->data == customerQueueTail){
            customerQueueHead = customerQueueTail = nullptr;
        }//Nếu khách hàng đó cuối hàng chờ thì cho cái đầu và cuối danh sách hàng chờ bằng null
        else{
            customerQueueHead = customerQueueHead->next;
            customerQueueHead->prev = nullptr;
        }//Không thì đầu danh sách = người kế tiếp
        temp->inDesk = true;//Đổi trạng thái từ là người trong hàng thành người trên bàn ăn
        addinDesk(temp->data);
        sizeCusInQueue--;
    }
}
void imp_res::addinDesk(customer*newCus){
    newCus->next = newCus->prev = nullptr;
    if (sizeCusInDesk == 0){
        customerX = newCus;
        newCus->prev = customerX;
        newCus->next = customerX;
        sizeCusInDesk++;
    }//Nếu là vị khách đầu tiên thì prev với next bằng chính nó và customerX sẽ cập nhật
    else if (sizeCusInDesk >= MAXSIZE/2){
        customerX = findHighRES(newCus);//Đi tìm vị trí có RES cao nhất và gán nó cho customerX
        if (newCus->energy - customerX->energy >= 0)addLeft(newCus);//nếu hiệu energy của newCus và customerX dương thì add left, không thì ngược lại
        else addRight(newCus);
        sizeCusInDesk++;
        customerX = newCus;
    }//Khi số lượng >= MAXSIZE/2 thì phải tìm vị trí HighRES rồi add
    else{
        if (newCus->energy >= customerX->energy)addLeft(newCus);//Nếu energy lớn hơn customerX thì add chiều kim đồng hồ, không thì ngược lại
        else addRight(newCus);
        sizeCusInDesk++;
        customerX = newCus;
    }//Trường hợp tổng quát
}

//REVERSAL
int imp_res::countCurseSpirit(){
    customer*run = customerX;
    int count = 0;
    do{
        if (run->energy < 0){
            count++;
        }
        run = run->next;
    }while(run != customerX);//Đếm energy oán linh
    return count;
}
int imp_res::countSoccerer(){
    customer*run = customerX;
    int count = 0;
    do{
        if (run->energy > 0){
            count++;
        }
        run = run->next;
    }while(run != customerX);//Đếm energy thuật sư
    return count;
}
void imp_res::Reversal(int countS, int countCS){
    customer*head = customerX;
    customer*tail = head;
    customer*prehead;
    int headS, headCS, tailS = countS, tailCS = countCS;
    headS = headCS = 0;
    do{
        prehead = head->prev;
        int i = -1;
        if (head->energy > 0){
            do{
                if (tail->energy > 0)i++;//Chỉ cộng khi thấy chú thuật sư
                if (i >= tailS - headS - 1)break;
                else tail = tail->prev;
            }while(i < tailS - headS);
            headS++;
            tailS--;
            Swap(head,tail);
        }
        else{
            do{
                if (tail->energy < 0)i++;//Chỉ cộng khi thấy oán linh
                if (i >= tailCS - headCS - 1)break;
                else tail = tail->prev;
            }while(i < tailCS - headCS);
            headCS++;
            tailCS--;
            Swap(head,tail);
        }
        head = prehead;
        tail = head;
    }while(headS < tailS || headCS < tailCS);//Chạy cho tới khi mà head với cái tail của cả chú thuật sư và oán linh bằng nhau
}
void imp_res::Swap(Restaurant::customer *&head, Restaurant::customer *&tail){
    if (head == tail)return;
    customer*temp;
    temp = head->next;
    head->next = tail->next;
    tail->next = temp;

    head->next->prev = head;
    tail->next->prev = tail;

    temp = head->prev;
    head->prev = tail->prev;
    tail->prev = temp;

    head->prev->next = head;
    tail->prev->next = tail;
}

//DOMAIN_EXPASION
void imp_res::kickSoccerer(){
    customerTime*print = CustomerTimeTail;
    while(print != nullptr){
        if (print->data->energy > 0){
            print->data->print();
        }
        print = print->pre;
    }//In từ thằng cuối lên đầu
    customerTime*run = CustomerTimeHead;
    while(run != nullptr){
        if(run->data->energy > 0){
            if (run->inDesk){
                customerTime*temp = run;
                run = run->next;
                kickCustomer(temp);
            }
            else{
                customerTime*temp = run;
                run = run->next;
                kickinQueue(temp);
            }
        }
        else{
            run = run->next;
        }
    }//In xong xóa từ đầu xuống cuối
}
void imp_res::kickEvilSpirit(){
    customerTime*print = CustomerTimeTail;
    while(print != nullptr){
        if (print->data->energy < 0){
            print->data->print();
        }
        print = print->pre;
    }//In từ cuối lên đầu
    customerTime*run = CustomerTimeHead;
    while(run != nullptr){
        if(run->data->energy < 0){
            if (run->inDesk){
                customerTime*temp = run;
                run = run->next;
                kickCustomer(temp);
            }
            else{
                customerTime*temp = run;
                run = run->next;
                kickinQueue(temp);
            }
        }
        else{
            run = run->next;
        }
    }//In xong xóa từ đầu xuống cuối
}
void imp_res::kickinQueue(imp_res::customerTime *kickingCus){
    sizeCusInQueue--;
    if (sizeCusInQueue == 0){
        if (sizeCusInDesk == 0){
            CustomerTimeHead = CustomerTimeTail = nullptr;
        }//TH cả trong bàn ăn cũng ko còn ai
        else{
            if (kickingCus == CustomerTimeHead){
                CustomerTimeHead = CustomerTimeHead->next;
                CustomerTimeHead->pre = nullptr;
            }
            else if (kickingCus == CustomerTimeTail){
                CustomerTimeTail = CustomerTimeTail->pre;
                CustomerTimeTail->next = nullptr;
            }
            else{
                kickingCus->pre->next = kickingCus->next;
                kickingCus->next->pre = kickingCus->pre;
            }
        }//TH bàn ăn có người
    }//TH trong hàng chờ ko còn ai
    else{
        //Thay đổi thứ tự thời gian trước
        if (kickingCus == CustomerTimeHead){
            CustomerTimeHead = CustomerTimeHead->next;
            CustomerTimeHead->pre = nullptr;
        }
        else if (kickingCus == CustomerTimeTail){
            CustomerTimeTail = CustomerTimeTail->pre;
            CustomerTimeTail->next = nullptr;
        }
        else{
            kickingCus->pre->next = kickingCus->next;
            kickingCus->next->pre = kickingCus->pre;
        }

        //Thay đổi data sau
        if (kickingCus->data == customerQueueHead){
            customerQueueHead = customerQueueHead->next;
            customerQueueHead->prev = nullptr;
        }
        else if (kickingCus->data == customerQueueTail){
            customerQueueTail = customerQueueTail->prev;
            customerQueueTail->next = nullptr;
        }
        else{
            kickingCus->data->next->prev = kickingCus->data->prev;
            kickingCus->data->prev->next = kickingCus->data->next;
        }
    }//Trường hợp trong sảnh chờ vẫn còn người
    delete kickingCus;
}

//PURPLE
Restaurant::customer* imp_res::findHighestABS(int &size){
    int max = 0;
    if (sizeCusInQueue == 0)return nullptr;
    customerTime *findingCus = CustomerTimeTail;
    customer *result = nullptr;
    do{
        if (findingCus->inDesk == false){
            if (abs(findingCus->data->energy) > max){
                result = findingCus->data;
                max = abs(findingCus->data->energy);
            }
        }
        findingCus = findingCus->pre;
    }while(findingCus != nullptr);//Đi tìm người có trị tuyệt đối energy cao nhất trong sảnh chờ
    customer*run = customerQueueHead;
    size++;
    while(run != result){
        size++;
        run = run->next;
    }//Đếm size của danh sách con từ head cho tới vị trí cao nhất đã tìm
    return result;
}
Restaurant::customer* imp_res::findAt(Restaurant::customer *head, int n){
    customer*run = head;
    for(int i = 0; i < n; i++){
        run = run->next;
    }//Đi tìm khách hàng theo index
    return run;
}
void imp_res::shellSort(Restaurant::customer *& list, int size){
    int count = 0;
    for(int i = size / 2; i > 2; i /= 2){
        for(int j = 0; j < i; j++){
            customer*At = findAt(list,j);
            count += insertionSort(At, size - j, i);
        }
    }//Chạy tới trước gap bằng 2 thì shell sort thông thường
    customer*At = findAt(list,0);
    count += insertionSort(At, size, 1);//Insertion nguyên dãy lần cuối dành cho khi gap bằng 2 và 1
    BLUE(count%MAXSIZE);//Đuổi số khách bằng count mod MAXSIZE
}
int imp_res::insertionSort(Restaurant::customer *&list, int size, int increment){
    int swap = 0;//Biến đếm số lần swap
    for(int i = increment; i < size; i+=increment){
        for(int j = i; j >= increment; j -= increment){
            customer*first = findAt(list,j);
            customer*second = findAt(list, j - increment);
            if (abs(first->energy) > abs(second->energy)
            || abs(first->energy) == abs(second->energy) && stableCheck(first,second)){
                if (first == customerQueueHead)customerQueueHead = second;
                else if (second == customerQueueHead)customerQueueHead = first;
                if (first == customerQueueTail)customerQueueTail = second;
                else if (second == customerQueueTail)customerQueueTail = first;
                swapQueue(list,first,second);
                swap++;
            }
            else break;
        }//Chạy từ increment chạy rồi so với cái trước đó nếu thõa điều kiện thì swap
    }//Chạy qua cái node tiếp theo bắt đầu từ thằng incrememnt
    return swap;
}
bool imp_res::stableCheck(Restaurant::customer *first, Restaurant::customer *second){
    customerTime*run = CustomerTimeHead;
    for(int i = 0; i < sizeCusInDesk + sizeCusInQueue; i++){
        if (run->data == first)return true;//Nếu gặp first trước từ head thì sẽ trả true để swap để đúng thứ tự vào nhà hàng
        else if (run->data == second)return false;//Nếu gặp second từ head thì sẽ trả false để không swap
        run = run->next;
    }
    return false;
}
void imp_res::swapQueue(Restaurant::customer *&head, Restaurant::customer *&first, Restaurant::customer *&second){
    //Swap giống swap của reversal nhưng có thay đổi chút để cho phù hợp với doubly linked list
    if (head == first)head = second;
    if (head == second) head = first;

    customer*temp = first->next;
    first->next = second->next;
    second->next = temp;

    if (first->next != nullptr)first->next->prev = first;
    if (second->next != nullptr)second->next->prev = second;

    temp = first->prev;
    first->prev = second->prev;
    second->prev = temp;

    if (first->prev != nullptr)first->prev->next = first;
    if (second->prev != nullptr)second->prev->next = second;
    temp = first;
    first = second;
    second = temp;
}