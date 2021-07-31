#include <stdio.h>
#include <unordered_map>
#include <algorithm>
#include <cctype>

std::vector<int> dies[30];
auto nextFree = dies;
std::unordered_map<int, std::vector<int>*> permToDie;
std::unordered_map<int, std::vector<int>*> combToDie;
char opposite[6] = { 1, 0, 4, 5, 2, 3 };

char rotate[6][4] = { { 2, 3, 4, 5 }, { 5, 4, 3, 2 }, { 0, 5, 1, 3 },
                      { 1, 4, 0, 2 }, { 0, 3, 1, 5 }, { 0, 4, 1, 2 } };

inline std::vector<int>* addCombination(int combination)
{
    auto it = combToDie.find(combination);
    if(it == combToDie.end())
    {
        combToDie.insert( { combination, nextFree++ } );
        return nextFree-1;
    }
    else
        return it->second;
}
inline int permToComb(const std::vector<int>& perm)
{
    int comb = 0;
    int pos = find(perm.begin(), perm.end(), 6) - perm.begin();
    comb += perm[opposite[pos]]*10000;
    int nm = perm[opposite[pos]] == 5 ? 4 : 5;
    int pos2 = std::find(perm.begin(), perm.end(), nm) - perm.begin();

    int pos3 = std::find(rotate[pos], rotate[pos] + 4, pos2) - rotate[pos];
    int mul = 1000;
    for(int i = 0; i < 4; i++, mul /= 10)
        comb += perm[rotate[pos][(pos3 + i) % 4]]*mul;
    return comb;
}

inline int getint()
{
    int ret = 0, ch;
    while(!isdigit(ch = getc(stdin)));
    ret = ch - '0';
    while(isdigit(ch = getc(stdin)))
        ret = ret*10 + ch - '0';
    return ret;
}

int main()
{
    int N = getint();
    std::vector<int> perm = { 1, 2, 3, 4, 5, 6 };
    do
    {
        int comb = permToComb(perm);
        auto p = addCombination(comb);
        int pint = 0;

        for(int i = 0, mul = 100000; i < 6; i++, mul /= 10)
            pint += perm[i]*mul;
        permToDie.insert( { pint, p } );
    }
    while(next_permutation(perm.begin(), perm.end()));

    std::vector<std::vector<int>*> output;
    for(int i = 1; i <= N; i++)
    {
        int pint = 0;
        for(int j = 0, mul = 100000; j < 6; j++, mul /= 10)
        {
            int d = getint();
            pint += d*mul;
        }

        if(permToDie[pint]->empty())
            output.push_back(permToDie[pint]);
        permToDie[pint]->push_back(i);
    }
    printf("%d\n", output.size());
    for(int i = 0; i < output.size(); i++)
    {
        for(int j = 0; j < output[i]->size(); j++)
            printf("%d ", (*output[i])[j]);
        printf("\n");
    }
}
