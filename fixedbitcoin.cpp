#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <thread>

#include "bitcoin.h"

std::string generate_address()
{
    unsigned __int128 low = 0x100000000000000000;
    unsigned __int128 high = 0x1fffffffffffffffff;
    std::random_device rd;
    std::mt19937_64 generator(rd());
    std::uniform_int_distribution<unsigned __int128> distribution(low, high);
    unsigned __int128 val = distribution(generator);
    std::string result = std::to_string(val);
    result = std::string(46 + result.length() - result.length(), '0') + result;
    std::string priv = result;
    std::string pub = privtopub(priv);
    std::string pubkey1 = encode_pubkey(privtopub(priv), "bin_compressed");
    std::string addr = pubtoaddr(pubkey1);
    return addr + "," + result;
}

void check_address(int process_index)
{
    auto start_time = std::chrono::steady_clock::now();
    int keys_generated = 0;
    double g = 0.0;

    while (true)
    {
        std::string addr_result = generate_address();
        std::string addr = addr_result.substr(0, addr_result.find(','));
        std::string result = addr_result.substr(addr_result.find(',') + 1);
        keys_generated++;

        if (addr == "19vkiEajfhuZ8bs8Zu2jgmC6oqZbWqhxhG")
        {
            std::cout << "found!! " << addr << " " << result << std::endl;
            std::string k1 = result;
            std::string k2 = privtopub(result);
            std::string k3 = addr;

            std::ofstream file("boom.txt", std::ios_base::app);
            file << "Private key: " << k1 << '\n' << "Public key: " << k2 << '\n' << "Address: " << k3 << '\n' << '\n';
            file.close();

            return;
        }
        else
        {
            auto elapsed_time = std::chrono::steady_clock::now() - start_time;
            double elapsed_seconds = std::chrono::duration<double>(elapsed_time).count();
            if (elapsed_seconds >= 1.0)
            {
                double speed = keys_generated / elapsed_seconds;
                g = speed;
                keys_generated = 0;
                start_time = std::chrono::steady_clock::now();
            }

            std::cout << "searching... Process " << process_index << " " << addr << " " << result << " Speed: " << g << " keys/second" << std::endl;
        }
    }
}

int main()
{
    int num_processes = std::thread::hardware_concurrency();

    std::vector<std::thread> threads;
    for (int i = 0; i < num_processes; i++)
    {
        threads.emplace_back(check_address, i);
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    return 0;
}
