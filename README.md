# Keanuwhoa
api for whoa.onrender.com database whoa saying by Keanu Reeves in his movies.
# main
```cpp
#include "Keanuwhoa.h"
#include <iostream>

int main() {
   Keanuwhoa api;

    auto whoa = api.random_whoas(0,3).then([](json::value result) {
        std::cout << "Search results: " << result.serialize() << std::endl;
    });
    whoa.wait();
    
    return 0;
}
```

# Launch (your script)
```
g++ -std=c++11 -o main main.cpp -lcpprest -lssl -lcrypto -lpthread -lboost_system -lboost_chrono -lboost_thread
./main
```
