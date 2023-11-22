// 由两个 @ 标注的变量将会被 CMake 替换为版本号
#define Tutorial_VERSION_MAJOR 1
#define Tutorial_VERSION_MINOR 0

// 如果 USE_MYMATH 选项被选中，CMake 将会导入 USE_MYMATH 宏
#define USE_MYMATH

// 系统提供了 log 和 exp 函数吗？
/* #undef HAVE_LOG */
/* #undef HAVE_EXP */
