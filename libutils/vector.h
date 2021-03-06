#ifndef VECTOR_H
#define VECTOR_H

struct vector {
    void **mem;
    size_t len;
    size_t alloc;
};

extern struct vector *vec_new(void);

extern struct vector *vec_new1(void *val);

extern struct vector *vec_newn(size_t capacity);

extern void vec_free(struct vector *v);

extern void *vec_at(struct vector *v, int index);

extern void *vec_at_safe(struct vector *v, int index);

extern void vec_set(struct vector *v, int index, void *val);

extern void vec_set_safe(struct vector *v, int index, void *val);

extern void vec_push(struct vector *v, void *val);

extern void vec_push_safe(struct vector *v, void *val);

extern void vec_push_front(struct vector *v, void *val);

extern void *vec_pop(struct vector *v);

extern void *vec_pop_front(struct vector *v);

extern void vec_clear(struct vector *v);

extern int vec_empty(struct vector *v);

extern size_t vec_len(struct vector *v);

extern void *vec_head(struct vector *v);

extern void *vec_tail(struct vector *v);

extern void vec_add(struct vector *v, struct vector *v2);

extern struct vector *vec_reverse(struct vector *v);

extern struct vector *vec_copy(struct vector *v);

extern struct vector *vec_sort(struct vector *v, int (*sort) (const void *val1, const void *val2));

extern void *vtoa(struct vector *v, unsigned int area);

extern void vec_add_array(struct vector *v, void *array);

#endif
