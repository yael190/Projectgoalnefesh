mcro .data   ; �� �� ���� - �� ���� �����
    mov r5, r6
mcroend

mcro PRINT_NUM
    prn r3
mcroend
mcro PRINT_NUM  ; ���� ���� - ���� ����� �����
    prn r4
mcroend

HELLO:
    PRINT_NUM
    stop
