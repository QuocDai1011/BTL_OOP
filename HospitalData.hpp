#ifndef HOSPITALDATA_HPP
#define HOSPITALDATA_HPP
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Date	{
	int day;
	int month;
	int year;	
};

class Human {
	protected:
		string name;
		int gender; // quy dinh 0 la NU va 1 la NAM
		string phoneNumber;
	public:
		Human();
		Human(string name, int gender, string phoneNumber);
		virtual string getName() const = 0;
        virtual int getGender() const = 0;
        virtual string getPhoneNumber() const = 0;
		void setName(const string &newName) { name = newName; }
		void setGender(const int &newGender) { gender = newGender; }
		void setPhoneNumber(const string &newPhoneNumber) { phoneNumber = newPhoneNumber; }                                                                       
		// friend istream& operator>>(istream& in, Human* h) {
        // 	cout << "Enter the patient's name: ";
        // 	in >> ws;  // Discard any leading whitespace
        // 	getline(in, h->name);
        
        // 	cout << "Enter the patient's gender (0: FEMALE || 1: MALE): ";
        // 	in >> h->gender;

        // 	cout << "Enter the patient's telephone number: ";
        // 	in >> ws;  // Discard any leading whitespace
        // 	in >> h->phoneNumber;

        // 	return in;
    	// }
};

class Staff : public Human {
	private: 
		string ID;
		string address;
		string pass;
	public:
		Staff();  
		Staff(string name, int gender, string phoneNumber, string ID, string address, string pass);	
		void logIn(int &login);
		void setName(const string &newName);
		void setGender(const int &newGender);
		void setPhoneNumber(const string &newPhoneNumber);
		string getName() const override { return name;}
		int getGender() const override { return gender;}
		string getPhoneNumber() const override { return phoneNumber;}
};

class Patient : public Human {
	private:
		Date dateBuy; // ngay mua thuoc
		string currentStatus; // tinh trang hien tai
		string IDmedicine; // ID thuoc
		string quantity; //so luong thuoc.
		string accumulatedPoints; // diem da tich duoc
		string amountReceived; // so tien da nhan
	public:
		Patient();
		Patient(string name, int gender, string phoneNumber, Date dateBuy, string currentStatus, 
		string IDmedicine, string quantity, string accumulatedPoints, string amountReceived);
		Date getDateOfBirth();
		string getAddress();
		Date getDateOfHospital();
		string getCurrentStatus();
		string getName() const override { return name; }
        int getGender() const override { return gender; }
        string getPhoneNumber() const override { return phoneNumber; }
		string getIDdoctor();
		void setName(const string &newName);
		void setGender(const int &newGender) { Human::setGender(newGender); }
		void setPhoneNumber(const string &newPhoneNumber) { Human::setPhoneNumber(newPhoneNumber); }
		void setCurrentStatus(const string &newStatus);
		void setIDdoctor(const string &newIDdoctor);
		//
		// void setInformation();
		// void outInformation();
		friend istream& operator>>(istream& is, Patient *p);
		friend ostream& operator<<(ostream& os, Patient *p);
		bool checkIDdoctor(string ID);
		bool checkIDmedicine(string ID); 
}; 

class Prescription {
	private:
		string ID;
		string namePrescription; // ten thuoc
		double price; // gia tien
		string dosageForm; //dang bao che
		int currentQuantity; // so luong hien tại trong kho
		string dosageOfDrug; // cach dùng của thuốc
	public:
		Prescription();
		Prescription(string ID, string namePrescription, double price, string dosageForm,
		int currentQuantity, string dosageOfDrug);
		void readFromFile();
		string getIDFromFile(string IDCheck);
		string getNamePresciptionFromFile(string ID);
		double getPriceByIDFromFile(string ID);
		string getDosageFormFromFile(string ID);
};

class Bill {
private:
    string ID;
    string nameOfPatient; // tên của bệnh nhân
    string totalCost; // tổng chi phí
    string statusPay; // tình trạng thanh toán (0 là chưa thanh toán, 1 là đã thanh toán)
    Date dateOfBill; // ngày tạo hóa đơn
    string patientPhone; // số điện thoại bệnh nhân
    vector<pair<string, int>> medicineList; // danh sách thuốc (ID thuốc và số lượng)
public:
    Bill();
    Bill(string ID, string nameOfPatient, string totalCost, string statusPay, Date dateOfBill);
    Bill(string phone);
	void loadMedicineList(); // Đọc danh sách thuốc từ file informationPatient.txt 
    void calculateTotalCost(); // Tính toán tổng tiền thuốc 
    void displayBill(); // Hiển thị hóa đơn
};


#endif