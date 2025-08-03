#ifndef CHECKFUNC_H
#define CHECKFUNC_H

/*
   ������ �������� ������� ����� ����� ����� ���������� ����.
   �� ������� ����� ���� ��� (line) ������ ��� ������ ���� ����� ���� ������.
   ������ 0 �� ��� ������, 1 �� ����� �����.
*/

/* ���� ������ �� ��� ��������� (mov, add, sub ���') */
int check_mov_add_sub(char* line);

/* ���� ������ �� ������� ��� (clr, not, inc, ���') */
int check_clr_not_inc_dec_red(char* line);

/* ���� ������ ��� ��������� (rts, stop) */
int check_rts_stop(char* line);

#endif
