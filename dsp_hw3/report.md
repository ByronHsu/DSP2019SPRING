# DSP HW3

> b05901011 電機三 許秉倫



## Setting

- Environment - macosx

- Compile

  ``````bash
  # Compile mydisambig.cpp
  make
  # Generate map
  make map
  ``````

- Execution

  - Customize 'run' part in Makefile:

  ```bash
  # Format
  ./mydisambig -text <testdata> -map <map> -lm <lm> -order 2 > <output>;
  ```


## Implementation

1. Set up the environment

   The installing process was very painful. 

   I encountered a weird bug. I spent so much time and finally found out it was because the path variable in Makefile does not allow 'space'.  (i.e. user/byron hsu/a.txt is illegal becauase there is a space between 'byron' and 'hsu')

2. Preprocess the data

   After the environment problem is solved, preprocessing is quite easy. Just follow the TA's instructions, and everything go well like expected.

3. `mapping.py`

   Python is super convenient. I take advantage of the `dict` in python and only write about 20 lines of codes to implement it.

4. `mydisambig.cpp`

   This part is a little complicated. Firstly, I spent time on figuring out how to use the `srilm` package. Secondly, I use what I have learned in DSnP course to design structures of node and graph. And the rest is coding, debugging, coding and debugging... 

   After a lot of hard working, I finally produce the same result as what `disambig` produces.





