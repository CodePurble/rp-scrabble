# General

If you are interested to contribute to this codebase, fork this project first.
Then work on the changes in your copy, and submit a pull request. Creating new
branches for features is highly recommended instead of directly committing to
`master`. If you are not in a position to contribute code but still have
suggestions, open up an issue and I'll take a look at it!

# Coding Style

When submitting code, the following guidelines must be followed:

* Use **TABS** having a size of **4** spaces instead of just spaces to indent
  the code.
* Class names must be **capitalised**
	```cpp
	class Foo {
		...
	};

	NOT

	class foo {
		...
	};
	```
* Braces for functions must start on **new lines**

	```cpp
	void foo()
	{
		...
	}

	NOT

	void foo() {
		...
	}
	```
* Braces must be used even for one-line conditional statements or loops and
  they must be attached

	```cpp
	if(isFoo) {
	}

	for(;;) {
	}
	```
**If you are unsure, just follow the coding style that is used in the code you
are working on**

# Comments

All new classes and methods must be commented using the **javadoc** style for
use with Doxygen. Use inline comments only when they are concise and are really
required.
