#include "qmc.h"
using qmc::term;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <fstream>
using std::ifstream;

#include <set>
using std::set;

#include <vector>
using std::vector;

#include <algorithm>
#include <iterator>
#include <math.h>
using std::pow;



void Set_Size();
void Input(set<term> & min, set<term> & dont, set<term> & all);
class make_table
{
    public:
        bool is_show;
        std::ostream & os;

        make_table(bool sh, std::ostream & ost): is_show(sh), os(ost) {};
        ~make_table() {};
        void Make_Table(set<term> & in, set<term> & pi, unsigned int times =0);
};



int main()
{
    Set_Size();

    set<term> minterm, dontcare, all;
    Input(minterm, dontcare, all);

    set<term> prime_implicants;
    make_table mt{true, cout};
    mt.Make_Table(all, prime_implicants);

    return 0;
}


void Set_Size()
{
    unsigned int temp;
    cout << "Enter how many input(max:" << sizeof(unsigned long) *8 << "): ";
    while (!(cin >> temp) || temp < 0 || temp > sizeof(unsigned long) *8 )
    {
        cin.clear();
        while (cin.get() != '\n')
            continue;
        cout << "Error input, enter again: ";
    }
    term::size = temp;
}


void Input(set<term> & min, set<term> & dont, set<term> & all)
{
    unsigned long temp;
    unsigned long max_ = pow(2, term::size) -1;
    cout << "(range: 0 ~ " << max_ << ")" << endl;
    cout << "(out the range to stop)" << endl;
    cout << "Enter minterm: " << endl;
    while (cin >> temp)
    {
        if (temp < 0 || temp > max_)
            break;
        min.insert( term{temp} );
        all.insert( term{temp} );
    }
    if (!cin)
    {
        cin.clear();
        while (cin.get() != '\n')
            continue;
    }

    cout << "Enter don't care: " << endl;
    while (cin >> temp)
    {
        if (temp < 0 || temp > max_)
            break;
        if (!min.count(temp))
        {
            dont.insert( term{temp} );
            all.insert( term{temp} );
        }
    }
    if (!cin)
    {
        cin.clear();
        while (cin.get() != '\n')
            continue;
    }
}

void make_table::Make_Table(set<term> & in, set<term> & pi, unsigned int times)
{
    vector< set<term> > group(term::size +1 -times);
    for_each(in.begin(), in.end(), [&group](term te){ group[te.how_many_one()].insert(te); } );

    for (auto i = 0; i < group.size(); ++i)
    {
        if (!group[i].empty())
        {
            os << "G" << i << ":" << endl;
            for_each(group[i].begin(), group[i].end(), [&](term te){ os << '\t'; te.out_for_ta(os); os << endl; });
        }
    }
}
