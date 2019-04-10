//////////////////////////////////////////////////////////////////////////////////////

							// SLOWNIK//

//////////////////////////////////////////////////////////////////////////////////////


#include "dictionary.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

struct dictionary_t* create_dictionary(int N)
{
	if (N <= 0)
		return NULL;

	struct dictionary_t *dic = malloc(sizeof(struct dictionary_t));
	if (dic == NULL)
		return NULL;
	dic->size = 0;
	dic->capacity = N;
	dic->wc = malloc(sizeof(struct word_count_t)*N);
	if (dic->wc == NULL)
	{
		free(dic);
		return NULL;
	}

	return dic;
}

void destroy_dictionary(struct dictionary_t** d)
{
	if (d == NULL)
		return;
	if (*d == NULL)
		return;
	for (int i = 0; i < (*d)->size; i++)
	{
		if (((*d)->wc + i)->word != NULL)
			free( ((*d)->wc + i) -> word );
	}
	if((*d)->wc!=NULL)
		free((*d)->wc);
	if ((*d) != NULL)
		free(*d);
	return;
}

struct word_count_t* dictionary_find_word(const struct dictionary_t *d, const char *word)
{
	if (d == NULL || word == NULL)
		return NULL;
	if (d->size < 0 || d->capacity < 0 || d->capacity < d->size || d->wc == NULL)
		return NULL;
	for (int i = 0; i < d->size; i++)
	{
		if (!strcmp(word, (d->wc + i)->word))
			return (d->wc + i);
	}
	return NULL;

}

void dictionary_display(const struct dictionary_t *d)
{
	if (d == NULL)return;
	if (d->wc == NULL)return;
	if (d->size < 0 || d->capacity < 0 || d->capacity < d->size)
		return;
	for (int i = 0; i < d->size; i++)
	{
		printf("%s %i\n", ((d->wc) + i)->word, ((d->wc) + i)->counter);
	}
	return;
}

int dictionary_add_word(struct dictionary_t *d, const char *word)
{
	if (d == NULL || word == NULL)
		return 1;
	if (d->size < 0 || d->capacity < 0 || d->capacity < d->size || d->wc == NULL)
		return 1;
	struct word_count_t* lookin_word = dictionary_find_word(d, word);
	if (lookin_word == NULL)  //not nie ma
	{
		if (d->size == d->capacity)	//not enough capacity need memory
		{
			d->capacity *= 2;
			struct word_count_t*tmp;
			tmp = realloc(d->wc, sizeof(struct word_count_t)*d->capacity);
			if (tmp==NULL)
			{
				d->capacity /= 2;
				return 2;
			}
			 d->wc = tmp;
			(d->wc + d->size)->word = (char*)malloc(strlen(word) + 1);	//alokuj na slowo

			if ((d->wc + d->size)->word == NULL)
			{
				return 2;
			}

			strncpy(((d->wc) + d->size)->word, word, strlen(word) + 1);
			(d->wc + d->size)->counter = 1;
			d->size++;
		}
		else//enough place
		{

			((d->wc) + (d->size))->word = (char*)malloc(strlen(word) + 1);

			if (((d->wc) + (d->size))->word == NULL)
			{
				return 2;
			}

			strncpy(((d->wc) + d->size)->word, word, strlen(word) + 1);
			(d->wc + d->size)->counter = 1;
			d->size++;
		}
	}
	else
	{
		lookin_word->counter += 1;
	}
	return 0;

}

