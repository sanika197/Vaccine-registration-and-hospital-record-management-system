#include  <iostream>
#include<iomanip>
#include <string>

using namespace std;
class user//node
{
    string name;
    int age;
    string adharNum;
    int hr, min;//time
    user* next;

public:
    user() {//default constructor of class user
        name = "--";
        age = 0;
        adharNum = "";
        hr = 8;
        min = 0;
        next = NULL;
    }
    void setSlot(int, int);
    int getSlotHr();
    int getSlotMin();
    friend class userOperations;
    friend class hospital;

};
class hospital
{
    int hID;
    string name;// hospital name
    int vCount;// total available vaccine
    user* head;//points to patients linked list

public:
    hospital() {  //default constructor
        hID = 0;
        name = "";
        vCount = 0;
        head = NULL;
    }

    hospital(int id, string nm, int cnt)  //parameterized constructor
    {
        hID = id;
        vCount = cnt;
        name = nm;
        head = NULL;
    }
    void updateHead(user* hd);//function to update head of ll after each registration
    string getName();
    int getCount();
    void setCount(int);
    user* getHead();

    static void display_Admin(hospital h[]);//hospitals vaccine count and number of pa
    static void display_User(hospital h[]);//hospital availability data for user
    void count();//count number of patients in a hospital
    void updateVCount();//take no of vaccines available from admin
    static void displayPtoA(hospital h[]);  //display patients in allocated hospitals


};
class userOperations
{

public:
    void User_register(hospital* ptr);//insert last
    void cancel_registration(hospital* ptr);// deleteAt
    void user_data(hospital* ptr);//patient data display
    friend class hospital;
    friend class user;
};
//*************************************************************************************************************************************
//hospital-opearations
string hospital::getName() {
    return name;
}
int hospital::getCount() {
    return vCount;
}
void hospital::setCount(int v) {
    vCount = v;
}

user* hospital::getHead() {
    return head;
}
void hospital::updateHead(user* hd) {
    head = hd;
}
void hospital::display_Admin(hospital h[])//O(m)
{
    //display hospitals details to admin
    int i = 0;
    cout << "                             *TODAYS DATA*                                      " << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << setw(5) << "ID" << setw(36) << "HOSPITAL" << setw(27) << "NUMBER OF VACCINES" << endl; 
    for (i = 0; i < 5; i++)
    {
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << setw(5) << h[i].hID << setw(36) << h[i].name << setw(27) << h[i].vCount << endl;

    }
    cout << "--------------------------------------------------------------------------------" << endl;
}
void hospital::display_User(hospital h[]) //O(mn)
{
    //display availablility of slots in hospitals
    int i, cnt;
    user* h1;
    cout << "                          ***HOSPITAL AVAILABILTY***" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << setw(5) << "ID" << setw(36) << "HOSPITAL" << setw(18) << "AVAILABILITY" << setw(21) << "DURATION" << endl;

    for (i = 0;i < 5;i++)
    {
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << setw(5) << i + 1 << setw(36) << h[i].getName() << setw(18);
        cnt = 0;
        h1 = h[i].getHead();
        while (h1 != NULL)
        {
            if (h1->name == "")
            {
                cnt++;   //counter for checking number of cancelled slots
            }
            h1 = h1->next;
        }
        if (h[i].getCount() != 0 || cnt > 0)  //if vaccines available or slots cancelled 
        {
            cout << "Available" << setw(21);  //print available
        }
        else
        {
            cout << "Unavailable" << setw(21);  //else vaccines not available
        }
        cout << "8 am  to  2 pm";  
        cout << endl;
    }//for-end
    cout << "--------------------------------------------------------------------------------" << endl;
}//display_user-function-end

void hospital::updateVCount()//O(1)
{
    //update no of vaccines available at hospital for one day
    int  no = 0;
    cout << "ENTER TODAYS VACCINE COUNT : " << endl;
    cin >> no;
    vCount = no;//update vaccine count
    cout << hID << "  NAME : " << name << "  TOTAL VACCINE : " << vCount << endl;//display updated data
    cout << "VACCINE COUNT UPDATED SUCCESSFULLY!!" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
}

