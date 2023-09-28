THE NEW C MACRO LANGUAGE (NCM)
----------------------------------

NCM is a replacement for the C/C++ macroprocessor, fixing its issues and extending the features. NCM was born out of my own work on the New C language, which is designed to provide an alternative to C++, without the quirks of C++, while sticking with the original C design philosophy. The New C compiler will be available for sale soon.

NCM can be used as a standalone program, or embedded into your application to preprocess arbitrary text data, including GLSL, XML, HTML and scripting languages. For example, NCM can be used for generating HTML page from database query.

NCM can also run on top of ordinary C/C++ preprocessor, since it passes the escaped #\ directives to it unchanged.

src/main.c provides an example of a standalone use.

NCM improvements over the original C preprocessor:

- Succinct declarations: instead of `#define PI 3.14`, we now have `#PI 3.14`
  `#if #SYMBOL` instead of `#if defined SYMBOL`.

- `#pragma once` is made default for .h files, but user can at any
  time use the #multi directive to specify that the lines below
  can be included multiple times.
  The #once directive will move back into the single-include mode.
  Obviously there is no need for #ifndef/#define/#endif boilerplate.

- Optional and keyword arguments.
  Even if C99 doesn't support default values, NCM adds support for them:
    void foo(int x, int y, int z) {...}
    #foo(x,y=123,z=abc) foo(x,y,z)
  now that foo macro will supply the default values for y and z,
  and user can also call foo(456,z=789) to supply argument only for z

- Calculate arbitrary functions:
    #fac(n,x) #if n>0 fac(#[n-1],#[x*n]) #else x #endif
    fac(10,1) //expands into factorial of 10

    #count 0
    #next() {#<count> #<count=#[count+1]>}
    next() //expands into 0
    next() //expands into 1

- Redefine punctuation, like `+` and `-`:
    #+ -
    x+y    //expands into x-y

- Nest macros with different scopes, just like normal C variables.
    #x 123
    x //expands into 123
    #{
      #x 456 //shadow the x defined above
      #<x=#[x+1]> //increment x by 1
      x //expands into 457
    } //interior x gets out of scope
    x //expands int 123

- No need to escape newlines with `\`:
    #foo {
      printf("hello");
      printf("world");
    }
  The body will also produce proper #line numbers.

- Much easier to use variadic argument number macros. For example:
    #last([xs],x) x
  picks the last element of the arglist. While:
    #pp_map(f,x,[xs]) {f(x)#if xs_n != 0 , pp_map(f,xs) #endif}
    pp_map(f,a,b,c,d,e)
  expands into `f(a), f(b), f(c), f(d), f(e)`
  not how the auto argument xs_n got created to hold the length f xs

- printf style formatting:
    #("%-6s=%05d" "var1" 123)
  expands into `var1  =00123`

- Macros can be defined anywhere, not just at the start of the line.
  For example:
    #x 123
    #y #z{456} x z
    y
  will expand into `123 456`

- Insert macro arguments into strings:
   #foo(x, y) "#x+123+#y"

- Allows calling an external program or a user function with arguments.
  For example:
    #+ -
    #(echo "a+b")
  will expand into `a-b`: first external `echo` command is called with "a+b"
  Then then its stdout is being macroexpanded.

- Available as a single header library and can be used to preprocess
  other languages, like GLSL.

- Special builtin command #(say ...) printing to stdout. Useful for debugging.

- Nested /* */ comments.

- When a function-like macro invokation has no () arglist,
  NCM takes as the arguments everything up to the newline or the //-comment
  That would allow user the create elegant looking DSLs.
  Or use NCM to preprocess assembly files:
    #myopcode(a,b) {...}
    xor ax, ax
    myopcode bx, ax

- Escapable comas in arg list.

- A way to change `#` to another character, if you use the macroprocessor to
  preprocess a language where `#` is used for, say, comments.

- Auto adds extension ".h" to the files without one.

- And much more!


Notes:

