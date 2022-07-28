#include <iostream>
#include <vector>
#include <cpr/cpr.h>

cpr::Parameters httpParamsFromPairs(std::vector<cpr::Pair>& base) {
    cpr::Parameters result;
    for (auto & it : base) {
        result.Add(cpr::Parameter(it.key, it.value));
    }
    return result;
}

cpr::Payload httpPayloadFromPairs(std::vector<cpr::Pair>& base) {
    cpr::Payload result{base.begin(), base.end()};
    return result;
}

int main() {
    std::cout << "Enter parameters of request (key and value);\n"
                 "Enter get or post to make request of according type;\n"
                 "Enter exit to stop program.\n\n";

    std::vector<cpr::Pair> params;
    while (true) {
        std::cout << "Enter key or command:" << std::endl;
        std::string command;
        std::cin >> command;

        if (command == "exit") {
            return 0;
        } else if (command == "get") {
            cpr::Parameters cprParams = httpParamsFromPairs(params);
            cpr::Response response = cpr::Get(cpr::Url("http://httpbin.org/get"), cprParams);
            params.clear();
            std::cout << response.text << std::endl;
        } else if (command == "post") {
            cpr::Payload cprParams = httpPayloadFromPairs(params);
            cpr::Response response = cpr::Post(cpr::Url("http://httpbin.org/post"), cprParams);
            params.clear();
            std::cout << response.text << std::endl;
        } else {
            std::cout << "Key " << command << " registered, enter value:" << std::endl;
            std::string value;
            std::cin >> value;
            params.emplace_back(command, value);
            std::cout << "Pair {" << command << ", " << value << "} have been added to parameters list." << std::endl;
        }
    }
}
