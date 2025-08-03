#define _CRT_SECURE_NO_WARNINGS/* finalize_output.h */
#ifndef FINALIZE_OUTPUT_H
#define FINALIZE_OUTPUT_H

#include "encode_instruction.h"

/*
������� �� ����� ������ ������� (�� 14 ������) ����� ����������.
����� ������ ������� ������� ������ ���������� ����.
*/
char* binary_to_hex(const char* binary);

/*
������� �� ����� �� ������ ������� �������� ������ ���� .ob ����.
��� �����:
- base_name: �� ���� �� �����
- instructions: ���� ������� �������� �� �������
- icf: ���� ������ ����
- data: ���� ������� �������� �� �������
- dcf: ���� ������ ����

���� ��� ���� ob �����.
*/
void write_final_ob_file(const char* base_name, char** instructions, int icf, char** data, int dcf);

/*
������� �� ������ ������ ��� ���� ������� �����.
*/
void free_string_array(char** array, int size);

#endif