- The ncm.h uses stb_ds.h for hash tables and lists.
  Rationale: It is public domain, easy to use, and
             many C/C++ developers are familiar with it.

- By default all comments get stripped stripped, unless kc=1 option provided.
  Rationale: The original C-preprocessor doens't support nested comments.
             User language may not support comment either
             In addition that improves the speed a bit.

- NCM provides _LINE_ and _FILE_ symbols (single underscores).
  Rationale: avoids shading the old CPP's __LINE__ and __FILE__

- That `say` command is defined only in the example ncm executable.
  If you include ncm.h, you will have to intercept it yourself.


QUICK REFERENCE
-------------------------

#("FORMAT_STRING" [ARGS])     printf style formatting
                              supported types: s,d,x,X,
                              supported flags: -,+,0
                              additional flags `?` specifies user defined
                              justification character, instead of ' ' or 0

#:path/to/a/file.ext          Include the contents of "path/to/a/file.ext".
                              The path is relative to folder of the current
                              file. If there is no such file, the global
                              include folders are searched.
                              If the file has no extension, then .h is appended.

#:"path/to/a/file.ext"        Same as above, but avoids the need to '\'-escape
                              spaces and special charaters.

#:<path/to/a/file.ext>        Same as above, but ignores the files inside the
                              current folder.


#:'FILENAME'                  Inserts the file unprocessed - as is.

#:file1.h;file2.h[;...]       Include multiple files.

#\SYMBOL...                   Removes `\`, and copies to the end of line.
                              For compatibility with the old CPP.
                              I.e. #\include could be used to include
                              the old headers, NCM is not supposed to process.

#(CONTENT)                    Passes CONTENT to the opts_table_t.command
                              callback, specified by user. The result is then
                              macro-processed. Used for custom features.

#:(CONTENT)                   Like above, but don't macro-process the result.


#:{[BODY]}                    The body won't be macro-processed but copied
                              as is. Useful when macro redefines some symbol.
                              For example:
                                 #inline {static
                                            __attribute__((always_inline))
                                            #:{inline}}
                              forces Clang to inline all functions declared
                              inline by redefining the inline keyword.

#once                         The code from this line to the end of this file
                              or the #multi directive is included only once.
                              Default for included .h files.

#multi                        The code from this line to the end of this file
                              or the #once directive is included multiple times.
                              Default for included non .h files.

#NAME [BODY]                  Defines a variable like macro NAME.
                              Takes as BODY everything up to newline
                              Newlines inside [BODY] should be escaped with '\'

#NAME(ARG0[,...]) {[BODY]}    Defines a function like macro NAME.
                              '}'s inside [BODY] should be escaped with '\'

#NAME({ARG0}[,...])           Same as above, but one of the arguments will be
                              the {...} block following the macro invocation.
                              Examples:
                                    #when(CND,{BODY}) {
                                      if (CND) {BODY}
                                    }
                                    #foreach(x,xs,{BLOCK}) {
                                      for(int i = 0; i < length(xs); i++) {
                                        x = xs[i];
                                        BLOCK
                                      }
                                    }


#{                            Opens macro scope. Macros declared inside will
                              shadow the same named macros outside.

 }                            Closes the macro scope. Freeing all local macros.

#extern NAME                  Exports NAME definition into the scope above

#undef NAME                   Undefine the macro NAME from the closest
                              scope it is in.


#if EXPR [BODY]               Inserts BODY only if EXPR1 isnt 0
#else [BODY]                  Inserts BODY only whne previous if got 0
#elif EXPR [BODY]             Shorthand for #else #if.
#endif                        Closes the #if/#else sequence.

#[EXPR]                       Evaluates integer arithmetic expression.
                              All C99 operators are supported and
                              have corresponding precedence.
                              Additional unary operator `# var` checks
                              if macro var is defined.
                              Macros can be referenced too as variables.
                              Example:
                                #x 123
                                #[log2(x*2 + 1)] //expands to 7

#<NAME>                       Explcitly treats NAME as a macro symbol.

"...#<NAME>..."               Inserts NAME into string.