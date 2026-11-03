#include "uincampus/version.hpp"
#include <print>
int main()
{
    std::println("UIN-campus - Systeme de gestion academique");
    std::println("Version {}", uin::version());
}
