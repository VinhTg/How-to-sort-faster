#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <filesystem>
#include <cstdlib>

using namespace std;



 void hoan_doi(string &a, string &b) {
    string temp = a; a = b; b = temp;
}


 string tail_string(int x, int len = 4) {
    string s = "";
    for (int i = 0; i < len; i++) {
        char c = 'z' - (x % 26);
        s += c;
        x /= 26;
    }
    return s;
}

 void tu_xao_tron(vector<string> &arr) {
    int n = (int)arr.size();
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        hoan_doi(arr[i], arr[j]);
    }
}



 void strlexi_test1() {
    ofstream fout("strlexi/test001.in");
    vector<string> ans;
    int groups = 3125, bucket = 32, prefA = 45, prefB = 45;
    for (int g = 0; g < groups; g++) {
        string pref(prefA, 'a');
        pref += char('a' + (g % 26));
        pref += char('a' + ((g / 26) % 26));
        pref += char('a' + ((g / 676) % 26));
        for (int i = 0; i < bucket; i++)
            ans.push_back(pref + string(prefB, 'a') + tail_string(bucket - i));
    }
    tu_xao_tron(ans);
    fout << ans.size() << '\n';
    for (const string &s : ans) fout << s << '\n';
}

 void strlexi_test2() {
    ofstream fout("strlexi/test002.in");
    vector<string> ans;
    int groups = 6250, bucket = 16, prefA = 45, prefB = 45;
    for (int g = 0; g < groups; g++) {
        string pref(prefA, 'a');
        pref += char('a' + (g % 26));
        pref += char('a' + ((g / 26) % 26));
        pref += char('a' + ((g / 676) % 26));
        for (int i = 0; i < bucket; i++)
            ans.push_back(pref + string(prefB, 'a') + tail_string(bucket - i));
    }
    tu_xao_tron(ans);
    fout << ans.size() << '\n';
    for (const string &s : ans) fout << s << '\n';
}

 void strlexi_test3() {
    ofstream fout("strlexi/test003.in");
    vector<string> ans;
    int groups = 2500, bucket = 32, prefA = 90, prefB = 5;
    for (int g = 0; g < groups; g++) {
        string pref(prefA, 'a');
        pref += char('a' + (g % 26));
        pref += char('a' + ((g / 26) % 26));
        pref += char('a' + ((g / 676) % 26));
        for (int i = 0; i < bucket; i++)
            ans.push_back(pref + string(prefB, 'a') + tail_string(bucket - i));
    }
    tu_xao_tron(ans);
    fout << ans.size() << '\n';
    for (const string &s : ans) fout << s << '\n';
}

 void strlexi_test4() {
    ofstream fout("strlexi/test004.in");
    vector<string> ans;
    int groups = 2000, bucket = 50, prefA = 95, prefB = 1;
    for (int g = 0; g < groups; g++) {
        string pref(prefA, 'a');
        pref += char('a' + (g % 26));
        pref += char('a' + ((g / 26) % 26));
        pref += char('a' + ((g / 676) % 26));
        for (int i = 0; i < bucket; i++)
            ans.push_back(pref + string(prefB, 'a') + tail_string(bucket - i));
    }

    fout << ans.size() << '\n';
    for (const string &s : ans) fout << s << '\n';
}

 void strlexi_test5() {
    ofstream fout("strlexi/test005.in");
    vector<string> ans;
    for (int g = 0; g < 2000; g++) {
        int bucket = (g & 1) ? 16 : 32;
        string pref(70, 'a');
        pref += char('a' + (g % 26));
        pref += char('a' + ((g / 26) % 26));
        for (int i = 0; i < bucket; i++)
            ans.push_back(pref + string(20, 'a') + tail_string(bucket - i));
    }
    tu_xao_tron(ans);
    fout << ans.size() << '\n';
    for (const string &s : ans) fout << s << '\n';
}


 void strlenlexi_test1() {
    ofstream fout("strlenlexi/test001.in");
    int n = 9999;
    fout << n << '\n';
    for (int i = 0; i < n; ++i) {
        int idx = i % 676;
        fout << (char)('z' - (idx / 26)) << (char)('z' - (idx % 26));
        for (int j = 1; j <= 100; ++j) fout << 'a';
        fout << '\n';
    }
}

 void strlenlexi_test2() {
    ofstream fout("strlenlexi/test002.in");
    int n = 9999;
    fout << n << '\n';
    for (int i = 0; i < n; ++i) {
        int idx = i % 676;
        fout << (char)('z' - (idx / 26)) << (char)('z' - (idx % 26));
        for (int j = 0; j < 97; ++j) fout << 'b';
        fout << (char)('z' - (i % 26)) << '\n';
    }
}

 void strlenlexi_test3() {
    ofstream fout("strlenlexi/test003.in");
    int n = 9999;
    fout << n << '\n';
    for (int i = 0; i < n; ++i) {
        int gr = i / 25;
        char c2 = 'd' - (gr % 26);
        if (c2 < 'a') c2 = (char)('z' - ('a' - c2 - 1));
        fout << 'z' << c2 << 'h';
        for (int j = 0; j < 97; ++j) fout << 'c';
        fout << '\n';
    }
}

 void strlenlexi_test4() {
    ofstream fout("strlenlexi/test004.in");
    int n = 9999;
    fout << n << '\n';
    for (int i = 0; i < n; ++i) {
        fout << "qwert";
        int gr = i / 25;
        char c6 = 'n' - (gr % 14);
        if (c6 < 'a') c6 = 'z';
        fout << c6 << 'b';
        for (int j = 0; j < 90; ++j) fout << 'd';
        fout << (char)('a' + (i % 26)) << '\n';
    }
}

 void strlenlexi_test5() {
    ofstream fout("strlenlexi/test005.in");
    int n = 9999;
    fout << n << '\n';
    for (int i = 0; i < n; ++i) {
        fout << (char)('a' + ((i / 24) % 26)) << 'f';
        for (int j = 0; j < 97; ++j) fout << 'e';
        fout << (char)('z' - (i % 24)) << '\n';
    }
}


