#include <fstream>
#include <climits>
#include <string>

int naturalGetSeries(const std::string &workPath, const std::string &buf1Path, const std::string &buf2Path) {
    std::ifstream work(workPath);
    std::ofstream buf1(buf1Path), buf2(buf2Path);
    std::ofstream *bufs[] = {&buf1, &buf2};
    int prev = INT_MIN, cnt = 1, cur = 0;
    int a;
    while (work >> a) {
        if (a < prev) {
            *bufs[cur] << "\\ ";
            cur = (cur + 1) % 2;
            cnt++;
        }
        *bufs[cur] << a << ' ';
        prev = a;
    }
    work.close();
    buf1.close();
    buf2.close();
    return cnt;
}

void naturalMerge(const std::string &workPath, const std::string &buf1Path,
                  const std::string &buf2Path) {
    int series = naturalGetSeries(workPath, buf1Path, buf2Path);
    if (series < 2)
        return;
    std::ifstream buf1(buf1Path), buf2(buf2Path);
    std::ofstream work(workPath);

    for (int i = 0; i < (series + 1) / 2; i++) {
        std::string a, b;
        buf1 >> a;
        buf2 >> b;

        while (!buf1.eof() && !buf2.eof() && a != "\\" && b != "\\") {
            if (std::stoi(a) < std::stoi(b)) {
                work << a << ' ';
                buf1 >> a;
            } else {
                work << b << ' ';
                buf2 >> b;
            }
        }

        while (a != "\\" && !buf1.eof()) {
            work << a << ' ';
            buf1 >> a;
        }

        while (b != "\\" && !buf2.eof()) {
            work << b << ' ';
            buf2 >> b;
        }
    }
    work.close();
    buf1.close();
    buf2.close();
    naturalMerge(workPath, buf1Path, buf2Path);
}

void naturalSort(const std::string &inPath, const std::string &outPath, const std::string &buf1Path,
                 const std::string &buf2Path) {
    std::ifstream in;
    std::ofstream out;
    in.open(inPath);
    out.open(outPath);
    std::string s;
    while (!in.eof()) {
        in >> s;
        out << s << ' ';
    }
    in.close();
    out.close();
    naturalMerge(outPath, buf1Path, buf2Path);
}