void hospital::displayPtoA(hospital h[])
//function to display patient details from every hospital
{
    int i = 0, j = 0;;
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << setw(5) << "SR.NO" << setw(30) << "HOSPITAL NAME" << setw(30) << "PATIENT NAME" << setw(18) << "PATTIENT AGE" << endl;
    for (i = 0;i < 5;i++)
    {
        user* temp = h[i].getHead();//initializing temporary pointer to respective head pointer holding patients list
        if (temp == NULL)//if no patients available
        {
            cout << "-------------------------------------------------------------------------------------" << endl;
            cout << setw(5) << i + 1 << setw(30) << h[i].name << setw(30) << "NO PATIENTS " << endl;
        }
        j = 0;
        while (temp != NULL)//if patients are available
        {
            if (j == 0)
            {
                cout << "-------------------------------------------------------------------------------------" << endl;
                cout << setw(5) << i + 1 << setw(30) << h[i].name << setw(30) << temp->name << setw(10) << temp->age << endl;
            }
            else
            {
                cout << "-------------------------------------------------------------------------------------" << endl;
                cout << setw(65) << temp->name << setw(10) << temp->age << endl;
            }
            temp = temp->next;
            j++;
        }//while-end
    }//for-end
}//displayPtoA-function-end
void hospital::count()
//function to count number of patients(nodes)
{
    if (head == NULL)//if head is null then display no patients availabel
    {
        cout << "NO PATIENTS!!" << endl;
        return;
    }
    user* temp = head;//temporary pointer is used so as to avoid permanent data loss
    int cnt;//keeps track of node
    cnt = 0;
    while (temp != NULL)
    {
        cnt++;
        temp = temp->next;//traversing linked list
    }
    cout << "NUMBER OF PATIENTS: " << cnt << endl;//display total number of patients
    return;
}//count-function-end
//hospital-operation-end
//************************************************************************************************************************************
void user::setSlot(int h, int m)
{
    //alloacte time slot for patient
    hr = h;
    min = m;
}
int user::getSlotHr() {
    return hr;//get time slot for patient
}
int user::getSlotMin() {
    return min;//get time slot for patient
}
//user-operation-end
//************************************************************************************************************************************
//user-operations
void userOperations::User_register(hospital* ptr)//O(n)
{
    int cnt = 0, h = 0, m = 0;
    int flag;
    flag = 0;//slot is not available
    cnt = ptr->getCount();
    user* patient = new user();//newnode;
    if (cnt != 0)
    {
        flag = 1;//slot is available
        //enter details of patient
        cout << "->ENTER YOUR DETAILS :" << endl;
        cout << "NAME : " << endl;
        cin.ignore();
        getline(cin, patient->name);

        cout << "AGE : " << endl;
        cin >> patient->age;
        if (patient->age < 18 || patient->age>100)//validation for age
        {
            patient->name = "";
            cout << "INVALID AGE!!" << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
            return;
        }
        cout << "ADHAAR NUMBER : ";
        cin >> patient->adharNum;
        if ((patient->adharNum.length()) != 12)//validation of adhar number
        {
            patient->name = "";
            patient->age = 0;
            patient->adharNum = "";
            cout << "INVALID ADHAR NUMBER!!" << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
            return;
        }
        user* hd;
        user* temp;
        hd = ptr->getHead();//get head of linked list
        if (hd == NULL)
        {
            hd = patient; //add patient to list
            cnt--; //decrement vaccine count
        }
        else
        {
            temp = hd;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            h = temp->getSlotHr();//get time slot of prevoius patient
            m = temp->getSlotMin();
            if (m + 30 == 60)
            {
                patient->setSlot(h + 1, 0);//set time slot for patient
            }
            else
            {
                patient->setSlot(h, m + 30);//set time slot for patient
            }
            temp->next = patient;//add patient to list
            cnt--;//decrement vaccine count
        }
        ptr->updateHead(hd); //update head of linked list
        ptr->setCount(cnt); //update vaccine count of hospital
    }//if-end

    else  //allocate free slot if any after cancellation
    {
        user* temp1 = ptr->getHead();//get head of linkedlist
        while (temp1 != NULL)
        {
            if (temp1->name == "")//traverse loop till empty slot
            {
                flag = 1;//slot is available
                //accept patient details
                cout << "->ENTER YOUR DETAILS :" << endl;
                cout << "NAME : " << endl;;
                cin.ignore();
                getline(cin, temp1->name);
                cout << "AGE : " << endl;
                cin >> temp1->age;
                if (temp1->age < 18 || temp1->age>100)//validation for age
                {
                    temp1->name = "";
                    cout << "INVALID AGE!!" << endl;
                    return;
                }
                cout << "ADHAAR NUMBER : ";
                cin >> temp1->adharNum;
                if ((temp1->adharNum.length()) != 12)//validation of adhar number
                {
                    temp1->name = "";
                    temp1->age = 0;
                    temp1->adharNum == "";
                    cout << "INVALID ADHAR NUMBER!!" << endl;
                    return;
                }

            }//if-end
            temp1 = temp1->next;
        }//while-end
    }//else-end
    if (flag == 0)
    {
        cout << "SLOT IS NOT AVAILABEL!!" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
    }
    else
    {
        cout << "REGISTRATION SUCCESSFULL!!" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
    }

}//User_register-fuction-end

