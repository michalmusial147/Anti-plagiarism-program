#include "dictionary.h"
#include "vector.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main()
{
	char * filename1, *filename2;
	filename1 = (char*)malloc(51);
	if (filename1 == NULL)
	{
		printf("Failed to allocate memory");
		return 4;
	}
	filename2 = (char*)malloc(51);
	if (filename2 == NULL)
	{
		free(filename1);
		printf("Failed to allocate memory");
		return 4;
	}
	printf("Podaj nazwe pliku nr1: ");
	fgets(filename1, 51, stdin);
	strtok(filename1, "\n");
	FILE *f = fopen(filename1, "rt");
	if (f == NULL)
	{
		free(filename1);
		free(filename2);
		printf("File not found");
		return 2;
	}
	
	int err_code;
	struct dictionary_t *d1, *d2, *dcommon;
	int test;
	////////////////////////// PIERWSZY /////////////////////////////////
				
				char * buf;
				buf = (char*)malloc(41);
				if (buf == NULL)
				{
					free(filename1);
					free(filename2);
					fclose(f);
					printf("Failed to allocate memory");
					return 4;
				}
				d1 = create_dictionary(10);
				if (d1 == NULL)
				{
					free(filename1);
					free(filename2);
					free(buf);
					printf("Failed to allocate memory");
					fclose(f);
					return  4;
				}
				//
				while (!feof(f))
				{
						test = fscanf(f, "%s", buf);
						if (!test)
							break;
						strtok(buf, ".");
						strtok(buf, ",");
						strtok(buf, "?");
						strtok(buf, "!");
			
						test = dictionary_add_word(d1, buf);

						if (test == 2)
						{
							free(filename1);
							free(filename2);
							free(buf);
							printf("Failed to allocate memory");
							fclose(f);
							destroy_dictionary(&d1);
							return 4;
						}
				}
				fclose(f);
				
				printf("Podaj nazwe pliku nr2: ");
				fgets(filename2, 51, stdin);
				strtok(filename2, "\n");
				
				f = fopen(filename2, "rt");
				if (f == NULL)
				{
					free(filename1);
					free(filename2);
					free(buf);
					destroy_dictionary(&d1);
					printf("File not found");
					return 2;
				}
				
				d2 = create_dictionary(10);
				if (d2 == NULL)
				{
					free(filename1);
					free(filename2);
					destroy_dictionary(&d1);
					free(buf);
					printf("Failed to allocate memory");
					fclose(f);
					return  4;
				}
				// drugi
				while (!feof(f))
				{
					test = fscanf(f, "%s", buf);
					if (!test)
						break;
					strtok(buf, ".");
					strtok(buf, ",");
					strtok(buf, "?");
					strtok(buf, "!");

					test = dictionary_add_word(d2, buf);

					if (test == 2)
					{
						free(filename1);
						free(filename2);
						free(buf);
						printf("Failed to allocate memory");
						fclose(f);
						destroy_dictionary(&d1);
						destroy_dictionary(&d2);
						return 4;
					}
				}
				fclose(f);
	/////////     TRZEEEEEEEEEECIIIIIIIIII ///////////////
		dcommon = create_dictionary(10);
		if (dcommon == NULL)
		{
			free(filename1);
			free(filename2);
			destroy_dictionary(&d1);
			destroy_dictionary(&d2);
			free(buf);
			printf("Failed to allocate memory");
			return  4;
		}
		
		for (int i = 0; i < d1->size; i++)
		{
			for (int j = 0; j < (d1->wc + i)->counter; j++)
			{
				err_code = dictionary_add_word(dcommon, (d1->wc + i)->word);
				if (err_code == 2)
				{
					free(filename1);
					free(filename2);
					destroy_dictionary(&d1);
					destroy_dictionary(&d2);
					destroy_dictionary(&dcommon);
					free(buf);
					printf("Failed to allocate memory");
					return  4;
				}
			}
		}
		for (int i = 0; i < d2->size; i++)
		{
			for (int j = 0; j < (d2->wc + i)->counter; j++)
			{
				err_code = dictionary_add_word(dcommon, (d2->wc + i)->word);
				if (err_code == 2)
				{
					free(filename1);
					free(filename2);
					destroy_dictionary(&d1);
					destroy_dictionary(&d2);
					destroy_dictionary(&dcommon);
					free(buf);
					printf("Failed to allocate memory");
					return  4;
				}
			}
		}
	
		struct array_t *v1, *v2;

		err_code = create_array(&v1, dcommon->size);
		if (err_code)
		{
			free(filename1);
			free(filename2);
			destroy_dictionary(&d1);
			destroy_dictionary(&d2);
			destroy_dictionary(&dcommon);
			free(buf);
			printf("Failed to allocate memory");
			return  4;
		}
		err_code = create_array(&v2, dcommon->size);
		if (err_code)
		{
			free(filename1);
			free(filename2);
			destroy_dictionary(&d1);
			destroy_dictionary(&d2);
			destroy_dictionary(&dcommon);
			free(buf);
			printf("Failed to allocate memory");
			return  4;
		}
		struct word_count_t *wp;
		int d1_sum=0, d2_sum=0;
		for (int i = 0; i < d1->size; i++)
		{
			d1_sum += (d1->wc + i)->counter;
		}
		for (int i = 0; i < d2->size; i++)
		{
			d2_sum += (d2->wc + i)->counter;
		}
		float bufer;
		for (int i = 0; i < dcommon->size; i++)
		{

			wp = dictionary_find_word(d1, (dcommon->wc + i)->word);
			if (wp == NULL)
				add(v1, 0);
			else 
			{
				bufer = wp->counter;
				bufer /= (double)d1_sum/1.0;
				add(v1, bufer);
			}
			wp = dictionary_find_word(d2, (dcommon->wc + i)->word);
			if (wp == NULL)
				add(v2, 0);
			else 
			{
				bufer = wp->counter;
				bufer /= (double)d2_sum / 1.0;
				add(v2, bufer);
			}
		}
		double dot = dot_product(v1, v2);
		double len_mult = length(v1) * length(v2);

		printf("	Podobienstwo to : %.5f\n", dot / len_mult);
		free(filename1);
		free(filename2);
		destroy_dictionary(&d1);
		destroy_dictionary(&d2);
		destroy_dictionary(&dcommon);
		free(buf);
		destroy_array(&v1);
		destroy_array(&v2);
		printf("Wcisnij dowolny przycisk by kontynuowac");
		getchar();
		return 0;
}

