# KMP
A better way to calculate next-array by KMP algorithm.

## Problem
```
for example
a b a c a b
The old way calculated next-array as follow:
0 0 1 0 1 2
```

See that, when the last letter failed, `i` is 5 and it'll turn to the value of next[i - 1].
Then `i` is 1, it try to math 'b' again.
So we want the next-array as follow:
```
a b a c a b
0 0 1 0 0 0
```
when not match turn to the value of next[i - 1]

Or as follow:
```
a b a c a b
0 0 0 1 0 0
```
when not match turn to the value of next[i]

Note that, 'ab' and 'ac' has the same prefix and they are only the last letter is not equal.
So we try to use a state to mark the substring has the same prefix with pattern string.
And When it is not matched, state turn to 0 and update next-array by the position of head pointer.

Like following:

```
First init next-array by 0.

Step 1:
flag = 0
|
v
a b a c a b
0 0 0 0 0 0

Step 2:
flag = 0
| |
v v
a b a c a b
0 0 0 0 0 0

Step 3:
flag = 1(matched and mark flag)
|   |
v   v
a b a c a b
0 0 0 0 0 0

Step 4:
flag = 0(turn to 0 when not matched, and update next-array)
  |   |
  v   v
a b a c a b
0 0 0 1 0 0

Step 5:
flag = 1(matched and mark flag)
|       |
v       v
a b a c a b
0 0 0 1 0 0

Step 6:
flag = 1(matched and mark flag)
  |       |
  v       v
a b a c a b
0 0 0 1 0 0

Notice, after this step, next-array is update complite.
```

## Other explain
This code can pass the test of [LintCode.]: http://www.lintcode.com/zh-cn/problem/strstr/