void userOperations::cancel_registration(hospital* admin)//O(n)
{
    string adnum;
    cout << "ENTER AADHAAR NUMBER : ";
    cin >> adnum;//take adhar number of patient to cancel registration
    if (adnum.length() != 12)//validation of adhar number
    {
        cout << "INVALID ADHAR NUMBER!!" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        return;
    }
    user* Head;
    Head = admin->getHead();//get head of linked list
    if (Head == NULL)//list is empty
    {
        cout << "THE HOSPITAL IS YET TO ALLOCATE ANY SLOTS." << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        return;
    }
    else
    {
        user* ptr;
        ptr = Head;
        while (ptr != NULL)//traverse list
        {
            if (adnum == ptr->adharNum)//entered adhar number is equal to adhar number of patient in list
            {
                //erase details of patient
                ptr->name = "";
                ptr->adharNum = "";
                ptr->age = 0;
                cout << "SLOT HAS BEEN CANCELLED SUCCESSFULLY!" << endl;
                cout << "--------------------------------------------------------------------------------" << endl;
                return;
            }
            ptr = ptr->next;
        }
    }
    cout << "NO DETAILS FOUND ASSOCIATED WITH AADHAAR NUMBER : " << adnum << endl;
    cout << "--------------------------------------------------------------------------------" << endl;

    return;
}

