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