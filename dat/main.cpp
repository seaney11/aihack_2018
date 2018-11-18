#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <boost/python.hpp>


#define LEFT_OFFSET_C 8
#define X_DIV 3

char const* greet()
{
   return "hello, world";
}

BOOST_PYTHON_MODULE(gwas_loader)
{
    using namespace boost::python;
    def("greet", greet);
}



int main(int argc, const char** argv) {
	FILE* fp;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;


	for(int i=1; i<23; i++) {
		char buffer[256];
		sprintf(buffer, "raw/AIHack-SNP-Matrix-%d.csv", i);
		fp = fopen(buffer, "r");
		if(fp == NULL)
			exit(EXIT_FAILURE);

		char* f_line = NULL;
		size_t f_line_len = 0;
		getline(&f_line, &f_line_len, fp);

		//printf("%s", f_line);
		int comma_count = 0;
		for(int k=0; k<f_line_len; k++) {
			if(f_line[k] == ',')
				comma_count++;
		}
		char **names = (char**) malloc(comma_count*sizeof(char*));
		int name_num = 0;
		int start = 0;
		for(int k=0; k<f_line_len; k++) {
			if(f_line[k] == ','){
				names[name_num] = (char*) malloc((k-start)*sizeof(char));
				memcpy(names[name_num], f_line+start, k-start-1);
				names[name_num][k-start-1] = '\0';
				//printf("name: %s\n", names[name_num]);
				name_num++;
				start = k+2;
			}
		}
			

		printf("Chromasome: %d - %d snips\n", i, comma_count);
		
		char oname_buf[1024];
		//sprintf(oname_buf, "rs/c%d-%d-%s.csv", i, j, cname);
		FILE* f = fopen(oname_buf, "a");

		
		
		fclose(f);

		for (int k = 0; k < comma_count; k++){
			free(names[k]);
		}
		free(names);
	}

	fclose(fp);
	if (line)
		free(line);
}
