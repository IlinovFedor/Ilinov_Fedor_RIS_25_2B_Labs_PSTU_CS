#include <fstream>
#include <string>

int balancedSplit(const std::string &workPath, const std::string &buf1Path, const std::string &buf2Path,
                  int runLen) {
    std::ifstream work(workPath);
    std::ofstream buf1(buf1Path), buf2(buf2Path);
    std::ofstream *bufs[] = {&buf1, &buf2};

    int segments = 0, cnt = 0, cur = 0, a;
    while (work >> a) {
        if (cnt == 0) {
            segments++;
        }
        *bufs[cur] << a << ' ';
        cnt++;
        if (cnt == runLen) {
            cnt = 0;
            cur = 1 - cur;
        }
    }
    work.close();
    buf1.close();
    buf2.close();
    return segments;
}

void balancedMerge(const std::string &workPath, const std::string &buf1Path, const std::string &buf2Path,
                   int runLen) {
    std::ifstream buf1(buf1Path), buf2(buf2Path);
    std::ofstream work(workPath);

    int valB = 0, valC = 0;
    bool hasB = (bool)(buf1 >> valB);
    bool hasC = (bool)(buf2 >> valC);

    while (hasB || hasC) {
        int countB = 0;
        int countC = 0;

        while ((hasB && countB < runLen) || (hasC && countC < runLen)) {
            bool availB = hasB && countB < runLen;
            bool availC = hasC && countC < runLen;
            bool takeB = false;

            if (!availB) {
                takeB = false;
            } else if (!availC) {
                takeB = true;
            } else {
                takeB = valB <= valC;
            }

            if (takeB) {
                work << valB << ' ';
                countB++;
                if (countB < runLen) {
                    hasB = (bool)(buf1 >> valB);
                }
            } else {
                work << valC << ' ';
                countC++;
                if (countC < runLen) {
                    hasC = (bool)(buf2 >> valC);
                }
            }
        }

        if (countB == runLen) {
            hasB = (bool)(buf1 >> valB);
        }
        if (countC == runLen) {
            hasC = (bool)(buf2 >> valC);
        }
    }

    work.close();
    buf1.close();
    buf2.close();
}

void balancedSort(const std::string &inPath, const std::string &outPath, const std::string &buf1Path,
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

    int runLen = 1;
    int segments = balancedSplit(outPath, buf1Path, buf2Path, runLen);
    while (segments > 1) {
        balancedMerge(outPath, buf1Path, buf2Path, runLen);
        runLen *= 2;
        segments = balancedSplit(outPath, buf1Path, buf2Path, runLen);
    }
}
