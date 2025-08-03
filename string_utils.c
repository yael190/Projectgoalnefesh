#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "string_utils.h"
#include "error_handler.h"

#define BUFFER_SIZE 128

/*
    ���� ���� ��� ���� ���� ���.
    ����� �� ��� ������, ������ �� ��� ����.
*/
char* read_word(char** line) {
    int i = 0;
    char* temp;
    int bufferSize = BUFFER_SIZE;
    char* buffer = (char*)malloc(bufferSize * sizeof(char));

    if (!buffer) {
        report_error("����� ������: ����� ������ �����", -1);
        return NULL;
    }

    while (isspace(**line)) (*line)++;

    if (**line == ',') {
        buffer[i++] = **line;
        buffer[i] = '\0';
        (*line)++;
        return buffer;
    }

    while (isspace(**line)) (*line)++;

    while (**line != ',' && **line != '\0' && !isspace(**line)) {
        buffer[i++] = **line;
        (*line)++;

        if (i >= bufferSize) {
            bufferSize += BUFFER_SIZE;
            temp = (char*)realloc(buffer, bufferSize * sizeof(char));
            if (!temp) {
                report_error("����� ������: ����� ���� �����", -1);
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }
    }

    buffer[i] = '\0';
    return buffer;
}

/*
    ���� ������ ������� ������ �� ������.
*/
char* trim_whitespace(char* str) {
    char* end;
    if (!str) return NULL;
    while (isspace((unsigned char)*str)) str++;
    if (*str == '\0') return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
    return str;
}

/*
    ���� ������ �������� �� ��� ����� ���.
*/
char* trim_quotes(char* str) {
    size_t len;
    if (!str) return NULL;
    len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
        str[len - 1] = '\0';
        return str + 1;
    }
    return str;
}

/*
    ���� ���� ��� �� ������ ����� ����� ������ ������.
    ����� NULL �� ����.
*/
char* duplicateString(const char* src) {
    if (!src) return NULL;
    char* copy = (char*)malloc(strlen(src) + 1);
    if (copy) strcpy(copy, src);
    return copy;
}
