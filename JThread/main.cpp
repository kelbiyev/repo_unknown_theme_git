/*
#include <iostream>
#include <thread>
#include <chrono>

void print_hello() {
    std::cout<<"Hello\n";
}
int main() {
    std::thread normal_thread(print_hello());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return 0;
}
//MISTAKE : unused .join();
*/

/*
#include <iostream>
#include <thread>
#include <chrono>

void print_hello() {
    std::cout<<"Hello\n";
}
int main() {
    std::jthread j_normal_thread(print_hello);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return 0;
}
*/

#include <iostream>
#include <chrono>
#include <thread>
int main() {
    std::stop_source s_sourse;
    std::stop_token s_token;
    std::cout<<"Stop possible: "<<s_token.stop_possible()<<"\n";
    std::cout<<"Stop requested: "<<s_token.stop_possible()<<"\n";
    auto my_thread = std::jthread([](std::stop_token stop_token) {
        int count = 0;
        while (!stop_token.stop_requested()) {
            std::cout<<count++<<"\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }
    );

    s_sourse = my_thread.get_stop_source();
    s_token = my_thread.get_stop_token();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    if(s_sourse.stop_possible()) {
        s_sourse.request_stop();
        std::cout<<"Stop request sent\n";
    }
    std::cout<<"Stop possible: "<<s_sourse.stop_possible()<<"\n";
    std::cout<<"Stop requested: "<<s_sourse.stop_requested()<<"\n";

    return 0;
}


