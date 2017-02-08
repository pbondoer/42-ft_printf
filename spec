printf specification // structures

- [digit] $ (optional)
next argument to access, if not provided, uses last accessed. indexing from 1

- flags (optional)
 -> #
c,d,i,n,p,s,u -- no effect
o -- precision increased to force start with 0
x,X -- 0x or 0X if != 0
a,A,e,E,f,F,g,G -- always display decimal point even if no digits follow
			g,G -- do not remove trailing 0s

 -> 0
all except n -- left padding with 0 rather than blanks
d,i,o,u,x,X and precision -- no effect

 -> -
same as 0 but with right padding, overrides 0
uses blanks only

 -> ' ' (space)
a,A,d,e,E,f,F,g,G,i -- leave blank before positive value

 -> +
same as ' ' (space) but puts a + sign, overrides ' ' (space)

 -> ' (apostrophe)
d,u,i -- separate by thousands
f,F -- separate integral part by thousands
use localeconv(3) to find separator

- [digits] (optional)
specifies minimum field width, if value is less length it will be padded

- .[digits] (optional)
precision, if no digits = 0
d,i,o,u,x,X -- minimum number of digits
a,A,e,E,f,F -- number of digits after decimal point
g,G -- maximum number of significant digits
s -- maximum string length

- length modifier (optional)
--------------------------------------------------------------------------------
Modifier          d, i           o, u, x, X            n
--------------------------------------------------------------------------------
hh                signed char    unsigned char         signed char *
h                 short          unsigned short        short *
l (ell)           long           unsigned long         long *
ll (ell ell)      long long      unsigned long long    long long *
j                 intmax_t       uintmax_t             intmax_t *
z                 (see note)     size_t                (see note)
--------------------------------------------------------------------------------
Modifier          a, A, e, E, f, F, g, G
--------------------------------------------------------------------------------
l (ell)           double (ignored, same behavior as without it)
L                 long double
--------------------------------------------------------------------------------
Modifier          c         s                            (THIS IS FOR UNICODE)
--------------------------------------------------------------------------------
l (ell)           wint_t    wchar_t *
--------------------------------------------------------------------------------
