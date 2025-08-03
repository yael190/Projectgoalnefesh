/* file_utils.c */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_utils.h"
#include "error_handler.h"

#define MAX_FILENAME_LENGTH 256

/* ����� ���� .am ������ ��� �� ���� */
FILE* open_am_file(const char* base_name) {
    char filename[MAX_FILENAME_LENGTH];
    build_filename(filename, base_name, ".am");
    FILE* file = fopen(filename, "r");
    if (!file) {
        report_error("����� ������ ���� .am", -1);
    }
    return file;
}

/* ���� �� ���� ��� �� ����� ����� */
void build_filename(char* dest, const char* base_name, const char* extension) {
    if (!dest || !base_name || !extension) return;

    size_t base_len = strlen(base_name);
    size_t ext_len = strlen(extension);

    if (base_len + ext_len >= MAX_FILENAME_LENGTH) {
        report_error("�����: �� ���� ���� ���", -1);
        dest[0] = '\0';
        return;
    }

    strcpy(dest, base_name);
    strcat(dest, extension);
}

/* ����� ���� ��� ��� ����� */
FILE* open_output_file(const char* base_name, const char* extension) {
    char filename[MAX_FILENAME_LENGTH];
    build_filename(filename, base_name, extension);
    if (filename[0] == '\0') {
        report_error("����� ������ �� ���� ����", -1);
        return NULL;
    }
    FILE* file = fopen(filename, "w");
    if (!file) {
        report_error("����� ������ ���� ���", -1);
    }
    return file;
}

/* ����� ���� �� ��� ���� */
void safe_close(FILE* fp) {
    if (fp != NULL) fclose(fp);
}
