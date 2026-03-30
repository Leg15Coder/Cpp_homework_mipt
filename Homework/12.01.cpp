#include <iostream>
#include <string>
#include <sstream>
#include <locale>
#include <iomanip>

int main()
{
    const long double exchange_rate = 92.50L;

    std::locale io_locale("en_US.utf8");

    std::cout << "Enter amount to convert (US format): ";
    std::string input_line;
    std::getline(std::cin, input_line);

    std::stringstream ss(input_line);
    ss.imbue(io_locale);

    long double money_value = 0;
    ss >> std::get_money(money_value, false);
    if (ss.fail()) {
        ss.clear();
        ss.str(input_line);
        ss >> std::get_money(money_value, true);
    }

    if (ss.fail())
    {
        std::cerr << "Error: Could not parse monetary value in en_US format." << std::endl;
        return 1;
    }

    long double rub_amount = money_value / 100.0L;
    long double usd_amount = rub_amount / exchange_rate;

    long double usd_value_for_put = usd_amount * 100.0L;

    std::cout.imbue(io_locale);
    std::cout << "Converted amount in USD: " << std::showbase << std::put_money(usd_value_for_put, true) << std::endl;
}
