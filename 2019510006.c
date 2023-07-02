#include <stdio.h>
#include <malloc.h>

struct Employee
{
    char name[64];      //utf16
    char surname[32];   //utf8
    char gender;
    char email[32];
    char phone_number[16];
    char address[32];
    char level_of_education[8];
    unsigned int income_level;  // given little-endian
    unsigned int expenditure;   // given big-endian
    char currency_unit[16];
    char currentMood[32];
    float height;
    unsigned int weight;
};
unsigned int LTB(unsigned int x) {

    return (((x >> 24) & 0x000000FF) | ((x >> 8) & 0x0000FF00) | ((x << 8) & 0x00FF0000) | ((x << 24) & 0xFF000000));
}

unsigned BTL(unsigned val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}
struct Employee *Read_Employees(char filePath[])
{
    struct Employee *emp = calloc(51, sizeof(struct Employee));
    FILE *BinaryFile;
    BinaryFile = fopen(filePath, "rb");
    if(BinaryFile == NULL)
    {
        printf("File is not found.");
        return emp;
    } else{
        struct Employee temp;
        for(int i = 0; i < 51; i++){
            fread(&temp, sizeof(struct Employee), 1, BinaryFile);
                emp[i] = temp;
        }
    }

    fclose(BinaryFile);
    return emp;
}

int main(int argc, char* argv[]) {

    struct Employee *Employees = Read_Employees(argv[1]);
    FILE *xml = fopen(argv[2], "w");
    fprintf(xml, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(xml, "\t%s","<records>\n");
    printf("successful\n");

    for (int i = 1; i < 51; ++i) {
        fprintf(xml, "\t\t<row id = \"%d\">\n", (i));
        fprintf(xml, "\t\t\t%s%s%s\n", "<name>",Employees[i].name,"</name>");
        fprintf(xml, "\t\t\t%s%s%s\n", "<surname>",Employees[i].surname,"</surname>");
        fprintf(xml, "\t\t\t%s%c%s\n", "<gender>",Employees[i].gender,"</gender>");
        fprintf(xml, "\t\t\t%s%s%s\n", "<email>",Employees[i].email,"</email>");
        fprintf(xml, "\t\t\t%s%s%s\n", "<phone_number>",Employees[i].phone_number,"</phone_number>");
        fprintf(xml, "\t\t\t%s%s%s\n", "<address>",Employees[i].address,"</address>");
        fprintf(xml, "\t\t\t%s%s%s\n", "<level_of_education>",Employees[i].level_of_education,"</level_of_education>");
        fprintf(xml, "\t\t\t<income_level %s\"%u\">%u%s\n","bigEnd=",LTB(Employees[i].income_level),Employees[i].income_level,"</income_level>");
        fprintf(xml, "\t\t\t<expenditure %s\"%u\">%u%s\n","bigEnd=",Employees[i].expenditure,BTL(Employees[i].expenditure),"</expenditure>");
        fprintf(xml, "\t\t\t%s%s%s\n", "<currency_unit>",Employees[i].currency_unit,"</currency_unit>");
        fprintf(xml, "\t\t\t%s%s%s\n", "<currentMood>",Employees[i].currentMood,"</currentMood>");
        fprintf(xml, "\t\t\t%s%f%s\n", "<height>",Employees[i].height,"</height>");
        fprintf(xml, "\t\t\t%s%u%s\n", "<weight>",Employees[i].weight,"</weight>");

        fprintf(xml, "\t\t</row>\n");
    }
    fprintf(xml, "\t%s","</records>\n");

    return 0;
}
