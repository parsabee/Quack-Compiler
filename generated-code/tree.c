/*
 * MIT License
 *
 * Copyright (c) 2020 Parsa Bagheri
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * _input_file the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included _input_file all
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

/*************************
 * Node forward reference
 *************************/
struct class_Node_struct;
typedef struct obj_Node_struct *obj_Node;
typedef struct class_Node_struct *class_Node;

/*************************
 * Leaf forward reference
 *************************/
struct class_Leaf_struct;
typedef struct obj_Leaf_struct *obj_Leaf;
typedef struct class_Leaf_struct *class_Leaf;

/**************************
 * Inner forward reference
 **************************/
struct class_Inner_struct;
typedef struct obj_Inner_struct *obj_Inner;
typedef struct class_Inner_struct *class_Inner;

/* ======================= Class Definitions ======================== */

/******************
 * Node definition
 ******************/
struct obj_Node_struct {
  struct class_Node_struct *clazz;
};

struct class_Node_struct {
  class_Obj super_;

  /* method table */
  obj_Node (*constructor)(void);
  obj_Boolean (*EQUALS)(obj_Obj, obj_Obj); /* inherited */
  obj_Obj (*PRINT)(obj_Obj); /* inherited */
  obj_String (*STR)(obj_Node); /* overridden or introduced */
  obj_Boolean (*search)(obj_Node, obj_Int); /* overridden or introduced */
};

extern class_Node the_class_Node;

/**************
 * constructor
 **************/
obj_Node new_Node() {
  obj_Node this = (obj_Node)malloc(sizeof(struct obj_Node_struct));
  this->clazz = the_class_Node;
  return this;
}

obj_Boolean Node_method_search( obj_Node this, obj_Int var__val ) {
  obj_Boolean tmp__001 = lit_false;
  return (obj_Boolean)tmp__001;
}

obj_String Node_method_STR( obj_Node this ) {
  obj_String tmp__001 = str_literal( "" );
  return (obj_String)tmp__001;
}

struct class_Node_struct the_class_Node_struct = {
  &the_class_Obj_struct,
  new_Node,
  Obj_method_EQUALS,
  Obj_method_PRINT,
  Node_method_STR,
  Node_method_search
};

class_Node the_class_Node = &the_class_Node_struct;

/******************
 * Leaf definition
 ******************/
struct obj_Leaf_struct {
  struct class_Leaf_struct *clazz;
  obj_Int val;
};

struct class_Leaf_struct {
  class_Node super_;

  /* method table */
  obj_Leaf (*constructor)(obj_Int);
  obj_Boolean (*EQUALS)(obj_Obj, obj_Obj); /* inherited */
  obj_Obj (*PRINT)(obj_Obj); /* inherited */
  obj_String (*STR)(obj_Leaf); /* overridden or introduced */
  obj_Boolean (*search)(obj_Leaf, obj_Int); /* overridden or introduced */
};

extern class_Leaf the_class_Leaf;

/**************
 * constructor
 **************/
obj_Leaf new_Leaf(obj_Int var__value) {
  obj_Leaf this = (obj_Leaf)malloc(sizeof(struct obj_Leaf_struct));
  this->clazz = the_class_Leaf;
  obj_Int tmp__001 = var__value;
  obj_Leaf tmp__002 = (obj_Leaf)this;
  tmp__002->val = (obj_Int)tmp__001;
  return this;
}

obj_String Leaf_method_STR( obj_Leaf this ) {
  obj_Leaf tmp__003 = (obj_Leaf)this;
  obj_Int tmp__004 = (obj_Int)(tmp__003->val);
  obj_Int tmp__002 = tmp__004;
  obj_String tmp__001 = (obj_String)(tmp__002->clazz->STR((obj_Int)tmp__002));
  obj_String tmp__005 = tmp__001;
  return (obj_String)tmp__005;
}

obj_Boolean Leaf_method_search( obj_Leaf this, obj_Int var__val ) {
  obj_Leaf tmp__003 = (obj_Leaf)this;
  obj_Int tmp__004 = (obj_Int)(tmp__003->val);
  obj_Int tmp__002 = tmp__004;
  obj_Int tmp__005 = var__val;
  obj_Boolean tmp__001 = (obj_Boolean)(tmp__002->clazz->EQUALS((obj_Int)tmp__002, (obj_Obj)tmp__005));
  obj_Boolean tmp__006 = tmp__001;
  if ( tmp__006->value ) goto true___001;
  else goto false___001;
  
true___001: /* if */ ;
    obj_Boolean tmp__007 = lit_true;
    return (obj_Boolean)tmp__007;
    goto endif___001;
  
false___001: /* else */ ;
    obj_Boolean tmp__008 = lit_false;
    return (obj_Boolean)tmp__008;
    goto endif___001;
  
endif___001: /* fi */ ;
}

