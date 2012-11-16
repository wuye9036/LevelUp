#ifndef DUP_H_INCLUDED
#define DUP_H_INCLUDED

#include <stdlib.h>

template <class R> class duppable {
  public:
    // Virtual deep-copy method;
    // so it can't be applied to a NULL pointer.
    virtual R * dup0 (void) const = 0 ;

    // Nonvirtual deep-copy (calling the virtual one)
    // such that it can be applied to a NULL pointer.
    R * dup (void) const { return this ? dup0() : (R *) NULL ; } ;

} ;

#endif // DUP_H_INCLUDED
