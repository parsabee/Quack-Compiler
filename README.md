# Quack-Compiler
a compiler for Quack, an object oriented statically typed language with type inference.
Work in progress...

### Build
```
mkdir build
cd build
cmake ..
cmake --build .
```
### Execute
```
./qkc [-o output] <.qk input file> 
```
the generated `.c` file has to be linked with `builtins` library

### What A Quack Program Looks Like
```
/* abstract node class */
class Node() {
    def search(val: Int): Boolean {
        return false;
    }

    def STR(): String {
        return "";
    }
}

/* leaf concrete type */
class Leaf(value: Int) extends Node {
    this.val = value;

    def STR(): String {
        return this.val.STR();
    }

    def search(val: Int): Boolean {
        if (this.val == val) {
            return true;
        } else {
            return false;
        }
    }
}

/* inner node concrete type */
class Inner(left: Node, right: Node, value: Int) extends Node {
    this.val = value;
    this.l = left;
    this.r = right;

    def STR(): String {
        return this.l.STR() + " " + this.val.STR() + " " + this.r.STR();
    }

    def search(val: Int): Boolean {
        if (this.val == val) {
            return true;
        } elif (this.val < val) {
            return this.r.search(val);
        } else {
            return this.l.search(val);
        }
    }
}
```