struct class_Leaf_struct the_class_Leaf_struct = {
  &the_class_Node_struct,
  new_Leaf,
  Obj_method_EQUALS,
  Obj_method_PRINT,
  Leaf_method_STR,
  Leaf_method_search
};

class_Leaf the_class_Leaf = &the_class_Leaf_struct;

/*******************
 * Inner definition
 *******************/
struct obj_Inner_struct {
  struct class_Inner_struct *clazz;
  obj_Node r;
  obj_Node l;
  obj_Int val;
};

struct class_Inner_struct {
  class_Node super_;

  /* method table */
  obj_Inner (*constructor)(obj_Node, obj_Node, obj_Int);
  obj_Boolean (*EQUALS)(obj_Obj, obj_Obj); /* inherited */
  obj_Obj (*PRINT)(obj_Obj); /* inherited */
  obj_String (*STR)(obj_Inner); /* overridden or introduced */
  obj_Boolean (*search)(obj_Inner, obj_Int); /* overridden or introduced */
};

extern class_Inner the_class_Inner;

/**************
 * constructor
 **************/
obj_Inner new_Inner(obj_Node var__left, obj_Node var__right, obj_Int var__value) {
  obj_Inner this = (obj_Inner)malloc(sizeof(struct obj_Inner_struct));
  this->clazz = the_class_Inner;
  obj_Int tmp__001 = var__value;
  obj_Inner tmp__002 = (obj_Inner)this;
  tmp__002->val = (obj_Int)tmp__001;
  obj_Node tmp__003 = var__left;
  obj_Inner tmp__004 = (obj_Inner)this;
  tmp__004->l = (obj_Node)tmp__003;
  obj_Node tmp__005 = var__right;
  obj_Inner tmp__006 = (obj_Inner)this;
  tmp__006->r = (obj_Node)tmp__005;
  return this;
}

obj_String Inner_method_STR( obj_Inner this ) {
  obj_Inner tmp__011 = (obj_Inner)this;
  obj_Node tmp__012 = (obj_Node)(tmp__011->l);
  obj_Node tmp__010 = tmp__012;
  obj_String tmp__009 = (obj_String)(tmp__010->clazz->STR((obj_Node)tmp__010));
  obj_String tmp__013 = tmp__009;
  obj_String tmp__008 = tmp__013;
  obj_String tmp__014 = str_literal( " " );
  obj_String tmp__007 = (obj_String)(tmp__008->clazz->PLUS((obj_String)tmp__008, (obj_String)tmp__014));
  obj_String tmp__015 = tmp__007;
  obj_String tmp__006 = tmp__015;
  obj_Inner tmp__018 = (obj_Inner)this;
  obj_Int tmp__019 = (obj_Int)(tmp__018->val);
  obj_Int tmp__017 = tmp__019;
  obj_String tmp__016 = (obj_String)(tmp__017->clazz->STR((obj_Int)tmp__017));
  obj_String tmp__020 = tmp__016;
  obj_String tmp__005 = (obj_String)(tmp__006->clazz->PLUS((obj_String)tmp__006, (obj_String)tmp__020));
  obj_String tmp__021 = tmp__005;
  obj_String tmp__004 = tmp__021;
  obj_String tmp__022 = str_literal( " " );
  obj_String tmp__003 = (obj_String)(tmp__004->clazz->PLUS((obj_String)tmp__004, (obj_String)tmp__022));
  obj_String tmp__023 = tmp__003;
  obj_String tmp__002 = tmp__023;
  obj_Inner tmp__026 = (obj_Inner)this;
  obj_Node tmp__027 = (obj_Node)(tmp__026->r);
  obj_Node tmp__025 = tmp__027;
  obj_String tmp__024 = (obj_String)(tmp__025->clazz->STR((obj_Node)tmp__025));
  obj_String tmp__028 = tmp__024;
  obj_String tmp__001 = (obj_String)(tmp__002->clazz->PLUS((obj_String)tmp__002, (obj_String)tmp__028));
  obj_String tmp__029 = tmp__001;
  return (obj_String)tmp__029;
}

