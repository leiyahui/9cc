#ifndef _STRING_H
#define _STRING_H

struct str {
    char    *str;
    size_t  len;
    size_t  alloc;
};

extern struct str * new_str();

extern void free_str(struct str *s);

extern size_t str_len(struct str *s);

extern void str_add(struct str *s, struct str *s2);

extern void str_cats(struct str *s, const char *src);

extern void str_catn(struct str *s, const char *src, size_t len);

extern void str_catd(struct str *s, long d);

extern void str_lstrip(struct str *s);

extern void str_rstrip(struct str *s);

extern void str_strip(struct str *s);

// key-value storage

extern char *strs(const char *str);

extern char *strn(const char *src, size_t len);

extern char *strd(long n);

extern char * stoa(struct str *s);

extern char *format(const char *fmt, ...);

#endif