int cmpstrings(char *word1, char *word2)
{
	int i;
	for (i = 0; *(word1 + i) && *(word2 + i); i++)
	{
		
		if(  (*(word1 + i)>='A' && *(word1 + i)<='Z') && ( *(word2 + i) >= 'A' && *(word2 + i) <= 'Z'))
		{ 
			//compere big letters
			if (*(word1 + i) > *(word2 + i))
			{
				return 2;
			}
			else if(*(word1 + i) < *(word2 + i))
			{
				return 1;
			}
			else if (*(word1 + i) == *(word2 + i))
			{
				//check next letter//
					  //i++//
			}
		}
		else if ((*(word1 + i) >= 'a' && *(word1 + i) <= 'z') && (*(word2 + i) >= 'a' && *(word2 + i) <= 'z'))
		{
			//compere small letters
			if (*(word1 + i) > *(word2 + i))
			{
				return 2;
			}
			else if (*(word1 + i) < *(word2 + i))
			{
				return 1;
			}
			else if (*(word1 + i) == *(word2 + i))
			{
				//check next letter//
				//i++//
			}
		}
		else if ((*(word1 + i) >= 'A' && *(word1 + i) <= 'Z') && (*(word2 + i) >= 'a' && *(word2 + i) <= 'z'))
		{
			//	compere	 	big	   and	 small
			/*if (*(word1 + i) + 32 > *(word2 + i))
			{
				return 2;
			}
			else if (*(word1 + i) + 32 < *(word2 + i))
			{
				return 1;
			}
			else if (*(word1 + i) + 32 == *(word2 + i))
			{	same but big latter bigger
				*/
				return 1;
		}
		else if ((*(word1 + i) >= 'a' && *(word1 + i) <= 'z') && (*(word2 + i) >= 'A' && *(word2 + i) <= 'Z'))
		{
			/*	compere	 	small	  and	 big
			if (*(word1 + i) > *(word2 + i) + 32)
			{
				return 2;
			}
			else if (*(word1 + i) < *(word2 + i) + 32)
			{
				return 1;
			}
			else if (*(word1 + i) == *(word2 + i) + 32)
			{	// same but big latter bigger
			*/
				return 2;
			//}
		}

	}
	if (((*(word1 + i) == '\0')) && (*(word2 + i) == '\0'))
		return 0;
	if ((*(word1 + i) == '\0'))
		return 1;
	if ((*(word2 + i) == '\0'))
		return 2;

	return 0;

}

int dictionary_sort_alphabetically(struct dictionary_t *d)
{
	if (d == NULL)
		return 1;
	if (d->wc == NULL)
		return 1;
	if (d->size < 0 || d->capacity < 0 || d->capacity < d->size || d->wc == NULL)
		return 1;

	int i, j, n;
	n = d->size;
	int change = 0;
	for (i = 0; i < n - 1; i++)
	{
		change = 0;
		for (j = 0; j < n - i - 1; j++)
		{	//ugliest if in whole world bleh//
			if (cmpstrings((d->wc + j)->word, (d->wc + j + 1)->word) == 2)
			{
				char * tmpcharp = (d->wc + j)->word;
				int tmpcounter = (d->wc + j)->counter;
				(d->wc + j)->word = (d->wc + j + 1)->word;
				(d->wc + j)->counter = (d->wc + j + 1)->counter;
				(d->wc + j + 1)->word = tmpcharp;
				(d->wc + j + 1)->counter = tmpcounter;
				change = 1;
			}
		}

		// IF no two elements were swapped by inner loop, then break
		if (change == 0)
			break;
	}

	return 0;
}

int dictionary_sort_occurence(struct dictionary_t *d)
{

	
		if (d == NULL)
			return 1;
		if (d->wc == NULL)
			return 1;
		if (d->size < 0 || d->capacity < 0 || d->capacity < d->size || d->wc == NULL)
			return 1;

		int i, j, n;
		n = d->size;
		int change = 0;
		for (i = 0; i < n - 1; i++)
		{
			change = 0;
			for (j = 0; j < n - i - 1; j++)
			{	//ugliest if in whole world bleh//
				if ((d->wc + j)->counter  <  (d->wc + j + 1)->counter )
				{
					char * tmpcharp = (d->wc + j)->word;
					int tmpcounter = (d->wc + j)->counter;
					(d->wc + j)->word = (d->wc + j + 1)->word;
					(d->wc + j)->counter = (d->wc + j + 1)->counter;
					(d->wc + j + 1)->word = tmpcharp;
					(d->wc + j + 1)->counter = tmpcounter;
					change = 1;
}
				
				if((d->wc + j)->counter  ==  (d->wc + j + 1)->counter)
					if (cmpstrings((d->wc + j)->word, (d->wc + j + 1)->word) == 2)
					{
						char * tmpcharp = (d->wc + j)->word;
						int tmpcounter = (d->wc + j)->counter;
						(d->wc + j)->word = (d->wc + j + 1)->word;
						(d->wc + j)->counter = (d->wc + j + 1)->counter;
						(d->wc + j + 1)->word = tmpcharp;
						(d->wc + j + 1)->counter = tmpcounter;
						change = 1;
					}
			}
			// IF no two elements were swapped by inner loop, then break
			if (change == 0)
				break;
		}

	
	
	return 0;
}

