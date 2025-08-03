#define _CRT_SECURE_NO_WARNINGS/* file_utils.h */
#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>

/*
����� ���� ������ (����� .am).
������ ����� ����� �� �����, ���� NULL.
*/
FILE* open_am_file(const char* base_name);

/*
����� �� ���� ��� �� ����� ������ (������ .ob, .ent, .ext).
������ �� ��� ����� ����.
*/
void build_filename(char* dest, const char* base_name, const char* extension);

/*
����� ���� ������. �� �� ���� ������� � ���� ���� ���.
*/
FILE* open_output_file(const char* base_name, const char* extension);

/*
����� ���� �� ��� ����.
*/
void safe_close(FILE* fp);

#endif
