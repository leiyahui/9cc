#ifndef COLOR_H
#define COLOR_H

#ifdef CONFIG_COLOR_TERM

#define RESET    "\033[0m"
#define CLEAR    "\033[1;38m"

// regular
#define BLACK_COLOR    "\033[0;30m"
#define RED_COLOR      "\033[0;31m"
#define GREEN_COLOR    "\033[0;32m"
#define YELLOW_COLOR   "\033[0;33m"
#define BLUE_COLOR     "\033[0;34m"
#define PURPLE_COLOR   "\033[0;35m"
#define CYAN_COLOR     "\033[0;36m"
#define WHITE_COLOR    "\033[0;37m"

// bold
#define BLACK_BOLD_COLOR    "\033[1;30m"
#define RED_BOLD_COLOR      "\033[1;31m"
#define GREEN_BOLD_COLOR    "\033[1;32m"
#define YELLOW_BOLD_COLOR   "\033[1;33m"
#define BLUE_BOLD_COLOR     "\033[1;34m"
#define PURPLE_BOLD_COLOR   "\033[1;35m"
#define CYAN_BOLD_COLOR     "\033[1;36m"
#define WHITE_BOLD_COLOR    "\033[1;37m"

#else

#define RESET    ""
#define CLEAR    ""

#define BLACK_COLOR    ""
#define RED_COLOR      ""
#define GREEN_COLOR    ""
#define YELLOW_COLOR   ""
#define BLUE_COLOR     ""
#define PURPLE_COLOR   ""
#define CYAN_COLOR     ""
#define WHITE_COLOR    ""

#define BLACK_BOLD_COLOR    ""
#define RED_BOLD_COLOR      ""
#define GREEN_BOLD_COLOR    ""
#define YELLOW_BOLD_COLOR   ""
#define BLUE_BOLD_COLOR     ""
#define PURPLE_BOLD_COLOR   ""
#define CYAN_BOLD_COLOR     ""
#define WHITE_BOLD_COLOR    ""

#endif /* CONFIG_COLOR_TERM */

#define BLACK(str)    BLACK_COLOR str RESET
#define RED(str)      RED_COLOR str RESET
#define GREEN(str)    GREEN_COLOR str RESET
#define YELLOW(str)   YELLOW_COLOR str RESET
#define BLUE(str)     BLUE_COLOR str RESET
#define PURPLE(str)   PURPLE_COLOR str RESET
#define CYAN(str)     CYAN_COLOR str RESET
#define WHITE(str)    WHITE_COLOR str RESET

#define BLACK_BOLD(str)    BLACK__BOLD_COLOR str RESET
#define RED_BOLD(str)      RED_BOLD_COLOR str RESET
#define GREEN_BOLD(str)    GREEN_BOLD_COLOR str RESET
#define YELLOW_BOLD(str)   YELLOW_BOLD_COLOR str RESET
#define BLUE_BOLD(str)     BLUE_BOLD_COLOR str RESET
#define PURPLE_BOLD(str)   PURPLE_BOLD_COLOR str RESET
#define CYAN_BOLD(str)     CYAN_BOLD_COLOR str RESET
#define WHITE_BOLD(str)    WHITE_BOLD_COLOR str RESET

#endif
