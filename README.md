# notmalloc the memory allocator that is not malloc 


is it safer than malloc? Probably not. is it more space efficient than malloc? Also probably not but it is mine.



if you want to try to use this knock yourself out the makefile will only work on a mac(for now) and the actual code will probably only work on unix machines(for now maybe) but you simply use the `notmalloc` and `notfree` functions to allocate and free memory as usual.