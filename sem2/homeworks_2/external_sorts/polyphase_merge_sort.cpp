#include <fstream>
#include <string>
#include <climits>

void upperFib(int n, int &a, int &b) {
    while (a + b < n) {
        int temp = a;
        a = a + b;
        b = temp;
    }
}

int countSeries(const std::string &workPath) {
    std::ifstream work(workPath);
    int cnt = 0, cur = 0;

    long long last = LLONG_MIN;
    bool f = (bool) (work >> cur);
    while (f) {
        while (f && cur >= last) {
            last = cur;
            f = (bool) (work >> cur);
        }
        last = LLONG_MIN;
        cnt++;
    }
    work.close();
    return cnt;
}

void polyphaseSplit(const std::string &workPath, const std::string &buf1Path, const std::string &buf2Path,
                    int firstCount, int targetB, int targetC) {
    std::ifstream work(workPath);
    std::ofstream buf1(buf1Path), buf2(buf2Path);

    int prev = INT_MIN;
    int seriesIndex = 0, realB = 0, realC = 0, cur = 0;
    if (work >> cur) {
        prev = cur;
        std::ofstream *out;
        if (seriesIndex < firstCount) out = &buf1;
        else out = &buf2;

        if (seriesIndex < firstCount) realB++;
        else realC++;

        *out << cur << ' ';
        while (work >> cur) {
            if (cur < prev) {
                *out << "\\" << ' ';
                seriesIndex++;
                if (seriesIndex < firstCount) out = &buf1;
                else out = &buf2;

                if (seriesIndex < firstCount) realB++;
                else realC++;
            }
            *out << cur << ' ';
            prev = cur;
        }
        *out << "\\" << ' ';
    }

    while (realB < targetB) {
        buf1 << "\\" << ' ';
        realB++;
    }
    while (realC < targetC) {
        buf2 << "\\" << ' ';
        realC++;
    }

    work.close();
    buf1.close();
    buf2.close();
}

std::streampos polyphaseMerge(const std::string &bigPath, const std::string &lowerPath,
                              const std::string &emptyPath, int lowerSeries,
                              std::streampos lowerPos) {
    std::ifstream big(bigPath);
    std::ifstream lower(lowerPath);
    std::ofstream empty(emptyPath);

    if (lowerPos != std::streampos(0)) lower.seekg(lowerPos);


    std::string a;
    std::string b;

    for (int i = 0; i < lowerSeries && (!big.eof() && !lower.eof()); i++) {
        big >> a;
        lower >> b;

        while (!big.eof() && !lower.eof() && a != "\\" && b != "\\") {
            if (std::stoi(a) <= std::stoi(b)) {
                empty << a << ' ';
                big >> a;
            } else {
                empty << b << ' ';
                lower >> b;
            }
        }

        while (a != "\\" && !big.eof()) {
            empty << a << ' ';
            big >> a;
        }

        while (b != "\\" && !lower.eof()) {
            empty << b << ' ';
            lower >> b;
        }

        empty << "\\" << ' ';
    }

    std::streampos pos = big.tellg();
    if (pos == std::streampos(-1)) pos = std::streampos(0);

    big.close();
    lower.close();
    empty.close();
    return pos;
}

void polyphaseSort(const std::string &inPath, const std::string &outPath, const std::string &buf1Path,
                   const std::string &buf2Path) {
    std::ifstream in(inPath);
    std::ofstream out(outPath);
    std::string s;
    while (!in.eof()) {
        if (!(in >> s)) break;
        out << s << ' ';
    }
    in.close();
    out.close();

    int series = countSeries(outPath);
    if (series < 2) return;

    int a = 1;
    int b = 0;
    upperFib(series, a, b);

    int firstCount = a - (a + b - series) / 2;
    polyphaseSplit(outPath, buf1Path, buf2Path, firstCount, a, b);

    std::string big = buf1Path;
    std::string lower = buf2Path;
    std::string empty = outPath;
    std::streampos lowerPos = 0;

    while (!(a == 1 && b == 0)) {
        lowerPos = polyphaseMerge(big, lower, empty, b, lowerPos);

        int temp = a;
        a = b;
        b = temp - b;

        std::string tempName = big;
        big = empty;
        empty = lower;
        lower = tempName;
    }

    std::string tempPath = (big != buf1Path) ? buf1Path : buf2Path;
    std::ifstream src(big);
    std::ofstream tmp(tempPath);
    while (!src.eof()) {
        if (!(src >> s)) break;
        if (s != "\\") tmp << s << ' ';
    }
    src.close();
    tmp.close();

    std::ifstream finalSrc(tempPath);
    std::ofstream finalOut(outPath);
    while (!finalSrc.eof()) {
        if (!(finalSrc >> s)) break;
        finalOut << s << ' ';
    }
    finalSrc.close();
    finalOut.close();
}
