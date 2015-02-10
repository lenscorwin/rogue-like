# How to Contribute

Wanna contribute ? Nice :D

There is some code rule, to keep the project and the code lisible.

### Releases:
> Base code's rules
Louis <louis@ne02ptzero.me>

# Code Norm

### Base

##### Style
The K & R style is __REQUIRED__

```cpp
if (TRUE) {
	/* Some code */
} else {
	/* Some code again */
}
```

##### Naming convention

For function's name, go with the Javascript Naming rules:

```cpp
void	MyAwesomeFunction(void) {
	/* Some code */
}
```
##### File name convention

For a class file, respect the Javascript naming rules (^)
```MyClassName.cpp```
```MyClassName.hpp```
Of course, the name of the class file must the respect the name of the class itself.


For a main, or outside-class functions, the Unix convention.
```main.cpp```
```my_awesome_functions.cpp```

> Note of the author
> Seem's like a little complicated, but we can actually make the difference betweeen class and functions with a ls.

### Comments


##### Base Header
A header file comment is required:

```cpp
/**
 * File: FileName.cpp
 * Creation: YYYY-MM-DD HH:MM
 * Username <username@mail.com>
 */
```

##### License
Also, we are on the Apache License, so __EACH__ file would have the following header:
```cpp
/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an
 *  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, either express or implied.  See the License for the
 *  specific language governing permissions and limitations
 * under the License.
 */
```

#### Function comment header
A header to __EACH__ function is required too, except one-line function (Getters and setters).
```cpp
/**
 * What the function do (In a few words)
 * @param: First Parameter name (type)
 * @param: Second Parameter name (type)
 * ...
 * @return: The return variable name
 */

/* EXAMPLE */

/**
 * Count and return the length of a string.
 * @param: str (const char *)
 * @return: n
 */
size_t		strlen(const char *str) {
	/* Some code */
	return n;
}
```

# Git rules

### Commit

A Commit norm is also required:
```
Action(target): Title
<Blank line>
Description of the commit
Can be two lines
<Blank line>
```

Here action is the basic code change on a project (Add, Fix, Feat (Features), Bug, Doc).
The target is where your commit is making change (Core, Graphic design, physic motor, etc....)

**Example:**
```
git commit -m "Add(Core): Add a debug function

I've added a debug function, to close the issue #154
Also, we gain 1.3s at the build.

"
```

### Build

*For main contributors:*
Be carefull, the build verification is make __after__ your push. so look at the travis icon for build.

*For pull requests*
Travis is automaticlly made the build, so if it failed, we can past you the debug as a comment to your pull request.

Happy contributing :)
