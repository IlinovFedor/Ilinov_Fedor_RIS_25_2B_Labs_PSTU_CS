#include <iostream>

#include "natural_merge_sort.cpp"
#include "balanced_merge_sort.cpp"
#include "polyphase_merge_sort.cpp"

using namespace std;

int main() {
    naturalSort("in", "naturalOut", "naturalBuf1", "naturalBuf2");
    balancedSort("in", "balancedOut", "balancedBuf1", "balancedBuf2");
    polyphaseSort("in", "polyphaseOut", "polyphaseBuf1", "polyphaseBuf2");
    ifstream in("in"), nout("naturalOut"), bout("balancedOut"), pout("polyphaseOut");

    std::string s;
    getline(in, s);
    std::cout << s << "\n\n";

    cout << "natural\n";
    getline(nout, s);
    cout << '\t' + s + '\n';

    cout << "balanced\n";
    getline(bout, s);
    cout << '\t' + s + '\n';

    cout << "polyphase\n";
    getline(pout, s);
    cout << '\t' + s + '\n';

}
