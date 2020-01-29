/*
 * MIT License
 *
 * Copyright (c) 2020 Parsa Bagheri
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdlib.h>
#include "builtins.h"

/* ======================= Class Declerations ======================= */

/**************************
 * Vec2D forward reference
 **************************/
struct class_Vec2D_struct;
typedef struct obj_Vec2D_struct *obj_Vec2D;
typedef struct class_Vec2D_struct *class_Vec2D;

/* ======================= Class Definitions ======================== */

/*******************
 * Vec2D definition
 *******************/
struct obj_Vec2D_struct {
  struct class_Vec2D_struct *clazz;
  obj_Int y;
  obj_Int x;
};

struct class_Vec2D_struct {
  class_Obj _super;

  /* method table */
  obj_Vec2D (*constructor)(obj_Int x, obj_Int y);
  obj_Boolean (*EQUALS)(obj_Obj, obj_Obj) /* inherit */;
  obj_Nothing (*PRINT)(obj_Vec2D) /* override */;
  obj_String (*STR)(obj_Obj) /* inherit */;
  obj_Vec2D (*PLUS)(obj_Vec2D, obj_Vec2D) ;
};

extern class_Vec2D the_class_Vec2D;

/********************
 * Vec2D constructor
 ********************/
obj_Vec2D new_Vec2D( obj_Int var__x, obj_Int var__y ) {
  obj_Vec2D this = (obj_Vec2D)malloc(sizeof(struct obj_Vec2D_struct));
  this->clazz = the_class_Vec2D;
  obj_Int tmp__0001 = var__x;
  obj_Vec2D tmp__0002 = (obj_Vec2D)this;
  tmp__0002->x = (obj_Int)tmp__0001;
  obj_Int tmp__0003 = var__y;
  obj_Vec2D tmp__0004 = (obj_Vec2D)this;
  tmp__0004->y = (obj_Int)tmp__0003;
  return this;
}

obj_Vec2D Vec2D_method_PLUS( obj_Vec2D this, obj_Vec2D var__other ) {
  obj_Vec2D tmp__0003 = (obj_Vec2D)this;
  obj_Int tmp__0004 = (obj_Int)(tmp__0003->x);
  obj_Int tmp__0002 = tmp__0004;
  obj_Vec2D tmp__0005 = var__other;
  obj_Int tmp__0006 = (obj_Int)(tmp__0005->x);
  obj_Int tmp__0001 = (obj_Int)tmp__0002->clazz->PLUS((obj_Int)tmp__0002, (obj_Int)tmp__0006);
  obj_Int tmp__0007 = tmp__0001;
  obj_Vec2D tmp__0010 = (obj_Vec2D)this;
  obj_Int tmp__0011 = (obj_Int)(tmp__0010->y);
  obj_Int tmp__0009 = tmp__0011;
  obj_Vec2D tmp__0012 = var__other;
  obj_Int tmp__0013 = (obj_Int)(tmp__0012->y);
  obj_Int tmp__0008 = (obj_Int)tmp__0009->clazz->PLUS((obj_Int)tmp__0009, (obj_Int)tmp__0013);
  obj_Int tmp__0014 = tmp__0008;
  obj_Vec2D tmp__0015 = new_Vec2D((obj_Int)tmp__0007, (obj_Int)tmp__0014);
  return (obj_Vec2D)tmp__0015;
}

obj_Nothing Vec2D_method_PRINT( obj_Vec2D this ) {
  obj_String tmp__0003 = str_literal( "<" );
  obj_String tmp__0002 = tmp__0003;
  obj_Obj tmp__0001 = (obj_Obj)tmp__0002->clazz->PRINT((obj_Obj)tmp__0002);
  obj_Obj tmp__0004 = tmp__0001;
  obj_Vec2D tmp__0007 = (obj_Vec2D)this;
  obj_Int tmp__0008 = (obj_Int)(tmp__0007->x);
  obj_Int tmp__0006 = tmp__0008;
  obj_Obj tmp__0005 = (obj_Obj)tmp__0006->clazz->PRINT((obj_Obj)tmp__0006);
  obj_Obj tmp__0009 = tmp__0005;
  obj_String tmp__0012 = str_literal( ", " );
  obj_String tmp__0011 = tmp__0012;
  obj_Obj tmp__0010 = (obj_Obj)tmp__0011->clazz->PRINT((obj_Obj)tmp__0011);
  obj_Obj tmp__0013 = tmp__0010;
  obj_Vec2D tmp__0016 = (obj_Vec2D)this;
  obj_Int tmp__0017 = (obj_Int)(tmp__0016->y);
  obj_Int tmp__0015 = tmp__0017;
  obj_Obj tmp__0014 = (obj_Obj)tmp__0015->clazz->PRINT((obj_Obj)tmp__0015);
  obj_Obj tmp__0018 = tmp__0014;
  obj_String tmp__0021 = str_literal( ">\n" );
  obj_String tmp__0020 = tmp__0021;
  obj_Obj tmp__0019 = (obj_Obj)tmp__0020->clazz->PRINT((obj_Obj)tmp__0020);
  obj_Obj tmp__0022 = tmp__0019;
  return none;
}

/* The Vec2D Class (a singleton) */
struct class_Vec2D_struct the_class_Vec2D_struct = {
  &the_class_Obj_struct,
  new_Vec2D,
  Obj_method_EQUALS,
  Vec2D_method_PRINT,
  Obj_method_STR,
  Vec2D_method_PLUS
};

class_Vec2D the_class_Vec2D = &the_class_Vec2D_struct;

/* ============================== Main ============================== */

int main (int argc, char *argv[]) {
  obj_Int tmp__0005 = int_literal( 5 );
  obj_Int tmp__0006 = int_literal( 6 );
  obj_Vec2D tmp__0007 = new_Vec2D((obj_Int)tmp__0005, (obj_Int)tmp__0006);
  obj_Vec2D tmp__0004 = tmp__0007;
  obj_Int tmp__0008 = int_literal( 6 );
  obj_Int tmp__0009 = int_literal( 7 );
  obj_Vec2D tmp__0010 = new_Vec2D((obj_Int)tmp__0008, (obj_Int)tmp__0009);
  obj_Vec2D tmp__0003 = (obj_Vec2D)tmp__0004->clazz->PLUS((obj_Vec2D)tmp__0004, (obj_Vec2D)tmp__0010);
  obj_Vec2D tmp__0011 = tmp__0003;
  obj_Vec2D tmp__0002 = tmp__0011;
  obj_Nothing tmp__0001 = (obj_Nothing)tmp__0002->clazz->PRINT((obj_Vec2D)tmp__0002);
  obj_Nothing tmp__0012 = tmp__0001;
  exit(0);
}
