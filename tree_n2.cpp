#include <iostream>
#include <vector>
#include <string>

struct Node {
    std::string sub = "";
    std::vector<int> ch;

    Node() {
    }

    Node(const std::string& sub) : sub(sub) {
    }
};

struct SuffixTree {
    std::vector<Node> nodes;
    std::string str;

    SuffixTree(const std::string& str) : str(str) {
        if (str.empty()) {
            std::cout << "Ошибка: пустая строка\n";
        }
        else if (str == " " || str.find_first_not_of(' ') == std::string::npos) {
            std::cout << "Ошибка: задан только пробел\n";
        }
        else {
            nodes.push_back(Node{});
            for (size_t i = 0; i < str.length(); i++) {
                addSuffix(i);
            }
        }
    }

    void visualize() {
        displayTree(0, "");
    }

private:
    void addSuffix(int pos) {
        int n = 0;
        while (pos < str.length()) {
            char b = str[pos];
            int x2 = 0;
            int n2;
            while (true) {
                auto children = nodes[n].ch;
                if (x2 == children.size()) {
                    n2 = nodes.size();
                    nodes.push_back(Node(str.substr(pos)));
                    nodes[n].ch.push_back(n2);
                    return;
                }
                n2 = children[x2];
                if (nodes[n2].sub[0] == b) {
                    break;
                }
                x2++;
            }
            auto sub2 = nodes[n2].sub;
            size_t j = 0;
            while (j < sub2.size()) {
                if (str[pos + j] != sub2[j]) {
                    auto n3 = n2;
                    n2 = nodes.size();
                    nodes.push_back(Node(sub2.substr(0, j)));
                    nodes[n2].ch.push_back(n3);
                    nodes[n3].sub = sub2.substr(j);
                    nodes[n].ch[x2] = n2;
                    break;
                }
                j++;
            }
            pos += j;
            n = n2;
        }
    }

    void displayTree(int node, std::string prefix, bool isRoot = true) {
        if (nodes[node].ch.empty()) {
            std::cout << prefix << "+-- " << nodes[node].sub << '\n';
        }
        else {
            if (!isRoot) {
                std::cout << prefix << "+-+ " << nodes[node].sub << '\n';
            }
            else {
                std::cout << prefix << "+ " << nodes[node].sub << '\n';
            }
            for (size_t i = 0; i < nodes[node].ch.size(); i++) {
                std::string newPrefix = prefix;
                if (i < nodes[node].ch.size() - 1) {
                    newPrefix += "| ";
                }
                else {
                    newPrefix += "  ";
                }
                displayTree(nodes[node].ch[i], newPrefix, false);
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    SuffixTree suffixTree1(" ");
    suffixTree1.visualize();

    return 0;
}