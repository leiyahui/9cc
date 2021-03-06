#include <stdio.h>
#include <stdlib.h>
#include "cc.h"

struct options opts;

static void parse_opts(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        const char *arg = argv[i];
        if (!strcmp(arg, "-o")) {
            if (++i >= argc)
                die("missing target file while -o option given");
            opts.ofile = argv[i];
        } else if (!strcmp(arg, "-ast-dump")) {
            opts.ast_dump = true;
        } else if (!strcmp(arg, "-Werror")) {
            opts.Werror = true;
        } else if (!strcmp(arg, "-Wall")) {
            opts.Wall = true;
        } else if (!strcmp(arg, "-E")) {
            opts.preprocess_only = true;
        } else if (!strcmp(arg, "-fleading_underscore")) {
            opts.fleading_underscore = true;
        } else if (!strcmp(arg, "-ansi")) {
            opts.ansi = true;
        } else if (arg[0] != '-' || !strcmp(arg, "-")) {
            if (opts.ifile == NULL)
                opts.ifile = arg;
            else if (opts.ofile == NULL)
                opts.ofile = arg;
        }
    }

    // reopen stdout
    if (opts.ofile && strcmp(opts.ofile, "-")) {
        if (freopen(opts.ofile, "w", stdout) == NULL)
            die("can't write file: %s", opts.ofile);
    }
}

static void preprocess(void)
{
    struct token *t = get_pptok(cpp_file);
    for (; t->id != EOI; t = get_pptok(cpp_file))
        print("%t", t);
}

static void doexit(void)
{
    debug_exit();
}

int main(int argc, char *argv[])
{
    atexit(doexit);
    parse_opts(argc, argv);
    debug_init(argc, argv);
    actions.init(argc, argv);
    symbol_init();
    type_init();
    cpp_init(argc, argv);

    if (opts.preprocess_only)
        preprocess();
    else
        translation_unit();

    return errors() > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
