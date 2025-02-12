#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string text = "int x = 42; // комментарий";
    std::regex keyword_regex(R"(\b(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)\b)");
    std::smatch matches;

    if (std::regex_search(text, matches, keyword_regex)) {
        std::cout << "Найдено ключевое слово: " << matches[0] << std::endl;
    } else {
        std::cout << "Ключевые слова не найдены." << std::endl;
    }

    return 0;
}
