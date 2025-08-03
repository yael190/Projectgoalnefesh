#ifndef TABLE_H
#define TABLE_H

typedef struct {
    char name[31];
    int address;
    int codeOrDS;
} Label;

typedef struct {
    char name[31];
    int address;
    int is_external;
    int is_entry;
} Symbol;

int addLabel(const char* tempLabel, Label** labelT, int sizeL, int DC, int type);
int findLabel(Label* labels, int count, const char* name);
void printLabelTable(Label* labels, int count);
Symbol* convert_labels_to_symbols(Label* labels, int count);

#endif
