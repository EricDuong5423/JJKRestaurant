#include "main.h"

class imp_res : public Restaurant
{
    private:
        customer*customerX; // Lưu khách mới được thay đổi gần đây
        int sizeCusInDesk; // Biến đếm số lượng khách ở bàn

        customer*customerQueue; // Lưu những vị Khách ở hàng đợi để làm iterator
        customer*customerFirstQueue;//Lưu người đầu tiên trong hàng đợi để dễ dàng làm việc
        int sizeCusInQueue;// Biến đếm số lượng khách ở trong hàng đợi

    public:
        class customerTime{ //Class lưu lại thứ tự khách được cho vào bàn ăn
            public:
                customer*data;
                customerTime*next;
            public:
            customerTime(customer * data) {
                this->data = new customer(data->name, data->energy, nullptr, nullptr);
                this->next = nullptr;}//constructor class customerTime
        };

    public:
        imp_res()
        {
            customerX = nullptr;
            sizeCusInDesk = 0;

            customerQueue = nullptr;
            customerFirstQueue = nullptr;
            sizeCusInQueue = 0;

            CustomerTime = nullptr;
        }

    public:
        bool checkDuplicate(string name){
            customer*checkTable = customerX;
            customer*checkQueue = customerFirstQueue;
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
            checkTable = nullptr;
            checkQueue = nullptr;
            delete checkTable;
            delete checkQueue;
            return false;
        }//check "thiên thượng thiên hạ, duy chỉ độc tôn", nếu có trùng trả về true không thì ngược lại
        void appendQueue(customer*cus){
            if (sizeCusInQueue == 0){
                customerQueue = cus;
                customerFirstQueue = cus;
            }//nếu là người đầu tiên thì cho vào đầu hàng chờ
            else{
                customerQueue->next = cus;
                customerQueue = cus;
            }//bằng không thì add ra sau cùng hàng chờ
            sizeCusInQueue++;
        }//cho vị khách vào hàng chờ
        void appendTimeline(customerTime * newTimeline){
            if (CustomerTime == nullptr){
                CustomerTime = newTimeline;
                CustomerFirstKick = newTimeline;
            }//nếu là người đầu tiên thì lưu vào đầu timeLine
            else{
                CustomerTime->next = newTimeline;
                CustomerTime = CustomerTime->next;
            }//Không thì add sau liên kết
        }//cho vị khách vào time line mỗi khi add
        customer *findHighRES(customer *cus){
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
        }//Tìm vị trí có RES cao nhất để trả về
        void addLeft(customer*cus){
            customer*temp = customerX->next;
            temp->prev = cus;
            cus->next = temp;
            customerX->next = cus;
            cus->prev = customerX;
            customerX = cus;
            temp = nullptr;
            delete temp;
        }//thêm vị khách theo chiều thuận kim đồng hồ của customerX
        void addRight(customer*cus){
            customer*temp = customerX->prev;
            temp->next = cus;
            cus->prev = temp;
            customerX->prev = cus;
            cus->next = customerX;
            customerX = cus;
            temp = nullptr;
            delete temp;
        }//thêm vị khách theo chiều ngược kim đồng hồ của customerX
    private:
        customerTime *CustomerTime; // Lưu thứ tự các vị khách được cho vào bàn ăn
        customerTime *CustomerFirstKick; //Lưu người đầu tiên trong timeline vào bàn ăn
    public:
        void RED(string name, int energy)
        {
            if (energy == 0)return;//Đuổi khách khi khách không phải oán linh hoặc thuật sư
            else if (sizeCusInDesk >= MAXSIZE && sizeCusInQueue >= MAXSIZE)return;//Đuổi khách khi quá tải cả ở bàn và trong hàng đợi
            else{
                if (checkDuplicate(name) == true)return;
            }//Đuổi khách khi tên trùng với ai đó ở bàn ăn hoặc hàng đợi

            //Sau khi check xem có đuổi khách hay không thì tiếp tục check xem khách được vào bàn hay vào hàng đợi
            customer* newCus = new customer(name,energy, nullptr, nullptr);//tạo một customer là khách mới vào

            //check xem khách có bị đưa vào hàng chờ không ?
            if (sizeCusInDesk == MAXSIZE){
                appendQueue(newCus);
                return;
            }//nếu trên có số lượng vượt ra khỏi qui định MAXSIZE thì add vào hàng đợi

            //nếu không vào hàng chờ thì khách sẽ được đưa vào bàn là link list tròn đôi
            else if (sizeCusInDesk == 0){
                customerX = newCus;
                newCus->prev = customerX;
                newCus->next = customerX;
                sizeCusInDesk++;
                customerTime*newTimeline = new customerTime(customerX);
                appendTimeline(newTimeline);
                return;
            }//Nếu là vị khách đầu tiên thì prev với next bằng chính nó và customerX sẽ cập nhật
            else if (sizeCusInDesk >= MAXSIZE/2.0){
                customerX = findHighRES(newCus);//Đi tìm vị trí có RES cao nhất và gán nó cho customerX
                if (newCus->energy - customerX->energy > 0)addLeft(newCus);//nếu hiệu energy của newCus và customerX dương thì add left, không thì ngược lại
                else addRight(newCus);
                sizeCusInDesk++;
                customerTime *newTimeLine = new customerTime(newCus);
                appendTimeline(newTimeLine);
                customerX = newCus;
                return;
            }//Khi số lượng >= MAXSIZE/2 thì phải tìm vị trí HighRES rồi add
            else{
                if (newCus->energy >= customerX->energy)addLeft(newCus);//Nếu energy lớn hơn customerX thì add chiều kim đồng hồ, không thì ngược lại
                else addRight(newCus);
                sizeCusInDesk++;
                customerTime*newTimeline = new customerTime(newCus);
                appendTimeline(newTimeline);
                customerX = newCus;
                return;

            }//Trường hợp tổng quát
        }
        void BLUE(int num)
        {

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

        }
        void LIGHT(int num)
        {
            if (num == 0 && sizeCusInQueue != 0){
                customer*print = customerFirstQueue;
                if(print == nullptr)return;
                while(print != NULL)
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
        }
};