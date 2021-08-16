# `isdense` — a loadable builtin for bash

`isdense` is a command you can load into your bash shell using `enable`.

`isdense a` checks if the indexed array `a` is dense, or sparse when using `! isdense a`.  
An indexed array is dense iff `a=("${a[@]}")` has no effect.

`isdense` prints nothing, unless there is an error. The exit status `$?` lets distinguish between dense and sparse arrays.

Space and time complexity of `isdense a` is indepent of the size and structure of `a`. The check should be as fast as something like `s=1`.

`a` can also be a nameref.

## Examples

```bash
a=(x y z) # dense
b=([1]=x [4]=y) # sparse
```

```bash
if isdense someArray; then
  echo "array is dense"
else
  echo "array is sparse"
fi
```

## Installation

1. Download the [source code](https://ftp.gnu.org/gnu/bash/) of your current bash version.
2. Unpack bash's source code.
3. Download [isdense.c](https://github.com/schaetzc/bash-loadable-is-array-dense/blob/main/isdense.c) and store it in `bash-.../examples/loadables/`
4. Modify the build process in `bash-.../examples/loadables/` so that `isdense.c` is built. The easiest way to do this is ... 
```bash
cd bash-.../
sh configure
cd examples/loadables/
sed -i.bak 's/sleep/isdense/g' Makefile
make isdense
```
6. Load the builtin into your bash shell using `enable -f ./isdense isdense` or better `enable -f /full/path/to/isdense isdense`

Of course the installation process and `isdense` itself depend on the version of bash. However, the relevant parts seem to be pretty stable. I was able to compile `isdense` for bash 3.2.57 (the version used on mac OS) and load the result into my bash 5.1.8.
