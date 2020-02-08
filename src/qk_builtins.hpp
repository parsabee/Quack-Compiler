#ifndef _QKBUILTINS_H_
#define _QKBUILTINS_H_

#include "all.hpp"
#include "ast_node.hpp"
#include "environment.hpp"

namespace ast {
    class Class; /* forward reference */
    class Classes; /* forward reference */

    /* Primitive types */
    Class *Obj_class();

    Class *String_class();

    Class *Integer_class();

    Class *Boolean_class();

    Class *Nothing_class();

}

#endif /* _QKBUILTINS_H_ */
