The New C language compiler prototype

Features:
- Rewriting symbols on the AST side:
    #macro(a) name_@{typeof a}();
    ...
    macro(x);
  would call `name_int` if `x` has type int, or `name_int_ptr`,
  if x has type `int *`
- Avoids most of the C++ issues, yet includes the most useful C++ features,
  like parametric classes, RAII and OOP.
- Allows overloading the "." method, redirecting all undefined methods
  to another object.
- 100% compatible with C99.
- Define methods and overload operators on builtin types:
    int int."[]"(int bit) {
      return ((*this)>>bit)&1;
    }
    int main() {
      int x = 123;
      if (x[0]) printf("%d is odd\n", x);
      else printf("%d is even\n", x);
      return 0;
    }
- `&` references allow you to use pointer variables
  like the values they are pointed to:
    int &x;  // declare x to be a reference
    &x = &y  // x is now a proxy for y
             // all changes to x are redirected to y
    x = 123; //set the value of y to be 123
  this is useful when the pointer itself is rarely modified.
  
  

Differences from C++:

- Like in C++, destructor (dtor method) is called on variables when they leave
  scope. There is one exception. If the class has no copy constructor defined,
  then its dtor wont be called before return, and the object will
  be copied as is (byte-by-byte):
    CLst foo() {
      CLst xs;
      return xs; //if CLst has CLst.ctor_CLst method, it will be called
                 //to make a copy, and the original object will get dtor'ed.
                 //otherwise no dtor/ctor will be called, and xs itself
                 //will be returned
    }
  rationale: it is more intuitive and useful default behavior.