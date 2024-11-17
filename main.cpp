#include <iostream>
#include <vector>
#include <iomanip>
#include "./HospitalData.hpp"
#include "./HospitalFunction.hpp"
using namespace std;

Human *staff[50]; // mang con tro cua staff
Human *patient[1000]; //mang con tro cua patient
Human *doctor[50]; // mang con tro cua doctor


int main() { 
    system("CLS");
    // Staff đăng nhập
    staff[0] = new Staff;
    int login = 0; //
    Staff* staffPtr = dynamic_cast<Staff*>(staff[0]);
    
    if (staffPtr) { 
        staffPtr->logIn(login);
    } else {
        cout << "Error: Unable to cast to Staff." << endl;
        return 1;
    }
    if (!login) {
        cout << "Login failed." << endl;
        return 1;
    }
    // Kết thúc đăng nhập
    int indexSp;
    do {
        printFunctions();
        cout << "Enter the index corresponding to the supported function: ";
        cin >> indexSp;
        if(indexSp < 0 || indexSp > 5) {
            while(indexSp < 0 || indexSp > 8) {
                cout << "Input is incorrect. Try again: ";
                cin >> indexSp;
            }
        } 
        switch (indexSp)
        {
            case 1: {
                system("CLS");
                cout << "-------------------- LIST OF DOCTORS --------------------\n";
                cout << "+---------+------------------------+---------+---------+" << endl;
                cout << "| ID      | NAME                   | GENDER  | WORKING |" << endl;
                cout << "+---------+------------------------+---------+---------+" << endl;
                doctor[0] = new Doctor;
                Doctor* doctorPtr = dynamic_cast<Doctor*>(doctor[0]);
                doctorPtr->readFromFile();
                break;
            }
            case 2: {
                system("CLS");
                Patient *pte = new Patient();
                string phone;
                cin.ignore();
                cout << "Enter the patient's phone number: ";
                getline(cin, phone);
                int check;
                system("CLS");
                cout << "+---------------------+---------+------------------+-------------------+-------------------+--------------------+-----------------------------------+--------------+" << endl;
                cout << "| Name                | Gender  | Phone Number     | Date of Birth     | Admission Date    | Address            | Current Status                    | Doctor's ID  |" << endl;
                cout << "+---------------------+---------+------------------+-------------------+-------------------+--------------------+-----------------------------------+--------------+" << endl;
                pte->readInFormationByPhoneNumber(phone, check, pte);
                if(check == 0) {
                    cout << "NOT FOUND THE PATIENT!\n";
                }
                break;
            }
            case 3: {
                Patient *p = new Patient();
                system("CLS");
                cin >> p;
                p->writeToFile();
                break;
            }
            case 4: {
                system("CLS");
                Patient *pte = new Patient();
                string phone;
                cin.ignore();
                cout << "Enter the patient's phone number: ";
                getline(cin, phone);
                int check;
                pte->readInFormationByPhoneNumber(phone, check, pte);
                system("CLS");
                if(check == 0) {
                    cout << "\n_____NOT FOUND THE PATIENT TO UPDATE INFORMATION!_____\n\n";
                    break;
                }else {
                    cout << "+---------------------+---------+------------------+-------------------+-------------------+--------------------+-----------------------------------+--------------+" << endl;
                    cout << "| Name                | Gender  | Phone Number     | Date of Birth     | Admission Date    | Address            | Current Status                    | Doctor's ID  |" << endl;
                    cout << "+---------------------+---------+------------------+-------------------+-------------------+--------------------+-----------------------------------+--------------+" << endl;
                    cout << pte;
                }
                cout << "\n------------------------------ UPDATE INFORMATION ------------------------------\n";
                pte->updateInformation();
                system("CLS");
                cout << "----------------------------- UPDATE SUCCESSFULLY ------------------------------\n\n";
                cout << "+---------------------+---------+------------------+-------------------+-------------------+--------------------+-----------------------------------+--------------+" << endl;
                cout << "| Name                | Gender  | Phone Number     | Date of Birth     | Admission Date    | Address            | Current Status                    | Doctor's ID  |" << endl;
                cout << "+---------------------+---------+------------------+-------------------+-------------------+--------------------+-----------------------------------+--------------+" << endl;
  
                cout << pte;
                pte->writeToFile();
                break;
            }
            case 5: {
                system("CLS");
                string phone;
                cin.ignore();
                cout << "Enter the patient's phone number for billing: ";
                getline(cin, phone);

                Bill bill(phone);
                bill.loadMedicineList();      // Đọc thông tin thuốc từ file
                bill.calculateTotalCost();    // Tính tổng chi phí thuốc
                bill.displayBill();           // Hiển thị hóa đơn
                break;
            }
            case 6: {
                system("CLS");
                Doctor dt;
                dt.addDoctor();
                break;
            }
            case 7: {
                system("CLS");
                cout << "-------------------- LIST OF DOCTORS --------------------\n\n";
                cout << "+---------+------------------------+---------+---------+" << endl;
                cout << "| ID      | NAME                   | GENDER  | WORKING |" << endl;
                cout << "+---------+------------------------+---------+---------+" << endl;
                doctor[0] = new Doctor;
                Doctor* doctorPtr = dynamic_cast<Doctor*>(doctor[0]);
                doctorPtr->readFromFile();
                Doctor dt;
                dt.deleteDoctor();
                break;
            }
            case 8: {
                system("CLS");
                Doctor dt;
                dt.sortExperience();
                break;
            }
            case 0: {
                system("CLS");
                cout << "\n\n";
                cout << "\t\t" << "_____GOODBYE_____";
                cout << "\n\n";
                break; 
            }
            default:
                break;
        }
    }while(indexSp != 0);
}
