#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "checkFunc.h"
#include "table.h"
#include "reserved.h"
#include "error_handler.h"
#include "string_utils.h"

/* ���� �� �� ��� ����� ����� ����� ����� ���� */
int isLabel(char* word) {
    
    int length = (int)strlen(word);

    if (length > 31) {
        report_error("�� ����� ���� ���", -1);
        return 0;
    }
    if (!isalpha(word[0])) {
        report_error("�� ����� ���� ������ ����", -1);
        return 0;
    }
    for (int i = 1; i < length; i++) {
        if (!isalnum(word[i])) {
            report_error("����� ����� ����� �� ������", -1);
            return 0;
        }
    }
    return 1;
}

/* ���� �� ���� ��� ���� ����� ���� */
int isListSaveWord(char* word) {
    return isReservedKeyword(word);
}

/* ���� �� ����� ��� ����� ��� ����� ����� ������� */
int findLabel(Label* labels, int count, const char* name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(labels[i].name, name) == 0) return 1;
    }
    return 0;
}

/* ���� �� ������ ��� ���� ��� ���� */
int isValidInteger(char* word) {
    char* current = word;
    while (*current == ' ' || *current == '\t') current++;
    if (*current == '\0') return 0;
    if (*current == '+' || *current == '-') current++;
    if (!isdigit(*current)) return 0;
    while (*current != '\0') {
        if (!isdigit(*current)) return 0;
        current++;
    }
    return 1;
}

/* ���� �� ������ ��� ������ ����� ������ .string */
int checkString(char* str) {
    char* start = str;
    while (*start == ' ' || *start == '\t') start++;
    if (*start != '"') return 0;
    start++;
    char* end = strchr(start, '"');
    if (end == NULL) return 0;
    char* after = end + 1;
    while (*after == ' ' || *after == '\t') after++;
    if (*after != '\0' && *after != '\n') return 0;
    if (start == end) return 0;
    return 1;
}

/* ����� �� ������ ��� ����� ������ ����� */
int isInstruction(const char* word) {
    static const char* instructions[] = {
        "mov", "cmp", "add", "sub", "lea",
        "clr", "not", "inc", "dec",
        "jmp", "bne", "jsr",
        "red", "prn", "rts", "stop"
    };
    int i;
    for (i = 0; i < sizeof(instructions) / sizeof(instructions[0]); i++) {
        if (strcmp(word, instructions[i]) == 0) return 1;
    }
    return 0;
}


/* ���� �� ������ ������� �������� ���� .data, ���� ������ ������� */
int checkData(char* line, int* dataValues, int* DC) {
    char* lineCopy = strdup(line);
    char* linePtr = lineCopy;
    char* token;
    int expectNumber = 1;
    int error = 0;
    int tempDC = DC ? *DC : 0;

    while ((token = read_word(&linePtr)) != NULL) {
        if (strlen(token) == 0) {
            free(token);
            continue;
        }

        if (strcmp(token, ",") == 0) {
            if (expectNumber) {
                report_error("���� ����� �� ����", -1);
                error = 1;
            }
            expectNumber = 1;
            free(token);
            continue;
        }

        if (!isValidInteger(token)) {
            char msg[100];
            snprintf(msg, sizeof(msg), "���� '%s' ���� ���� ����", token);
            report_error(msg, -1);
            error = 1;
            free(token);
            break;
        }

        if (dataValues) {
            dataValues[tempDC] = atoi(token);
        }
        tempDC++;
        expectNumber = 0;
        free(token);
    }

    if (expectNumber && tempDC > 0) {
        report_error("��� ��� ���� ����", -1);
        error = 1;
    }

    if (DC) *DC = tempDC;

    free(lineCopy);
    return error;
}