void int_test1() {
    ofstream fout("int/test001.in");

    int n = 100000;
    fout << n << '\n';

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    for (int i = 0; i < n; i++) {
        int y = (int)rng();

        if (i & 1) {
            y = -abs(y);
        } else {
            y = abs(y);
        }

        fout << y << '\n';
    }

    fout.close();
}

 void int_test2() {
    ofstream fout("int/test002.in");
    int n = 100000;
    fout << n << '\n';
    for (int i = 0; i < n; i++) {
        int x = i * 256;
        if (i & 1) x = -x;
        x ^= (i << 16);
        fout << x << '\n';
    }
}

void int_test3() {
    ofstream fout("int/test003.in");

    int n = 100000;
    fout << n << '\n';

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<long long> dist(0, 2147483647);

    for (int i = 0; i < n; i++) {
        long long y = dist(rng);

        if (i & 1) {
            y = -y;
        }

        y += i * 16777619LL;

        fout << (int)y << '\n';
    }

    fout.close();
}

 void int_test4() {
    ofstream fout("int/test004.in");
    fout << 1 << '\n';
    fout << -2147483648 << '\n';
}

 void int_test5() {
    ofstream fout("int/test005.in");
    int n = 100000;
    fout << n << '\n';
    mt19937 rng(123456789);
    for (int i = 0; i < n; i++) {
        unsigned int x = rng();
        x ^= (rng() << 8);
        x ^= (rng() << 16);
        int y = (int)x;
        if (i & 1) y = -y;
        fout << y << '\n';
    }
}



int main(int argc, char* argv[]) {
    if (argc != 3) return 1;
    filesystem::create_directories("int");
    filesystem::create_directories("strlexi");
    filesystem::create_directories("strlenlexi");

    srand(12345);

    string problem = argv[1];
    int test_num = atoi(argv[2]);

    if (test_num < 1 || test_num > 5)
        return 1;

    if (problem == "int") {
        if (test_num == 1) int_test1();
        else if (test_num == 2) int_test2();
        else if (test_num == 3) int_test3();
        else if (test_num == 4) int_test4();
        else int_test5();
    }
    else if (problem == "strlexi") {
        if (test_num == 1) strlexi_test1();
        else if (test_num == 2) strlexi_test2();
        else if (test_num == 3) strlexi_test3();
        else if (test_num == 4) strlexi_test4();
        else strlexi_test5();
    }
    else if (problem == "strlenlexi") {
        if (test_num == 1) strlenlexi_test1();
        else if (test_num == 2) strlenlexi_test2();
        else if (test_num == 3) strlenlexi_test3();
        else if (test_num == 4) strlenlexi_test4();
        else strlenlexi_test5();
    }
    else {
        return 1;
    }

    return 0;
}