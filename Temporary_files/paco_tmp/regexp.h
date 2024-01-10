/**
 * @file regexp.h
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  28 09:56:03 2022
 * @brief General include for regexp
 *
 * General include for regexp, as in the project's pdf document
 */

#ifndef _REGEXP_H_
#define _REGEXP_H_
#include <pyas/list.h> 
#include <pyas/chargroup.h>

#ifdef __cplusplus
extern "C" {
#endif



int issFull(int characters[256]);
int re_match_zero_or_more(int characters[256], list_t regexp, char *source, char **end);
int re_match(list_t regexp, char *source, char **end);
int re_match_empty(list_t regexp, char *source, char **end);
int re_match_one_or_more(int characters[256], list_t regexp, char *source, char **end);


#ifdef __cplusplus
}
#endif

#endif /* _ALL_H_ */
