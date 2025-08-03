#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "macro_handler.h" /* ���� ����� MacroTable */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    ���� ���� ����� ���� ���� input.txt,
    ������ ���� ������� �� ���� ����� ��� ������.
    ���� ����� ������ fileCount ����� �� ���� ������ ������.
    ����� NULL ����� �� �����.
*/
char** read_file_list(const char* filename, int* fileCount);

/*
    ���� ���-����� (preprocess) �� �� ������ �������,
    ���� ����� �������, ������, ������ ���� .am
*/
void preprocess_files(MacroTable* table, char** fileNames, int fileCount);


/*
    ���� ����� ������� �� ���� ��� ���� �� ����� .as
    ����� ���� ��� �� ����� .am
*/
void process_file(MacroTable* table, const char* fileName);



#endif
