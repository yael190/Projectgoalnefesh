/* error_handler.h */
#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

/*
������ �� ����� �� ��� ����� �����, ������ ������� �����.
���� ������ �� ���� ���� (�� -1 �� �� �������).
*/
void report_error(const char* message, int line_number);

/*
����� ��� ����� ����� ����� ��� �� ��.
*/
int has_errors();

/*
����� �� ��� ������� (������ �������� ���� ���).
*/
void reset_errors();
void print_errors();


#endif
