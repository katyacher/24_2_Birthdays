#include <iostream>
#include <ctime>
#include <iomanip>
#include <map>

int main() {
    std::cout << "24.1. My Friends BirthDay" << std::endl;
    std::time_t current_t = std::time(nullptr);
    std::tm* current_tm = std::localtime(&current_t);
    std::multimap <std::string, std::tm> birthdays;
    std::string name;
    std::tm birthday{};

    while(true){
        std::cout << "Name: ";
        std::cin >> name;
        if(name == "end") {
            break;
        } else{
            std::cout << "Birthday (YYYY/MM/DD): ";
            std::cin >> std::get_time(&birthday, "%Y/%m/%d");
            birthdays.emplace(name, birthday);
        }
    }

    std::multimap<double,std::string> next;

    for(auto my_friend: birthdays) {
        my_friend.second.tm_year = current_tm->tm_year;
        double diff = difftime(current_t, mktime(&my_friend.second));
        next.emplace(std::abs(diff), my_friend.first);

        if(my_friend.second.tm_mon == current_tm->tm_mon
            && my_friend.second.tm_mday == current_tm->tm_mday){
            std::cout << "Today is "<< my_friend.first << "'s birthday. " ;
        }
    }
    std::cout << next.begin()->second << std::endl;
    return 0;
}
