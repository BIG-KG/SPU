#ifndef COMPILLER_FUNC_H_INCLUDED
#define COMPILLER_FUNC_H_INCLUDED

int find_tags(FILE *inputFile, tag *tagsArray);
int get_tag(char* a, tag *tagsArray);
void compile_args(FILE *inputFile, FILE *outputFile, char returningMode);
int check_input_value(int returningMode, int typeOfMemory);
int jump_argument(tag *tagsArray, FILE *inputFile, FILE *outputFile, int jumpType);

#endif // COMPILLER_FUNC_H_INCLUDED
