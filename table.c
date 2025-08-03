#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

int addLabel(const char* tempLabel, Label** labelT, int sizeL, int DC, int type) {
    Label* temp = realloc(*labelT, (sizeL + 1) * sizeof(Label));
    if (!temp) {
        fprintf(stderr, "שגיאת זיכרון בהוספת תווית\n");
        return 2;
    }
    *labelT = temp;
    strncpy((*labelT)[sizeL].name, tempLabel, 30);
    (*labelT)[sizeL].name[30] = '\0';
    (*labelT)[sizeL].address = DC;
    (*labelT)[sizeL].codeOrDS = type;
    return 0;
}

int findLabel(Label* labels, int count, const char* name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(labels[i].name, name) == 0)
            return 1;
    }
    return 0;
}

void printLabelTable(Label* labels, int count) {
    int i;
    printf("טבלת סמלים:\n");
    for (i = 0; i < count; i++) {
        printf("  תווית: %-10s כתובת: %04d סוג: %s\n",
            labels[i].name,
            labels[i].address,
            labels[i].codeOrDS == 0 ? "קוד" : "נתון");
    }
}

Symbol* convert_labels_to_symbols(Label* labels, int count) {
    Symbol* symbols = malloc(sizeof(Symbol) * count);
    int i;
    if (!symbols) {
        fprintf(stderr, "שגיאה בהקצאת זיכרון לטבלת סמלים\n");
        return NULL;
    }
    for (i = 0; i < count; i++) {
        strncpy(symbols[i].name, labels[i].name, 30);
        symbols[i].name[30] = '\0';
        symbols[i].address = labels[i].address;
        symbols[i].is_external = (labels[i].codeOrDS == -1);
        symbols[i].is_entry = 0;
    }
    return symbols;
}