void userOperations::user_data(hospital* admin)//O(n)
{
    //display details of registered patient
    string adnum;
    cout << "ENTER AADHAAR NUMBER : ";
    cin >> adnum;//take adhar number of patient
    if (adnum.length() != 12)//validation of adhar number
    {
        cout << "INVALID AADHAAR NUMBER!!" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        return;
    }
    user* Head;
    Head = admin->getHead();//get head of linkedlist

    if (Head == NULL)//list is empty
    {
        cout << "NO DETAILS FOUND ASSOCIATED WITH AADHAAR NUMBER : " << adnum << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        return;
    }
    else
    {
        user* ptr;
        ptr = Head;
        while (ptr != NULL)//traverse list of patient
        {
            if (adnum == ptr->adharNum)//entered adhar number is equal to adhar number of patient in list
            {
                cout << "--------------------------------------------------------------------------------" << endl;
                cout << "NAME :" << ptr->name << "    PATTIENT AGE : " << ptr->age << endl;
                cout << "--------------------------------------------------------------------------------" << endl;
                cout << "ALLOTED HOSPITAL : " << admin->getName() << "   ALLOTED SLOT : ";
                if (ptr->getSlotHr() < 12)//time slot is before 12:00 
                {
                    cout << ptr->getSlotHr() << "." << ptr->getSlotMin() << "AM" << endl;
                }
                else//time slot is after 12:00
                {
                    cout << ptr->getSlotHr() << "." << ptr->getSlotMin() << "PM" << endl;
                }
                cout << "--------------------------------------------------------------------------------" << endl;
                return;
            }
            ptr = ptr->next;
        }
        cout << "--------------------------------------------------------------------------------" << endl;
    }
    cout << "YOU HAVE NOT REGISTERED FOR VACCINATION YET!" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    return;
}
//user-operations-end
//************************************************************************************************************************************
int main()
{
    hospital admin[5];
    //database
    admin[0] = hospital(1, "BHIMASHANKAR HOSPITAL", 2);
    admin[1] = hospital(2, "SDH HOSPITAL PUNE", 40);
    admin[2] = hospital(3, "PRIMARY HEALTH CENTER ADALE", 25);
    admin[3] = hospital(4, "KANHE PHATA RURAL HOSPITAL", 15);
    admin[4] = hospital(5, "TALEGHAR SDK", 30);
    int choice;//choose between admin and user
    do
    {

        cout << "->LOG IN AS: " << "\n1. ADMIN\n2. USER" << endl;
        cout << "OR\n3. EXIT" << endl;
        cin >> choice;

        switch (choice)
        {
            int option, tmpid;
        case 1: //Admin
            cout << "ENTER PASSWORD" << endl;
            int pass;
            cin >> pass;
            if (pass == 1234)
            {
                option = 0;//choose admin operation
                tmpid = 0;


                do {
                    //menu
                    hospital::display_Admin(admin);//sneha //display admin data

                    cout << "-------------------------------OPERATIONS--------------------------------------" << endl;
                    cout << "1.COUNT NUMBER OF PATIENTS IN A HOSPITTAL" << endl;
                    cout << "2.UDATE TOTAL VACCINE COUNT OF A HOSPITAL" << endl;
                    cout << "3.TODAY'S PATIENT DETAILS" << endl;
                    cout << "4.EXIT" << endl;
                    cout << "--------------------------------------------------------------------------------" << endl;
                    cout << "WHICH OPERATION YOU WISH TO PERFORM?" << endl;
                    cin >> option;
                    switch (option)
                    {
                    case 1:
                      
                        cout << "ENTER ID OF HOSPITAL" << endl;
                        cin >> tmpid;
                        admin[tmpid - 1].count();
                        cout << "--------------------------------------------------------------------------------" << endl;
                        break;
                    case 2:cout << "ENTER ID OF HOSPITAL" << endl;
                        cin >> tmpid;
                        admin[tmpid - 1].updateVCount();
                        //admin[tmpid-1].updateVCount();

                        break;

                    case 3:

                        hospital::displayPtoA(admin);
                        cout << "--------------------------------------------------------------------------------" << endl;
                        break;

                    case 4:
                        cout << "ADMIN EXIT COMPLETED!!" << endl;
                        cout << "--------------------------------------------------------------------------------" << endl;
                        break;
                    default:
                        cout << "INVALID CHOICE!!" << endl;
                        cout << "--------------------------------------------------------------------------------" << endl;
                        break;
                    }//admin-switch-end
                } while (option != 4);//admin-do-while-end
            }//if-end
            else
            {
                cout << "--------------------------------------------------------------------------------" << endl;
                cout << "INVALID PASSWORD !!!" << endl;
                cout << "--------------------------------------------------------------------------------" << endl;
            }
            break;
        case 2: //User
            userOperations u1;
            option = 0;//choose user operation
            tmpid = 0;

            do {
                //menu
                hospital::display_User(admin);//display hospital data

                cout << "1.REGISTERATION FOR VACCINATION" << endl;
                cout << "2.SEE ENTERED DATA" << endl;
                cout << "3.CANCEL REGISTRATION" << endl;
                cout << "4.EXIT" << endl;

                cout << "WHICH OPERATION YOU WISH TO PERFORM?" << endl;
                cin >> option;
                switch (option)
                {
                case 1:cout << "ENTER ID OF HOSPITAL" << endl;
                    cin >> tmpid;
                    u1.User_register(&admin[tmpid - 1]);//insert last
                    break;

                case 2: cout << "ENTER ID OF HOSPITAL" << endl;
                    cin >> tmpid;
                    cout << "YOUR DETAILS ARE:" << endl;
                    u1.user_data(&admin[tmpid - 1]);//display patient data
                    break;

                case 3: cout << "ENTER ID OF HOSPITAL" << endl;
                    cin >> tmpid;
                    u1.cancel_registration(&admin[tmpid - 1]);// deleteAt
                    break;

                case 4:
                    cout << "USER EXIT COMPLETED!!" << endl;
                    cout << "--------------------------------------------------------------------------------" << endl;
                    break;
                default:
                    cout << "INVALID CHOICE!!" << endl;
                    cout << "--------------------------------------------------------------------------------" << endl;
                    break;
                }//user-switch-end
            } while (option != 4);//user while
            break;//outter-switch-case-2-end
        case 3:
            cout << "EXIT COMPLETED!!" << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
            break;
        default:
            cout << "INVALID CHOICE !!" << endl;
            break;
        }//outter-switch-end
    } while (choice != 3);//outter-do-while-end
    return 0;
}
/*
Time complexity:
display_Admin(hospital h[]): O(m)
display_User(hospital h[]): O(mn)
updateVCount(): O(1)
displayPtoA(hospital h[]): O(m^2n)
count(): O(n)
User_register(hospital* ptr): O(n)
cancel_registration(hospital* admin): O(n)
user_data(hospital* admin): O(n)
*/