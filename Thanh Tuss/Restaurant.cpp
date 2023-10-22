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
            ~customerTime(){delete data;COUNTDELETE++;}//TODO:deconstructor class customerTime
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
        ~imp_res(){
            customerTime*run = CustomerTimeHead;
            while(CustomerTimeHead != nullptr){
                CustomerTimeHead = CustomerTimeHead->next;
                delete run;
                COUNTDELETE++;
                run = CustomerTimeHead;
            }
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
    //TODO:Hàm dành cho REVERSAL
    public:
        void reverseSoccerer();//TODO:Đảo chiều những chú thuật sư;
        void reverseEvilSpirit();//TODO:Đảo chiều những oán linh;
        void Swap(customer*&head, customer*&tail);//TODO:Hàm swap
    //TODO:Hàm dành cho DOMAIN EXPASION
    public:
        void kickSoccerer();//TODO:kick hết chú thuật sư
        void kickEvilSpirit();//TODO: kick hết oán linh
        void kickinQueue(customerTime*kickingCus);//TODO: kick trong hàng chờ
    //TODO:Hàm dành cho PURPLE
    public:
        customer* findHighestABS();//TODO:tìm chú thuật sư có giá trị tuyệt đối Energy cao nhất.
        void ShellSort(customer*tailSort);//TODO:Shell sort.
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
            COUNTDELETE--;

            //TODO:check xem khách có bị đưa vào hàng chờ không ?
            if (sizeCusInDesk == MAXSIZE){
                appendQueue(newCus);
                customerTime*newTimeline = new customerTime(newCus,false);
                COUNTDELETE--;
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
                COUNTDELETE--;
                appendTimeline(newTimeline);
                return;
            }//TODO:Nếu là vị khách đầu tiên thì prev với next bằng chính nó và customerX sẽ cập nhật
            else if (sizeCusInDesk >= MAXSIZE/2){
                customerX = findHighRES(newCus);//Đi tìm vị trí có RES cao nhất và gán nó cho customerX
                if (newCus->energy - customerX->energy >= 0)addLeft(newCus);//nếu hiệu energy của newCus và customerX dương thì add left, không thì ngược lại
                else addRight(newCus);
                sizeCusInDesk++;
                customerTime *newTimeLine = new customerTime(newCus,true);
                COUNTDELETE--;
                appendTimeline(newTimeLine);
                customerX = newCus;
                return;
            }//TODO:Khi số lượng >= MAXSIZE/2 thì phải tìm vị trí HighRES rồi add
            else{
                if (newCus->energy >= customerX->energy)addLeft(newCus);//TODO:Nếu energy lớn hơn customerX thì add chiều kim đồng hồ, không thì ngược lại
                else addRight(newCus);
                sizeCusInDesk++;
                customerTime*newTimeline = new customerTime(newCus,true);
                COUNTDELETE--;
                appendTimeline(newTimeline);
                customerX = newCus;
                return;
            }//TODO:Trường hợp tổng quát
        }//DONE.
        void BLUE(int num)
        {
            if (sizeCusInDesk == 0)return;//TODO:nếu không có khách trên bàn thì không xóa.
            if (num > sizeCusInDesk)num=sizeCusInDesk;//TODO:Chặn trường hợp num chạy quá số lượng khách trên bàn ăn.
            for(int i = 0; i < num; i++)
            {
                customerTime*deleteCus = findKickingCustomer();
                kickCustomer(deleteCus);
            }//TODO:Xóa khách num lần và xóa luôn thứ tự trong timeLine
            invitefromQueue();//TODO:Mời khách trong hàng chờ vào bàn
            return;
        }//DONE.
        void PURPLE()
        {

        }
        void REVERSAL()
        {
            if (sizeCusInDesk <= 1)return;//TODO:Không có ai trên bàn ăn thì không đảo.
            reverseEvilSpirit();//TODO:Hoán đổi oán linh trước
            reverseSoccerer();//TODO:Hoán đổi chú thuật sư sau
        }//DONE.
        void UNLIMITED_VOID(){
            if(sizeCusInDesk < 4)return;//TODO:Không đáp ứng đủ điều kiện để làm.
            int min = INT_MAX;//TODO:Biến để so sánh sum của dãy
            customer*head = nullptr, *tail = nullptr;
            customer*countUp = customerX;
            for(int i = 0; i < sizeCusInDesk; i++){
                int sum = 0;
                //TODO:countUP sẽ coi là cái head, run sẽ coi là cái tail
                customer*run = countUp;
                int j = 0;//TODO:Dùng để đếm số lượng phần tử trong dãy con
                do{
                    //TODO:Cho run chạy xung quanh cái bàn ăn rồi tính tổng của các energy mà run chạy qua
                    sum += run->energy;
                    if (j >= 3 && sum <= min){
                        min = sum;
                        head = countUp;
                        tail = run;
                    }
                    //TODO:Nếu mà số lượng phần tử trong dãy con mà lớn hơn hoặc bằng 3 mà tổng lại nhỏ hơn min đang có thì thay đổi head và tail
                    run = run->next;
                    j++;
                }while (run != countUp);//TODO:Điều kiện là run chỉ chạy tới cái "đầu" aka countUp;
                countUp = countUp->next;
            }//TODO:Đi tìm dãy con tổng nhỏ nhất
            customer*run = head;//TODO:Iterator dùng để đi qua các khách hàng trong dãy con mình tìm được
            customer*energyMin = head;//TODO:Biến dùng để lưu khách hàng có energy nhỏ nhất trong dãy con
            int headtoMin = 0;//TODO:Biến để xíu xài cho in(đếm từ vị trí đầu dãy tới energyMin nhỏ nhất mình cần tìm)
            int headtoTail = 0;//TODO:Biến để xíu xài cho in(đếm từ vị trí đầu dãy tới tail của dãy)
            do{
                if (energyMin->energy > run->energy){
                    energyMin = run;
                    headtoMin = headtoTail;
                }//TODO:Nếu tìm ra được ai đó nhỏ hơn thì cập nhật lại energyMin và biến headtoMin
                headtoTail++;
                run = run->next;
            }while(run != tail->next);//TODO:Đi tìm energy nhỏ nhất trong dãy con.
            customer*print = energyMin;//TODO:Bắt đầu in từ energyMin tới tail của dãy con
            for (int i = headtoMin; i < headtoTail; i++){
                print->print();
                print = print->next;
            }
            print = head;//TODO:Rồi sau đó bắt đầu in từ đầu cho tới trước energyMin;
            for(int i = 0; i < headtoMin; i++){
                print->print();
                print = print->next;
            }
            print = head = tail = run = energyMin = countUp = nullptr;
        }//DONE
        void DOMAIN_EXPANSION()
        {
            if(sizeCusInDesk == 0 && sizeCusInQueue == 0)return;//TODO:Không có ai trong bàn ăn lẫn hàng chờ sao mà kick
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
            }//TODO:Tính energy của cả oán linh và chú thuật sư
            EvilSpiritEnergy = abs(EvilSpiritEnergy);
            run = nullptr;
            if (SoccererEnergy == 0 || EvilSpiritEnergy == 0)return;//TODO:Nếu chỉ có một phe có năng lượng còn phe còn lại không có ai thì không kick ai cả
            if(SoccererEnergy >= EvilSpiritEnergy){
                kickEvilSpirit();
            }//TODO:Kick oán linh nếu chú thuật sư năng lượng manh hơn.
            else{
                kickSoccerer();
            }//TODO:Kick ngược lại đối với trường hợp ngược
            invitefromQueue();//TODO:Mời vào bàn ăn với các vị khách trong hàng chờ(nếu có)
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
    return false;
}
void imp_res::appendQueue(Restaurant::customer *cus){
    if (sizeCusInQueue == 0){
        customerQueueTail = cus;
        customerQueueHead = cus;
    }//TODO:nếu là người đầu tiên thì cho vào đầu hàng chờ
    else{
        customerQueueTail->next = cus;
        cus->prev = customerQueueTail;
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
    for(int i = 0; i < sizeCusInDesk; i++){
        int absSub = abs(cus->energy - run->energy);
        if (absSub > max)
        {
            max = absSub;
            result = run;
        }
        run = run->next;
    }//TODO:Chạy từ đầu cho đến hết bàn ăn coi ai có RES cao nhất thì trả về địa chỉ đó.
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
imp_res::customerTime*imp_res::findKickingCustomer() {
    //TODO:Vì kick từ người đầu tiên vào bàn ăn nên đi tìm từ đầu timeline xuống.
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
            delete kickingCus;
            COUNTDELETE++;
            CustomerTimeHead = CustomerTimeHead->next;
            CustomerTimeHead->pre = nullptr;
        }//TODO:Cũng là bàn ăn kick hết nhưng Queue còn người.
        else{
            delete CustomerTimeHead;
            COUNTDELETE++;
            CustomerTimeHead = CustomerTimeTail = nullptr;
        }//TODO:Ngược lại cái ở trên
    }//TODO:Trường hợp bàn ăn kick hết
    else{
        //Nếu khách bị xóa là chú thuật sư thì customerX là người thuận chiều kim đồng hồ, không thì ngược lại
        if(kickingCus->data->energy > 0)customerX=kickingCus->data->next;
        else customerX=kickingCus->data->prev;

        //Gán các prev next của khách ở trước và sau với nhau của vị khách đang xóa.
        kickingCus->data->prev->next = kickingCus->data->next;
        kickingCus->data->next->prev = kickingCus->data->prev;
        if(kickingCus == CustomerTimeHead) {
            CustomerTimeHead = CustomerTimeHead->next;
            CustomerTimeHead->pre = nullptr;
        }//TODO:Nếu khách hàng định kick đầu TimeLine thì dịch đầu TimeLine qua bên phải.
        else{
            kickingCus->pre->next = kickingCus->next;
            if(kickingCus == CustomerTimeTail){
                CustomerTimeTail = kickingCus->pre;
                CustomerTimeTail->next = nullptr;
            }//TODO:Nếu khách cần xóa cuối là cuối TimeLine thì dịch cuối TimeLine ngược về.
            else{
                kickingCus->next->pre = kickingCus->pre;
            }//TODO:Trường hợp tổng quát
        }//TODO:Không thì...
        delete kickingCus;
        COUNTDELETE++;
    }
}
void imp_res::invitefromQueue() {
    //TODO:Điều kiện dừng là khách trong hàng chờ = 0 hoặc khách trong bàn ăn bằng MAXSIZE
    while(sizeCusInQueue != 0 && sizeCusInDesk != MAXSIZE){
        customerTime*temp = CustomerTimeHead;
        for(int i = 0;i < sizeCusInQueue + sizeCusInDesk; i++){
            if (temp->data == customerQueueHead){
                break;
            }
            else{
                temp = temp->next;
            }//TODO:Đi tìm đầu danh sách thời gian để tìm ra người đứng đầu trong hàng chờ.
        }
        if(temp->data == customerQueueTail){
            customerQueueHead = customerQueueTail = nullptr;
        }//TODO:Nếu khách hàng đó cuối hàng chờ thì cho cái đầu và cuối danh sách hàng chờ bằng null
        else{
            customerQueueHead = customerQueueHead->next;
            customerQueueHead->prev = nullptr;
        }//TODO:Không thì đầu danh sách = người kế tiếp
        temp->inDesk = true;//TODO:Đổi trạng thái từ là người trong hàng thành người trên bàn ăn
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

//REVERSAL
void imp_res::reverseSoccerer() {
    customer*head = nullptr;
    customer*tail = nullptr;
    customer*preHead = nullptr;//TODO:Dùng để giữ khách hàng trước đó của Head
    customer*nextTail = nullptr;//TODO:Dùng để giữ khách hàng sau đó của Tail
    head = customerX;
    tail = head->next;
    do{
        int count = 0;
        while(head->energy < 0){
            head = head->prev;
            count++;
            if (count == sizeCusInDesk || head == tail)return;
        }//TODO:Đi tìm chú thuật sư
        preHead = head->prev;
        while(tail->energy < 0){
            tail = tail->next;
            if (tail == head)return;
        }//TODO:Đi tìm chú thuật sư tiếp theo
        nextTail = tail->next;
        Swap(head,tail);//TODO:SWAP
        if (preHead == tail && nextTail == head)return;//TODO:Check điều kiện dừng vòng lặp
        head = preHead;
        tail = nextTail;
    }while (head != tail);//TODO:Head đi ngược chiều đồng hồ còn tail đi thuận nếu gặp nhau thì end vòng lặp
    head = tail = preHead = nextTail = nullptr;
}
void imp_res::reverseEvilSpirit() {
    customer*head = nullptr;
    customer*tail = nullptr;
    customer*preHead = nullptr;//TODO:Dùng để giữ khách hàng trước đó của Head
    customer*nextTail = nullptr;//TODO:Dùng để giữ khách hàng sau đó của Tail
    head = customerX;
    tail = head->next;
    do{
        int count = 0;
        while(head->energy > 0){
            head = head->prev;
            count++;
            if (count == sizeCusInDesk || head == tail)return;
        }//TODO:Đi tìm oán linh
        preHead = head->prev;
        while(tail->energy > 0){
            tail = tail->next;
            if (tail == head)return;
        }//TODO:Đi tìm oán linh
        nextTail = tail->next;
        Swap(head,tail);//TODO:SWAP
        if (preHead == tail && nextTail == head)return;//TODO:Check điều kiện dừng vòng lặp
        head = preHead;
        tail = nextTail;
    }while (head != tail);//TODO:Head đi ngược chiều đồng hồ còn tail đi thuận nếu gặp nhau thì end vòng lặp
    head = tail = preHead = nextTail = nullptr;
}
void imp_res::Swap(Restaurant::customer *&head, Restaurant::customer *&tail) {
    //Tham khảo từ nguồn: https://www.geeksforgeeks.org/swap-given-nodes-in-a-doubly-linked-list-without-modifying-data/
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
        COUNTDELETE++;
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
        COUNTDELETE++;
    }
}

//PURPLE
Restaurant::customer* imp_res::findHighestABS() {
    int max = 0;
    customerTime *findingCus = CustomerTimeTail;
    customer *result = findingCus->data;
    while (findingCus != nullptr){
        if (findingCus->inDesk == false){
            if (abs(findingCus->data->energy) > max){
                max = abs(findingCus->data->energy);
                result = findingCus->data;
            }
        }
        findingCus = findingCus->pre;
    }
    findingCus = nullptr;
    return result;
}
void imp_res::ShellSort(Restaurant::customer *tailSort) {
    customer*count = customerQueueHead;
    int size = 0;
    while(count != tailSort){
        size++;
        count = count->next;
    }

    int N = 0;
    for (int gap = size/2; gap > 0; gap /= 2){

    }
}