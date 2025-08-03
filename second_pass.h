#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "encode_instruction.h"  /* ����� Symbol */

/*
    ���� �� ��� ����� ����:
    - ���� �� ���� .am
    - ���� ������ .entry ������ �� ���� ������
    - ����� ������ ��� ���� ������
    - ���� ���� ��� .ob, .ent, .ext

    �������:
    - base_name: �� ���� �� ����� (��� �����)
    - symbol_table: ���� ������ ������ ����� �����
    - symbol_count: ���� ������ �����
    - instruction_count: ���� ������
    - data_count: ���� ����� ������

    ��� ��� ����� � ���� ���� ������ �� ������ ����� �������.
*/
void second_pass(const char* base_name, Symbol* symbol_table, int symbol_count, int instruction_count, int data_count);

#endif
