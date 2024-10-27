#ifndef COMPILLER_FUNC_H_INCLUDED
#define COMPILLER_FUNC_H_INCLUDED

int find_tags(FILE *inputFile, tag *tagsArray);
int get_tag(char* a, tag *tagsArray);
void compile_args(FILE *inputFile, char returningMode, struct output_commands *outputArray, int commandNUM );
int check_input_value(int returningMode, int typeOfMemory);
int jump_argument(tag *tagsArray, FILE *inputFile, struct output_commands *outputArray, int jumpType);
void outputCommandFile(FILE *outputFile ,struct output_commands *outputArray);

#endif // COMPILLER_FUNC_H_INCLUDED
