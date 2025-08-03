#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "table.h"
#include "check.h"
#include "checkFunc.h"
#include "file_utils.h"
#include "encode_instruction.h"
#include "error_handler.h"
#include "finalize_output.h"
#include "string_utils.h"

/*
    מבצע את המעבר הראשון על קובץ .am
    - בונה את טבלת הסמלים (כולל extern)
    - סופר הוראות ונתונים
    - מקודד פקודות לא תלויות בתוויות
    - כותב את הפלט הבינארי לקובץ .ob
*/
int first_pass_file(const char* fileName, Label** labelT, int* sizeL,
    int* instruction_count, int* data_count) {
    int error = 0;
    int DC = 0;
    int IC = 100;
    int isLabelDefined = 0;
    char str[100];
    char tempLabel[31];

    FILE* read_file = open_am_file(fileName);
    if (!read_file) {
        printf("שגיאה: לא ניתן לפתוח את הקובץ %s.am\n", fileName);
        return 0;
    }

    char** instructions = malloc(sizeof(char*) * 500);
    char** data = malloc(sizeof(char*) * 500);
    int inst_index = 0;
    int data_index = 0;

    while (fgets(str, sizeof(str), read_file) != NULL) {
        char lineCopy[100];
        strcpy(lineCopy, str);
        char* linePtr = lineCopy;
        char* firstWord = read_word(&linePtr);
        if (!firstWord) continue;

        /* בדיקת תווית */
        if (firstWord[strlen(firstWord) - 1] == ':') {
            firstWord[strlen(firstWord) - 1] = '\0';
            if (!isLabel(firstWord)) {
                printf("שגיאה: שם תווית לא חוקי '%s'\n", firstWord);
                error = 1;
                continue;
            }
            if (isListSaveWord(firstWord)) {
                printf("שגיאה: '%s' היא מילה שמורה\n", firstWord);
                error = 1;
                continue;
            }
            if (findLabel(*labelT, *sizeL, firstWord)) {
                printf("שגיאה: תווית כפולה '%s'\n", firstWord);
                error = 1;
                continue;
            }
            strcpy(tempLabel, firstWord);
            isLabelDefined = 1;
            free(firstWord);
            firstWord = read_word(&linePtr);
            if (!firstWord) continue;
        }

        if (strcmp(firstWord, ".data") == 0) {
            if (isLabelDefined) {
                if (addLabel(tempLabel, labelT, *sizeL, DC + IC, 1) == 0) (*sizeL)++;
            }
            char* token;
            while ((token = read_word(&linePtr)) != NULL) {
                if (strcmp(token, ",") == 0) {
                    free(token);
                    continue;
                }
                int val = atoi(token);
                data[data_index++] = encode_value_with_are(val, 0);
                DC++;
                free(token);
            }
        }
        else if (strcmp(firstWord, ".string") == 0) {
            if (isLabelDefined) {
                if (addLabel(tempLabel, labelT, *sizeL, DC + IC, 1) == 0) (*sizeL)++;
            }
            char* quote = strchr(linePtr, '"');
            if (quote) {
                quote++;
                while (*quote && *quote != '"') {
                    data[data_index++] = encode_value_with_are((int)*quote, 0);
                    DC++;
                    quote++;
                }
                data[data_index++] = encode_value_with_are(0, 0);
                DC++;
            }
            else {
                printf("שגיאה: מחרוזת לא תקינה\n");
                error = 1;
            }
        }
        else if (strcmp(firstWord, ".extern") == 0) {
            char* label_name = read_word(&linePtr);
            if (label_name) {
                if (findLabel(*labelT, *sizeL, label_name)) {
                    printf("שגיאה: תווית '%s' כבר קיימת\n", label_name);
                    error = 1;
                }
                else {
                    Label* temp = realloc(*labelT, (*sizeL + 1) * sizeof(Label));
                    if (!temp) {
                        printf("שגיאת זיכרון\n");
                        fclose(read_file);
                        return 2;
                    }
                    *labelT = temp;
                    strncpy((*labelT)[*sizeL].name, label_name, 30);
                    (*labelT)[*sizeL].name[30] = '\0';
                    (*labelT)[*sizeL].address = 0;
                    (*labelT)[*sizeL].codeOrDS = -1;
                    (*sizeL)++;
                }
                free(label_name);
            }
        }
        else if (strcmp(firstWord, ".entry") == 0) {
            // לא רלוונטי למעבר ראשון
        }
        else if (isInstruction(firstWord)) {
            if (isLabelDefined) {
                if (addLabel(tempLabel, labelT, *sizeL, IC, 0) == 0) (*sizeL)++;
            }
            WordBin* bin = encode_instruction(firstWord, IC, NULL, 0, NULL, NULL);
            if (bin) {
                for (int j = 0; j < bin->count; j++) {
                    instructions[inst_index++] = duplicateString(bin->words[j]);  /* <<< שימוש בפונקציה הבטוחה */
                }
                IC += bin->count;
                free_wordbin(bin);
            }
            else {
                error = 1;
            }
        }
        else {
            printf("שגיאה: פקודה לא מזוהה '%s'\n", firstWord);
            error = 1;
        }

        isLabelDefined = 0;
        free(firstWord);
    }

    fclose(read_file);

    *instruction_count = IC - 100;
    *data_count = DC;

    write_final_ob_file(fileName, instructions, *instruction_count, data, *data_count);

    free_string_array(instructions, *instruction_count);
    free_string_array(data, *data_count);
    printLabelTable(*labelT, *sizeL);

    return (error ? 0 : 1);
}
