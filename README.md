# Build Guide

# Complete Build
clang -std=c89 -W -Wall -pedantic-errors -D_CRT_SECURE_NO_WARNINGS *.c

# For Traslation Unit
clang -std=c89 -W -Wall -pedantic-errors -E -D_CRT_SECURE_NO_WARNINGS *.c > *.pre

# For Assembly Code
clang -std=89 -W -Wall -padantic-errors -S -D_CRT_SECURE_NO_WARNINGS *.c

# For Object Code
clang -std=89 -W -Wall -padantic-errors -e -D_CRT_SECURE_NO_WARNINGS *.c
