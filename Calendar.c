// 万年历：输入年号，输出该年的所有日期

#include <stdio.h>  
   
// 计算某一天是周几（周日是0，周一是1，以此类推）  
int dayOfWeek(int year, int month, int day) {  
    if (month < 3) {  
        month += 12;  
        year--;  
    }  
    int c = year / 100;
    int y = year - c * 100;
    int week = (y + y / 4 + c / 4 - 2 * c + 26 * (month + 1) / 10 + day - 1) % 7;  
    return week;  
}  
  
// 判断是否为闰年  
int isLeapYear(int year) {  
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {  
        return 1;  
    }  
    return 0;  
}  
  
int main() {  
    int year, month, day, firstDay, daysInMonth, spacesToPrint;  
  
    printf("Select a year: ");  
    scanf("%d", &year);  
  
    for (month = 1; month <= 12; month++) {  
        // 计算每个月的第一天是星期几  
        firstDay = dayOfWeek(year, month, 1);  
  
        // 判断每个月天数 
        daysInMonth = 31;  
        if (month == 2) {  
            daysInMonth = isLeapYear(year) ? 29 : 28;  
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {  
            daysInMonth = 30;  
        }  
  
        printf("\n Month %d \n", month);  
        printf("Sun Mon Tue Wed Thu Fri Sat\n");  
  
        // 计算需要打印的空格数，将每月第一天和其对应的星期数对齐 
         spacesToPrint = firstDay;
        for (int i = 0; i < spacesToPrint; i++) {  
            printf("    ");  
        }  
  
        // 打印当月的每一天  
        for (day = 1; day <= daysInMonth; day++) {  
            printf("%2d  ", day);  
  
            // 如果下一个日期对应周日，则换行
            if (((day + firstDay) % 7) == 0) {
                printf("\n");
                spacesToPrint = 0; // 重置空格数为0
            }
        }  
    }  
  
    return 0;  
}