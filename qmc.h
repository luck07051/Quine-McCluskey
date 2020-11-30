#ifndef QMC_H_
#define QMC_H_

#include <iostream>

namespace qmc
{
    class term
    {
        private:
            unsigned long num;
            unsigned long mask; // mask for '-'

        public:
            bool pr_im; //preme implicant, if it is true


            static unsigned int size;

            term(unsigned long nu, unsigned long ma = 0, bool pr = true): num(nu), mask(ma), pr_im(pr) { num = num & ~mask; };
            term(): num(0), mask(0), pr_im(true) {};
            term(const term & te, bool pr = true): num(te.num), mask(te.mask), pr_im(pr) {};
            term(const term & te, unsigned long ma, bool pr = true): num(te.num), mask(ma), pr_im(pr) { num = num & ~mask; }; // copy te.num to this.num and change this.mask to ma
            term & operator=(const term & te);
            ~term() {};

            bool operator<(const term & te) const;
            bool operator>(const term & te) const;
            bool operator==(const term & te) const;
            bool operator<=(const term & te) const { return !(*this > te); };
            bool operator>=(const term & te) const { return !(*this < te); };;
            bool operator!=(const term & te) const { return !(*this == te); };;


            int how_many_one() const;
            unsigned long compare(const term & te) const; // return new mask, if no, return 0
            friend std::ostream & operator<<(std::ostream & os, const term & te);
            std::ostream & out_for_ta(std::ostream & os) const;
            std::ostream & out_for_out(std::ostream & os) const;
    };
}

#endif