int save_dictionary_b(const struct dictionary_t *d, const char *filename)
{
	if (d == NULL || filename == NULL)
		return 1;
	if(d->size<=0 || d->capacity <=0|| d->wc == NULL)
		return 1;
	FILE*f = fopen(filename, "wb");
	if (f == NULL)
		return 2;
	fwrite(&d->size, sizeof(int), 1, f);
	for(int i = 0 ; i < d->size ; i ++)
	{ 
		int len = strlen((d->wc + i)->word);
		fwrite(&len, sizeof(int),1, f);
		fwrite((d->wc + i)->word, len, 1, f);
		fwrite(&(d->wc + i)->counter, sizeof(int), 1, f);
	}
	fclose(f);
	return 0;

}

struct dictionary_t* load_dictionary_b(const char *filename, int *err_code)
{
	if (filename == NULL)
	{
		if (err_code != NULL)
			*err_code = 1;
		return NULL;
	}
	
	struct dictionary_t* d;
	d = (struct dictionary_t*)malloc(sizeof(struct dictionary_t));
	if (d == NULL)
	{
		if (err_code != NULL)
			*err_code = 4;
		return NULL;
	}
	FILE*f = fopen(filename, "rb");
	if (f == NULL)
	{
		if (err_code != NULL)
			*err_code = 2;
		free(d);
		return NULL;
	}
	if (strstr(filename, ".txt"))
	{
		if (err_code != NULL)
			*err_code = 3;
		free(d);
		fclose(f);
		return NULL;
	}
	int read_val;
	read_val = fread(&d->size, sizeof(int), 1, f);
	if (read_val == 0 || d->size<=0)
	{
		if (err_code != NULL)
			*err_code = 3;
		fclose(f);
		free(d);
		return NULL;
	}
	d->capacity = d->size;
	d->wc = malloc(sizeof(struct word_count_t)*d->size);
	if (d->wc == NULL)
	{
		if (err_code != NULL)
			*err_code = 4;
		fclose(f);
		free(d);
		return NULL;
	}
	d->size = 0;
	
	for (int i = 0 ; i < d->capacity; i++, d->size++)
	{
		int len;
		read_val = fread(&len, sizeof(int), 1, f);
		if (read_val == 0 || len<=0)
		{
			if (err_code != NULL)
				*err_code = 3;
			fclose(f);
			destroy_dictionary(&d);
			return NULL;
		}
		(d->wc + i)->word = (char*)malloc(len + 1);
		if((d->wc + i)->word == NULL)
		{
			if (err_code != NULL)
				*err_code = 4;
			fclose(f);
			destroy_dictionary(&d);
			return NULL;
		}
		*((d->wc + i)->word + len) = 0;
		read_val = fread((d->wc + i)->word, len, 1, f);
		if(read_val == 0)
		{
			if (err_code != NULL)
				*err_code = 3;
			fclose(f);
			destroy_dictionary(&d);
			return NULL;
		}
		read_val = fread(&(d->wc + i)->counter, sizeof(int), 1, f);
		if (read_val == 0|| (d->wc + i)->counter<=0)
		{
			if (err_code != NULL)
				*err_code = 3;
			fclose(f);
			destroy_dictionary(&d);
			return NULL;
		}
	}
	*err_code = 0;
	fclose(f);
	return d;
}
