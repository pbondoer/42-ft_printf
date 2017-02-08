# ft\_printf @ 42
Because I'm tired of using putnbr and putstr

This project aims at rebuilding the printf library with basic functionality. I
tried to implement as much of the original as possible, and also have a few
extra things which I found to be rather useful.

Extra conversions:

| Name		| Conversion	| Example output	|
| --------- | ------------- | ----------------- |
| Binary	| b				| 00001001			|

## Compiling
Make sure to edit the `Makefile` to point to
[libft](https://github.com/pbondoer/42-libft). Run `make` to compile the
library. Use it like you would use the `printf` function:

```c
int i;

i = 42;
ft_printf("value: %d\n", i);

// value: 42
```

## Unit tests
This project also has a set of unit tests in the `test` folder. Run `make test`
to check against this library or edit the tests in the folder to run them
against your own ft\_printf.

## License
`ft_printf` is under the **GNU General Public License 3.0**.
