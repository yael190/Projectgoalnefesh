#define _CRT_SECURE_NO_WARNINGS
#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "table.h"  /* ������ �-Label */
#include <stdio.h>

/*
    ���� �� ����� ������ �� ���� .am:
    - ���� �����, ���� ������, ������, ������ ������
    - ���� �� ���� ������ �����
    - ����� �� ������
    - �� ����� ������ � ����� 0, ���� 1

    ���:
    - fileName: �� ���� ���� (��� �����)
    - labelT: ����� ����� �������
    - sizeL: ���� �������

    ���:
    - 0 �� ����� ������, 1 �� �����
*/
int first_pass_file(const char* fileName, Label** labelT, int* sizeL,
    int* instruction_count, int* data_count);

#endif
