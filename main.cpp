#include <iostream>
#include <ctime>
#include <iomanip>
#include <map>
#include <vector>

struct my_friend{
    std::string name;
    std::tm birthday{};
    double diff = 0;
};

void print_vec(std::vector<my_friend> vec);
void print_next_birthday( std::map<double, std::vector<my_friend>> bro_map);

int main() {
    std::cout << "24.1. My Friends Birthdays" << std::endl;

    std::time_t current_t = std::time(nullptr);
    std::tm* current_tm = std::localtime(&current_t);

    std::vector <my_friend> my_friends;

    while(true){
        my_friend bro;
        std::cout << "Name: ";
        std::cin >> bro.name;

        if(bro.name == "end") break;

        while(true){
            std::cout << "Birthday (YYYY/MM/DD): ";
            std::cin >> std::get_time(&bro.birthday, "%Y/%m/%d");
            if(std::cin.fail()){
                std::cin.clear();
                std::string str;
                std::getline(std::cin, str);
                std::cout << "Incorrect format of date. Try again." << std::endl;
            } else {
                if(mktime(&bro.birthday) <= mktime(current_tm)){
                    my_friends.push_back(bro);
                    break;
                } else {
                    std::cout << "Birthday can't be in the future. Try again" << std::endl;
                }
            }
        }
    }

    std::tm today_tm = {};
    today_tm.tm_mon = current_tm->tm_mon;
    today_tm.tm_mday = current_tm->tm_mday;

    std::map<double, std::vector<my_friend>> next_birthday_in_this_year;

    for(auto item: my_friends) {
        item.birthday.tm_year = today_tm.tm_year;
        item.diff = difftime( mktime(&item.birthday), mktime(&today_tm));

        if(item.diff >= 0) {
            next_birthday_in_this_year[item.diff].push_back(item);
        }
    }

    print_next_birthday(next_birthday_in_this_year);

    return 0;
}

void print_vec(std::vector<my_friend> vec){
    for(auto item:vec){
        std::cout << item.name << " " << std::put_time(&item.birthday, "%m/%d" ) << std::endl;
    }
}

void print_next_birthday( std::map<double, std::vector<my_friend>> bro_map){
    if(bro_map.begin()->first == 0){
        std::cout << "Today is birthday of: " << std::endl;
        print_vec(bro_map.begin()->second);
    } else {
        std::cout << "Friend's next birthday: " << std::endl;
        print_vec(bro_map.begin()->second);
    }
}
