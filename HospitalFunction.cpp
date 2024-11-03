#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iomanip>
#include "./HospitalData.hpp"
#include "./HospitalFunction.hpp"
using namespace std;

bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

bool validationDate(Date date) {
    // Kiểm tra năm
    if (date.year < 1900 || date.year > 2024) {
        return false;
    }

    // Kiểm tra tháng
    if (date.month < 1 || date.month > 12) {
        return false;
    }

    // Kiểm tra ngày theo từng tháng
    if (date.day < 1) {
        return false; // Ngày không được nhỏ hơn 1
    }

    if (date.month == 2) { // Tháng 2
        if (isLeapYear(date.year)) {
            return date.day <= 29; // 29 ngày cho năm nhuận
        } else {
            return date.day <= 28; // 28 ngày cho năm không nhuận
        }
    } else { // Các tháng còn lại
        // Số ngày tối đa cho từng tháng
        int maxDays = (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) ? 30 : 31;
        return date.day <= maxDays;
    }
}

void printFunctions() {
	cout << "++++++++++-----------------FUNCTIONS-----------------------++++++++++\n";
    cout << "_________________________________________________\n";
    cout << "|  INDEX |              FUNCTIONS               |\n";
    cout << "|________|______________________________________|\n";
    cout << "|    1   | LOOK UP DOCTOR INFORMATION           |\n";
    cout << "|________|______________________________________|\n"; 
    cout << "|    2   | FIND PATIENTS BY PHONE NUMBER        |\n";
    cout << "|________|______________________________________|\n";
    cout << "|    3   | ENTER PATIENT INFORMATION            |\n";
    cout << "|________|______________________________________|\n";
    cout << "|    4   | UPDATE PATIENT INFORMATION           |\n";
    cout << "|________|______________________________________|\n";
    cout << "|    5   | PRINT INVOICE                        |\n";
    cout << "|________|______________________________________|\n";
    cout << "|    0   | LOG OUT                              |\n";
    cout << "|________|______________________________________|\n\n";
}

void doc(int n) {
    int tram = n / 100;
	int chuc = (n / 10) % 10;
	int dv = n % 10;

	switch (tram) {
	case 0:
		if(tram!=0)
		cout << "Khong Tram ";
		break;
	case 1:
		cout << "Mot Tram ";
		break;
	case 2:
		cout << "Hai Tram ";
		break;
	case 3:
		cout << "Ba Tram ";
		break;
	case 4:
		cout << "Bon Tram ";
		break;
	case 5:
		cout << "Nam Tram ";
		break;
	case 6:
		cout << "Sau Tram ";
		break;
	case 7:
		cout << "Bay Tram ";
		break;
	case 8:
		cout << "Tam Tram ";
		break;
	case 9:
		cout << "Chin Tram ";
		break;
	default:
		break;
	}
	switch (chuc) {
	case 0:
		if (dv != 0&&tram!=0)
			cout << "Le ";
		break;
	case 1:
		cout << "Muoi ";
		break;
	case 2:
		cout << "Hai Muoi ";
		break;
	case 3:
		cout << "Ba Muoi ";
		break;
	case 4:
		cout << "Bon Muoi ";
		break;
	case 5:
		cout << "Nam Muoi ";
		break;
	case 6:
		cout << "Sau Muoi ";
		break;
	case 7:
		cout << "Bay Muoi ";
		break;
	case 8:
		cout << "Tam Muoi ";
		break;
	case 9:
		cout << "Chin Muoi ";
		break;
	default:
		break;
	}
	switch (dv) {
	case 0:
		if (tram == 0 && chuc == 0) cout << "Khong ";
		break;
	case 1:
		cout << "Mot ";
		break;
	case 2:
		cout << "Hai ";
		break;
	case 3:
		cout << "Ba ";
		break;
	case 4:
		cout << "Bon ";
		break;
	case 5:
		if(chuc==0)cout << "Nam ";
		else cout << "Lam ";
		break;
	case 6:
		cout << "Sau ";
		break;
	case 7:
		cout << "Bay ";
		break;
	case 8:
		cout << "Tam ";
		break;
	case 9:
		cout << "Chin ";
		break;
	default:
		break;
	}
}

void docso(int n) {
    int numberArray[3]={0}, i = 0;
	int x = to_string(n).size();
		while (x >= 3 && i<3) {
			numberArray[i]= n % 1000;
			x -= 3; n = n / 1000;
			i++;
		}
		if (x != 0) numberArray[i] = n;
		for (int i = 2; i >= 0; i--) {
			if (numberArray[i] != 0) {
				doc(numberArray[i]);
				if (i == 2) cout << "Trieu ";
				else if (i == 1) cout << "Nghin ";
				else cout << "Dong.";
			}
		}
	
}

string nameFormat(string name) {
    stringstream ss(name);
    string word, temp = "";
    while (getline(ss, word, ' ')) {  // Split by spaces
        if (!word.empty()) {           // Skip empty words
            word[0] = toupper(word[0]);
            temp += word + ' ';
        }
    }
    if (!temp.empty()) {
        temp.pop_back(); // Remove the trailing space
    }
    return temp;
}

string removeSpace(string s) {
    stringstream ss(s);
    string word, temp = "";
    while (getline(ss, word, ',')) {  // Tách chuỗi theo dấu phẩy
        if (!word.empty()) {
            if (word[0] == ' ') {      // Kiểm tra nếu có khoảng trắng đầu
                word = word.substr(1); // Bỏ khoảng trắng đầu tiên
            }
            temp += word + ',';        // Ghép từ vào chuỗi kết quả
        }
    }
    if (!temp.empty()) {
        temp.pop_back(); // Xóa dấu phẩy cuối cùng
    }
    return temp;
}