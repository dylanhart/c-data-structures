#ifndef __STRBUF_H__
#define __STRBUF_H__ 1

#define STRBUF_DEFAULT_CAPACITY 64

/**
 * StrBuf
 * a string buffer object that allows the user to build a string dynamically
 *
 * str: the string
 * size: the size of the string buffer
 * len: the length of the string
 */
typedef struct {
	char* str;
	size_t size;
	size_t len;
} StrBuf;

/**
 * creates a string buffer with the given initial size
 *
 * size: the size of the new buffer
 * return: the new buffer
 */
StrBuf* strbuf_new(size_t size);

/**
 * creates a string buffer with the default size
 *
 * return: the new buffer
 */
StrBuf* strbuf_default();

/**
 * appends a char to the given buffer resizing if needed
 *
 * sb: the buffer to append to
 * c: the char to append
 */
void strbuf_append(StrBuf* sb, const char c);

/**
 * appends a string to the given buffer resizing if needed
 *
 * sb: the buffer to append to
 * chars: the string to append
 */
void strbuf_appends(StrBuf* sb, const char* chars);

/**
 * clears the string buffer
 *
 * sb: the stringbuffer to clear
 */
void strbuf_clear(StrBuf* sb);

/**
 * builds the final string and frees the given string buffer
 *
 * sb: the string buffer
 * return: the final string
 */
char* strbuf_build(StrBuf* sb);

/**
 * frees the given string buffer
 *
 * sb: the string buffer
 */
void strbuf_free(StrBuf* sb);

#endif