obj_Boolean Inner_method_search( obj_Inner this, obj_Int var__val ) {
  obj_Inner tmp__003 = (obj_Inner)this;
  obj_Int tmp__004 = (obj_Int)(tmp__003->val);
  obj_Int tmp__002 = tmp__004;
  obj_Int tmp__005 = var__val;
  obj_Boolean tmp__001 = (obj_Boolean)(tmp__002->clazz->EQUALS((obj_Int)tmp__002, (obj_Obj)tmp__005));
  obj_Boolean tmp__006 = tmp__001;
  if ( tmp__006->value ) goto true___002;
  else goto false___002;
  
true___002: /* if */ ;
    obj_Boolean tmp__007 = lit_true;
    return (obj_Boolean)tmp__007;
    goto endif___002;
  
false___002: /* else */ ;
    obj_Inner tmp__010 = (obj_Inner)this;
    obj_Int tmp__011 = (obj_Int)(tmp__010->val);
    obj_Int tmp__009 = tmp__011;
    obj_Int tmp__012 = var__val;
    obj_Boolean tmp__008 = (obj_Boolean)(tmp__009->clazz->LESS((obj_Int)tmp__009, (obj_Int)tmp__012));
    obj_Boolean tmp__013 = tmp__008;
    if ( tmp__013->value ) goto true___003;
    else goto false___003;
    
true___003: /* if */ ;
      obj_Inner tmp__016 = (obj_Inner)this;
      obj_Node tmp__017 = (obj_Node)(tmp__016->r);
      obj_Node tmp__015 = tmp__017;
      obj_Int tmp__018 = var__val;
      obj_Boolean tmp__014 = (obj_Boolean)(tmp__015->clazz->search((obj_Node)tmp__015, (obj_Int)tmp__018));
      obj_Boolean tmp__019 = tmp__014;
      return (obj_Boolean)tmp__019;
      goto endif___003;
    
false___003: /* else */ ;
      obj_Inner tmp__022 = (obj_Inner)this;
      obj_Node tmp__023 = (obj_Node)(tmp__022->l);
      obj_Node tmp__021 = tmp__023;
      obj_Int tmp__024 = var__val;
      obj_Boolean tmp__020 = (obj_Boolean)(tmp__021->clazz->search((obj_Node)tmp__021, (obj_Int)tmp__024));
      obj_Boolean tmp__025 = tmp__020;
      return (obj_Boolean)tmp__025;
      goto endif___003;
    
endif___003: /* fi */ ;
    goto endif___002;
  
endif___002: /* fi */ ;
}

struct class_Inner_struct the_class_Inner_struct = {
  &the_class_Node_struct,
  new_Inner,
  Obj_method_EQUALS,
  Obj_method_PRINT,
  Inner_method_STR,
  Inner_method_search
};

class_Inner the_class_Inner = &the_class_Inner_struct;

/* ============================== Main ============================== */

int main (int argc, char *argv[]) {
  obj_Int tmp__001 = int_literal( 3 );
  obj_Leaf tmp__002 = new_Leaf((obj_Int)tmp__001);
  obj_Int tmp__003 = int_literal( 5 );
  obj_Leaf tmp__004 = new_Leaf((obj_Int)tmp__003);
  obj_Int tmp__005 = int_literal( 4 );
  obj_Inner tmp__006 = new_Inner((obj_Node)tmp__002, (obj_Node)tmp__004, (obj_Int)tmp__005);
  obj_Int tmp__007 = int_literal( 7 );
  obj_Leaf tmp__008 = new_Leaf((obj_Int)tmp__007);
  obj_Int tmp__009 = int_literal( 9 );
  obj_Leaf tmp__010 = new_Leaf((obj_Int)tmp__009);
  obj_Int tmp__011 = int_literal( 8 );
  obj_Inner tmp__012 = new_Inner((obj_Node)tmp__008, (obj_Node)tmp__010, (obj_Int)tmp__011);
  obj_Int tmp__013 = int_literal( 6 );
  obj_Inner tmp__014 = new_Inner((obj_Node)tmp__006, (obj_Node)tmp__012, (obj_Int)tmp__013);
  obj_Node var__root;
  var__root = (obj_Node)tmp__014;
  obj_Node tmp__021 = var__root;
  obj_Node tmp__020 = tmp__021;
  obj_String tmp__019 = (obj_String)(tmp__020->clazz->STR((obj_Node)tmp__020));
  obj_String tmp__022 = tmp__019;
  obj_String tmp__018 = tmp__022;
  obj_String tmp__023 = str_literal( "\n" );
  obj_String tmp__017 = (obj_String)(tmp__018->clazz->PLUS((obj_String)tmp__018, (obj_String)tmp__023));
  obj_String tmp__024 = tmp__017;
  obj_String tmp__016 = tmp__024;
  obj_Obj tmp__015 = (obj_Obj)(tmp__016->clazz->PRINT((obj_Obj)tmp__016));
  obj_Obj tmp__025 = tmp__015;
  obj_Node tmp__030 = var__root;
  obj_Node tmp__029 = tmp__030;
  obj_Int tmp__031 = int_literal( 3 );
  obj_Boolean tmp__028 = (obj_Boolean)(tmp__029->clazz->search((obj_Node)tmp__029, (obj_Int)tmp__031));
  obj_Boolean tmp__032 = tmp__028;
  obj_Boolean tmp__027 = tmp__032;
  obj_Obj tmp__026 = (obj_Obj)(tmp__027->clazz->PRINT((obj_Obj)tmp__027));
  obj_Obj tmp__033 = tmp__026;
  exit(0);
}
