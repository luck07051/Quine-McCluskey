#include "qmc.h"
#include <math.h>

namespace qmc
{
    unsigned int term::size = 0;

    term & term::operator=(const term & te)
    {
        num = te.num;
        mask = te.mask;
        return *this;
    }

    bool term::operator<(const term & te) const
    {
        if (num < te.num)
            return true;
        else if (num == te.num && mask < te.mask)
            return true;
        return false;
    }

    bool term::operator>(const term & te) const
    {
        if (num > te.num)
            return true;
        else if (num == te.num && mask > te.mask)
            return true;
        return false;
    }

    bool term::operator==(const term & te) const
    {
        if (num == te.num && mask == te.mask)
            return true;
        return false;
    }


    int term::how_many_one() const
    {
        int count = 0;
        unsigned long tmp = num;
        for (int i = term::size; i > 0; --i)
        {
            count += tmp % 2;
            tmp /= 2;
        }
        return count;
    }

    unsigned long term::compare(const term & te) const
    {
        if (mask == te.mask)
        {
            unsigned long tmp = num ^ te.num;
            int count = 0;
            for (int i = term::size; i > 0; --i)
            {
                count += tmp % 2;
                tmp /= 2;
            }

            if (count == 1)
            {
                return mask | (num ^ te.num);
            }
        }
        return 0;
    }

    std::ostream & term::out_for_ta(std::ostream & os) const
    {
        unsigned long mask_ = pow(2, term::size -1);
        for (int i = term::size; i > 0; --i)
        {
            if (mask & mask_)
            {
                os << '-';
            }
            else if (num & mask_)
            {
                os << '1';
            }
            else
            {
                os << '0';
            }

            mask_ /= 2;
        }
        return os;
    }
}
