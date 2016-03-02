#include <stdlib.h>
#include <stdio.h>

#include "strbuf.h"

StrBuf* strbuf_new(size_t size) {
	StrBuf* sb = malloc(sizeof(StrBuf));
	sb->str = malloc(size * sizeof(char));
	sb->size = size;
	sb->len = 0;
	return sb;
}

StrBuf* strbuf_default() {
	return strbuf_new(STRBUF_DEFAULT_CAPACITY);
}

void strbuf_append(StrBuf* sb, const char c) {
	// resize if needed
	if (sb->len >= sb->size) {
		sb->size *= 2;
		sb->str = realloc(sb->str, sb->size);
	}
	// append char
	sb->str[sb->len++] = c;
}

void strbuf_appends(StrBuf* sb, const char* chars) {
	while (*chars != 0) {
		strbuf_append(sb, *chars);
		chars++;
	}
}

void strbuf_clear(StrBuf* sb) {
	sb->len = 0;
}

char* strbuf_build(StrBuf* sb) {
	// resize to fit str and add terminating null
	sb->str = realloc(sb->str, sb->len+1);
	sb->str[sb->len] = 0;

	char* ret = sb->str;
	free(sb);
	return ret;
}

void strbuf_free(StrBuf* sb) {
	free(sb->str);
	free(sb);
}
