# 2021-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
# See license.md for details.

all: prepare build
all-release: prepare-release build
examples: all build-examples

prepare:
	cmake -B staging -DCMAKE_BUILD_TYPE=Debug

prepare-release:
	cmake -B staging

build:
	cmake --build staging

build-examples:
	cmake --build staging --target spirits-example-allocation

clean:
	rm -rf staging

run:
	staging/./spirits-example-allocation

grind:
	valgrind --leak-check=full staging/spirits-example-allocation	

symbols:
	nm -an staging/spirits-example-allocation | c++filt